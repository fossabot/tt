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

#include "tt/parser/service/bundle_director.hpp"

#include <utility> // for move

#include "tt/data/bundle.hpp"                           // for Bundle
#include "tt/data/service.hpp"                          // for Service
#include "tt/exception.hpp"                             // for Exception
#include "tt/parser/section/bundle_options_builder.hpp" // for BundleOption...
#include "tt/parser/section/main_section_builder.hpp"   // for MainSectionB...

namespace tt {
class SectionBuilder;
} // namespace tt

using std::string;

using tt::Bundle;
using tt::BundleDirector;
using tt::Exception;
using tt::SectionBuilder;

auto BundleDirector::InstanceService(string &&path) -> tt::Service {
    auto &main_section = main_section_builder_.main_section();
    return Bundle(std::move(main_section.name),
                  std::move(main_section.description), std::move(path),
                  std::move(options_builder_.options()));
}

auto BundleDirector::GetBuilderForSection(const std::string &section)
    -> SectionBuilder * {
    if (section == "main") {
        return &main_section_builder_;
    }
    if (section == "options") {
        return &options_builder_;
    }
    auto msg = "Section '" + section + "' is not supported.";
    throw Exception(msg);
}
