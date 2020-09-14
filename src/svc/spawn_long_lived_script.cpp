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

#include "tt/svc/spawn_long_lived_script.hpp"

#include <poll.h>

#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"

#include "pstream.h"

tt::SpawnLongLivedScript::SpawnLongLivedScript(const std::string &service_name,
                                               const LongLivedScript &script,
                                               const Environment &environment)
    : SpawnScript(service_name, script, environment, [](std::string) {}),
      long_lived_script_(script) {}

tt::SpawnLongLivedScript::~SpawnLongLivedScript() {
    if (signals_handled_) {
        ResetSignals();
    }
}

auto tt::SpawnLongLivedScript::Spawn() -> ScriptStatus {
    SetupSignals();
    if (long_lived_script_.notify()) {
        SetupNotifyFd();
    }
    RunScript();
    if (long_lived_script_.notify()) {
        return ListenOnNotifyFd();
    }
    waiting_on_startup_ = true;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(long_lived_script_.timeout()));
    waiting_on_startup_ = false;
    return ScriptStatus::Success;
}

void tt::SpawnLongLivedScript::RunScript() {
    if (int pid = fork(); pid == 0) {
        execve("/bin/sh", const_cast<char **>(GetExecArgs().data()), NULL);
        spdlog::critical("An error had happened while running execve: {}",
                         strerror(errno));
        exit(1);
    }
}

auto tt::SpawnLongLivedScript::GetExecArgs() -> std::vector<char *> {
    std::vector<char *> args{};
    args.push_back(const_cast<char *>("/bin/sh"));
    args.push_back(const_cast<char *>("-c"));
    args.push_back(long_lived_script_.execute().data());
    args.push_back(0);
    return args;
}

auto tt::SpawnLongLivedScript::ListenOnNotifyFd() -> ScriptStatus {
    short revents = 0;
    struct pollfd fd = {notify_fd_, POLLIN, revents};
    int res = poll(&fd, 1, long_lived_script_.timeout());
    // We got a revents on notify_fd_
    if (res == 1) {
        if (revents | POLLIN) {
            return ScriptStatus::Success;
        }
    };
    // Timeout
    if (res == 0) {
        return ScriptStatus::Failure;
    }
    return ScriptStatus::Failure;
}

void tt::SpawnLongLivedScript::SetupNotifyFd() {
    std::array<int, 2> fd;
    pipe(fd.data());
    notify_fd_ = dup(fd[0]);
    close(dup(fd[0]));
    dup2(fd[1], long_lived_script_.notify().value());
}

void tt::SpawnLongLivedScript::HandleSignal(int /*signum*/) {
    // TODO
}

void tt::SpawnLongLivedScript::SetupSignals() {
    // TODO
}

void tt::SpawnLongLivedScript::ResetSignals() {
    // TODO
}