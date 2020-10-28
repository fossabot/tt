/*
 * Copyright (c) 2020 Rasmus Thomsen <oss@cogitri.dev>
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

#include <functional> // for function
#include <iostream>   // for operator<<, endl
#include <memory>     // for allocator, mak...
#include <string>     // for string

#include "args.hxx"        // for ArgumentParser
#include "fmt/format.h"    // for format_to
#include "spdlog/spdlog.h" // for info

#include "tt/cli/command/command.hpp"                 // for Command
#include "tt/cli/command/command_dispatcher.hpp"      // for CommandDispatcher
#include "tt/cli/command/enable_command.hpp"          // for EnableCommand
#include "tt/cli/command/parse_command.hpp"           // for ParseCommand
#include "tt/cli/command/serialize_command.hpp"       // for SerializeCommand
#include "tt/cli/command/service_control_command.hpp" // for ServiceControl...
#include "tt/cli/command/supervise_command.hpp"       // for SuperviseCommand
#include "tt/cli/global_options.hpp"                  // for GlobalOptions
#include "tt/exception.hpp"                           // for Exception

auto main(int argc, char *argv[]) -> int {
    args::ArgumentParser parser("tt init/rc manager.");
    auto common_options = std::make_shared<tt::cli::GlobalOptions>();

    tt::cli::CommandDispatcher dispatcher{common_options};

    args::Group manage{(args::Group &)parser, "Manage services"};

    // TODO: Decomment them when they have an action assigned each
    // args::Command(manage, "start", "Start/restart one or more services");
    // args::Command(manage, "stop", "Stop one or more services");
    args::Command enable(manage, "enable", "Enable one or more services",
                         dispatcher.Dispatch<tt::cli::EnableCommand>());
    // args::Command(manage, "disable", "Disable one or more services");
    // args::Command(manage, "edit-config", "Edit the config of a service");

    // args::Group query(parser, "Query the status of the system");
    // args::Command show(query, "show",
    //                   "Show the status and the configuration of a service");
    // args::Command status(query, "status", "Show the status of the system");

    // args::Group query(parser, "Query the status of the system");
    // args::Command show(query, "show",
    //                   "Show the status and the configuration of a service");

    args::Group system((args::Group &)parser, "System commands");
    args::Command svc(system, "svc", "Run service control",
                      dispatcher.Dispatch<tt::cli::ServiceControlCommand>());

    args::Command supervise(system, "supervise",
                            "Supervise a process [Do not run manually]",
                            dispatcher.Dispatch<tt::cli::SuperviseCommand>());

    args::Group testing((args::Group &)parser, "Test services files");
    args::Command parse(testing, "parse",
                        "Parse one or more services for testing purposes.",
                        dispatcher.Dispatch<tt::cli::ParseCommand>());
    args::Command serialize(testing, "serialize",
                            "Serialize a longrun into a file",
                            dispatcher.Dispatch<tt::cli::SerializeCommand>());

    args::GlobalOptions global_options(parser, common_options->arguments());

    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Help & /*e*/) {
        parser.Help(std::cout);
    } catch (const args::Error &e) {
        std::cerr << e.what() << std::endl;
        parser.Help(std::cout);
        return 1;
    }

    return dispatcher.exit_code();
}
