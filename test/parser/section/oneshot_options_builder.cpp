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

#include "tt/parser/section/oneshot_options_builder.hpp"

#include <vector> // for vector, operator==

#include "catch2/catch.hpp" // for SourceLineInfo, operator""_ca...

#include "tt/data/oneshot_options.hpp" // for OneshotOptions
#include "tt/parser/section/utils.hpp" // for TestBuilderWithFile

namespace tt {
class SectionBuilderException;
} // namespace tt

using std::string;
using std::vector;

using tt::OneshotOptions;
using tt::OneshotOptionsBuilder;
using tt::SectionBuilderException;
using tt::TestBuilderWithFile;

TEST_CASE("OneshotOptionsBuilder") {
    OneshotOptionsBuilder builder;

    SECTION("Parse valid section") {
        TestBuilderWithFile(builder, "../test/data/oneshot_options_section");

        auto expected_deps = vector<string>{"foo", "bar"};
        CHECK(builder.options().optional() == true);
        CHECK(builder.options().dependencies() == expected_deps);
    }

    SECTION("Parse invalid sections") {
        const auto testFiles =
            vector<string>{"empty_multiline_value",    "invalid",
                           "invalid_multiline_value",  "invalid_quotes",
                           "invalid_boolean",          "unclosed_quotes",
                           "unclosed_multiline_value", "unknown_key",
                           "unknown_multiline_value"};
        for (const auto &test : testFiles) {
            CHECK_THROWS_AS(
                TestBuilderWithFile(builder, "../test/data/" + test),
                SectionBuilderException);
        }
    }
}
