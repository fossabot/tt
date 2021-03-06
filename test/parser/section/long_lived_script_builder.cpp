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

#include "tt/parser/section/long_lived_script_builder.hpp"

#include <cstdint>  // for uint_fast32_t
#include <optional> // for optional

#include "catch2/catch.hpp" // for SourceLineInfo, operator""_...

#include "tt/data/long_lived_script.hpp" // for LongLivedScript
#include "tt/parser/section/utils.hpp"   // for TestBuilderWithFile

TEST_CASE("LongLivedScriptBuilder") {
    auto builder = tt::LongLivedScriptBuilder("test");
    SECTION("Parse valid script section") {
        TestBuilderWithFile(builder, "../test/data/long_lived_script_section");
        tt::LongLivedScript s = builder.long_lived_script();

        CHECK(s.notify());
        CHECK(s.notify().value() == 3);
    }

    SECTION("Parse invalid line") {
        REQUIRE_THROWS(builder.ParseLine("invalid"));
    }
}
