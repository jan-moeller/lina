#
# MIT License
#
# Copyright (c) 2021 Jan Möller
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required(VERSION 3.20)
project(lina)

add_library(lina
        include/lina/algorithm/algorithm.hpp
        include/lina/algorithm/element_at.hpp
        include/lina/algorithm/matrix_ostream.hpp
        include/lina/algorithm/trace.hpp
        include/lina/concepts/concepts.hpp
        include/lina/concepts/extent.hpp
        include/lina/concepts/is_matrix.hpp
        include/lina/concepts/is_square_matrix.hpp
        include/lina/concepts/types.hpp
        include/lina/lina.hpp
        include/lina/storage/detail/coordinate_index_conversion.hpp
        include/lina/storage/detail/index_iterator.hpp
        include/lina/storage/detail/launder_const_iterator.hpp
        include/lina/storage/matrix.hpp
        )
set_target_properties(lina PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )
set_target_properties(lina PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(lina PUBLIC include/)
target_compile_options(lina PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wduplicated-cond
        -Wno-duplicated-branches
        -Wlogical-op
        -Wnull-dereference
        -Wno-old-style-cast
        -Wuseless-cast
        -Wdouble-promotion
        -Wshadow
        -Wformat=2
        -Wuninitialized
        )

add_subdirectory(test)