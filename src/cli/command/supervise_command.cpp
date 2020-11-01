/*
 * Copyright (c) 2020 Danilo Spinella <oss@danyspin97.org>.
 *
 * This file is part of tt
 * (see https://github.com/danyspin97/tt).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "tt/cli/command/supervise_command.hpp"

#include <poll.h>
#include <sys/stat.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <future> // for async
#include <utility>

#include "args.hxx"

#include "bitsery/adapter/buffer.h"
#include "bitsery/bitsery.h"

#include "tt/cli/global_options.hpp"
#include "tt/log/service_logger_registry.hpp" // for ServiceLoggerRegistry
#include "tt/supervision/longrun_supervisor.hpp"
#include "tt/supervision/signal_handler.hpp" // for AddSignalToSet, ...
#include "tt/utils/deserialize.hpp"
#include "tt/utils/read_buffer_from_file.hpp"

tt::cli::SuperviseCommand::SuperviseCommand(
    args::Subparser &parser, std::shared_ptr<GlobalOptions> common_options)
    : Command(parser, std::move(common_options)),
      filename_(parser, "filename", "Filename to read the longrun from") {}

auto tt::cli::SuperviseCommand::Execute() -> int {
    sigset_t set;
    tt::AddSignalsToSet(stop_signals, &set);
    tt::AddSignalToSet(SIGCHLD, &set);
    tt::MaskSignals(&set);

    auto longrun = utils::Deserialize<Longrun>(args::get(filename_));

    ServiceLoggerRegistry logger_registry{dirs()};
    auto name = longrun.name();
    LongrunSupervisor supervisor{std::move(longrun),
                                 logger_registry.GetLongrunLogger(name)};
    // Run the longrun in another thread
    auto longrun_run_successfully = std::async(
        std::launch::async, [&supervisor]() { return supervisor.Run(); });

    // We don't want to wait on SIGCHLD
    tt::RemoveSignalFromSet(SIGCHLD, &set);
    // Wait until we receive a stop signal
    tt::WaitOnSignalSet(&set);
    supervisor.Kill();
    return longrun_run_successfully.get() ? 0 : 255;
}
