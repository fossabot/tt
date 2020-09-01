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

#pragma once

#include "tt/svc/spawn_script.hpp"

namespace tt {

class SpawnLongLivedScript : public SpawnScript {
public:
    explicit SpawnLongLivedScript(const std::string &service_name,
                                  const LongLivedScript &script,
                                  const Environment &environment);

    auto Spawn() -> ScriptStatus;
    ~SpawnLongLivedScript() override;

private:
    void HandleSignal(int signum);
    auto GetExecArgs() -> std::vector<char *>;
    auto ListenOnNotifyFd() -> ScriptStatus;
    void ResetSignals();
    void RunScript();
    void SetupNotifyFd();
    void SetupSignals();

    LongLivedScript long_lived_script_;
    bool waiting_on_startup_;
    bool signals_handled_;
    int notify_fd_;
};

} // namespace tt
