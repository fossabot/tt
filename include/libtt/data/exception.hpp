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

#ifndef LIBTT_DATA_EXCEPTION_HPP_
#define LIBTT_DATA_EXCEPTION_HPP_

#include <string>

#include "libtt/exception.hpp"

namespace tt {

class MaxDeathTooBigException : public Exception {
public:
    MaxDeathTooBigException()
        : Exception("max_death value cannot be bigger than 4096") {}
};

class ServiceNameDoNotMatchFileExecption : public Exception {
public:
    ServiceNameDoNotMatchFileExecption()
        : Exception("The attribute \"name\" must match the name of the file") {}
};

} // namespace tt

#endif // LIBTT_DATA_EXCEPTION_HPP_
