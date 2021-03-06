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

#include <filesystem>
#include <vector>

namespace tt {

class Dirs {
public:
    virtual ~Dirs() = default;

    [[nodiscard]] virtual auto bindir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto confdir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto libexecdir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto livedir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto logdir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto servicedirs() const
        -> std::vector<std::filesystem::path> = 0;
    [[nodiscard]] virtual auto statedir() const -> std::filesystem::path = 0;
    [[nodiscard]] virtual auto supervisedir() const
        -> std::filesystem::path = 0;

    [[nodiscard]] virtual auto services_suffix() const -> std::string = 0;
};

} // namespace tt
