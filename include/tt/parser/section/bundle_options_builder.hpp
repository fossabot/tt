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

#ifndef TT_BUNDLE_OPTION_BUILDER_HPP_
#define TT_BUNDLE_OPTION_BUILDER_HPP_

#include <string> // for string

#include "tt/data/bundle_options.hpp"            // for BundleOptions
#include "tt/parser/section/options_builder.hpp" // for OptionsBuilder

namespace tt {
class ArrayParser;
class BundleOptions;

class BundleOptionsBuilder : public OptionsBuilder {
public:
    BundleOptionsBuilder() = default;

    [[nodiscard]] auto options() -> BundleOptions &&;

    void EndParsing() override;
    void ParseLine(const std::string &line) override;

protected:
    void SaveValuesOfParser(const ArrayParser &parser) override;
    void TrySetAttributeForKey(const std::string &key,
                               const std::string &value) override;

private:
    BundleOptions options_;
};

} // namespace tt

#endif // TT_BUNDLE_OPTION_BUILDER_HPP_
