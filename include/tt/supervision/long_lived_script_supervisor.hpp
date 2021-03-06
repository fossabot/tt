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

#pragma once

#include <string> // for string

#include "tt/data/long_lived_script.hpp"        // for LongLivedScript
#include "tt/supervision/script_supervisor.hpp" // for ScriptSupervisor
#include "tt/supervision/types.hpp"             // for ScriptStatus

namespace tt {
class Environment;
class ScriptLogger;

class LongLivedScriptSupervisor : public ScriptSupervisor {
public:
    explicit LongLivedScriptSupervisor(const std::string &service_name,
                                       const LongLivedScript &script,
                                       const Environment &environment,
                                       const ScriptLogger &logger);

    auto ExecuteScript() -> ScriptStatus;

private:
    [[nodiscard]] auto ListenOnNotifyFd() const -> ScriptStatus;
    void SetupNotifyFd();

    LongLivedScript long_lived_script_;
    int notify_fd_ = 0;
};

} // namespace tt
