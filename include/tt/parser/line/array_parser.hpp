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

#ifndef TT_ARRAY_PARSER_HPP_
#define TT_ARRAY_PARSER_HPP_

#include <string>
#include <vector>

namespace tt {

class ArrayParser {
public:
    [[nodiscard]] auto IsParsing() const noexcept -> bool {
        return is_parsing_;
    }

    [[nodiscard]] auto key() const noexcept -> std::string { return key_; }

    [[nodiscard]] auto values() const noexcept -> std::vector<std::string> {
        return std::vector<std::string>{values_};
    }

    ArrayParser() : key_(""), values_({}) {}

    auto StartParsing(const std::string &line) -> bool;

    void ParseLine(const std::string &line);

    void Reset() {
        values_.clear();
        is_parsing_ = false;
        key_ = "";
    }

private:
    void AddValuesFromLine(const std::string &line);
    void UpdateStatus(const std::string &line);

    // TODO(danyspin97): Make key an Optional
    std::string key_;
    std::vector<std::string> values_;
    bool is_parsing_ = false;
};

} // namespace tt

#endif // TT_ARRAY_PARSER_HPP_
