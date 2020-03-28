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

#ifndef LIBTT_BUNDLE_HPP_
#define LIBTT_BUNDLE_HPP_

#include <istream>

#include "libtt/data/bundle_options.hpp"
#include "libtt/data/service.hpp"

namespace tt {

class Bundle : public Service {
public:
    Bundle(const std::string name, const std::string polish_name,
           const std::string description, const std::string path,
           BundleOptions &options)
        : Service(name, polish_name, description, path, options) {}

    std::ostream &dump(std::ostream &oss) const {
        Service::dump(oss);
        oss << "[main]\n"
            << "\ntype = bundle";
        return oss << "\n\n[options]\n" << options();
    }
};

} // namespace tt

#endif // LIBTT_BUNDLE_HPP_