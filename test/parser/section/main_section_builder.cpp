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

#include "tt/parser/section/main_section_builder.hpp"

#include <vector> // for vector

#include "catch2/catch.hpp" // for operator""_catch_sr

#include "tt/parser/section/main_section.hpp" // for MainSection
#include "tt/parser/section/utils.hpp"        // for TestBuilderWithFile

using std::string;
using tt::MainSection;
using tt::MainSectionBuilder;

TEST_CASE("MainSectionBuilder") {
    MainSectionBuilder builder;

    SECTION("parse valid section") {
        TestBuilderWithFile(builder, "../test/data/main_section");

        CHECK(builder.main_section().name == "nginx");
        CHECK(builder.main_section().description == "Run nginx server");
        CHECK(builder.main_section().type == "longrun");
    }

    SECTION("parse invalid section") {
        const auto testFiles = std::vector<string>{
            "invalid",
            "invalid_quotes",
            "unclosed_quotes",
            "unknown_key",
        };
        for (const string &test : testFiles) {
            CHECK_THROWS(TestBuilderWithFile(builder, "../test/data/" + test));
        }
    }
}
