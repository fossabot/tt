/*
 * Copyright (c) 2020 Danilo Spinella <danyspin97@protonmail.com>.
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

#include "tt/cli/command/command.hpp"

#include <memory>
#include <utility>

#include "args.hxx"

#include "tt/cli/define.hpp"
#include "tt/cli/log.hpp"

using std::shared_ptr;

using tt::cli::Command;
using tt::cli::GlobalOptions;

Command::Command(args::Subparser &parser,
                 shared_ptr<GlobalOptions> global_options)
    : parser_(parser), global_options_(std::move(global_options)) {}

int Command::InitAndExecute() {
    parser_.Parse();
    auto verbosity = global_options_->verbosity_.Matched()
                         ? global_options_->verbosity_.Get()
                         : tt::cli::DEFAULT_VERBOSITY;
    tt::cli::setupConsoleLoggers(verbosity, global_options_->quiet_);
    return Execute();
}
