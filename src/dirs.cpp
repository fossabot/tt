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

#include "tt/dirs.hpp"

auto tt::Dirs::GetInstance() -> tt::Dirs & {
    static tt::Dirs instance;

    return instance;
}

auto tt::Dirs::bindir() const -> const std::string & { return bindir_; }

auto tt::Dirs::confdir() const -> const std::string & { return confdir_; }

auto tt::Dirs::execline_prefix() const -> const std::string & {
    return execline_prefix_;
}

auto tt::Dirs::libexecdir() const -> const std::string & { return libexecdir_; }

auto tt::Dirs::livedir() const -> const std::string & { return livedir_; }

auto tt::Dirs::logdir() const -> const std::string & { return logdir_; }

auto tt::Dirs::servicedir() const -> const std::string & { return servicedir_; }

auto tt::Dirs::statedir() const -> const std::string & { return statedir_; }
