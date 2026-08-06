# @file      CMakeLists.txt
# @brief     Rush project CMakeLists file
#
# Copyright (C) Witekio
#
# This file is part of the Zephyr Rush demonstration.
#
# This demonstration is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This demonstration is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with This demonstration. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES "src/*.h" "src/*.c" "src/*.cpp")
target_sources(app PRIVATE ${SOURCES})

target_include_directories(app PRIVATE src)

include(cmake/Version.cmake)
