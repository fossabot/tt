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

#include "tt/parser/section/environment_builder.hpp"

#include <map>

#include "catch2/catch.hpp"

#include "tt/parser/section/utils.hpp"

using std::map;
using std::string;

using tt::Environment;
using tt::EnvironmentBuilder;

TEST_CASE("EnvironmentBuilder") {
    Environment e;
    auto builder = EnvironmentBuilder(e);

    SECTION("Parse valid section") {
        TestBuilderWithFile(builder, "../test/data/environment_section");
        map<string, string> expected;
        expected["CMDARGS"] = "-d --nofork";
        expected["LOGLEVEL"] = "0";
        for (auto &pair : expected) {
            CHECK(e.Get(pair.first) == pair.second);
        }
    }

    SECTION("Parse invalid section") {
        CHECK_THROWS(TestBuilderWithFile(builder, "../test/data/invalid"));
        CHECK_THROWS(
            TestBuilderWithFile(builder, "../test/data/invalid_environment"));
    }
}