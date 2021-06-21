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
        include/lina/algorithm/detail/lazy_matrix_product_evaluator.hpp
        include/lina/algorithm/detail/matrix_product_compatible.hpp
        include/lina/algorithm/detail/matrix_product_result_type.hpp
        include/lina/algorithm/detail/utility.hpp
        include/lina/algorithm/element_at.hpp
        include/lina/algorithm/fill.hpp
        include/lina/algorithm/for_each.hpp
        include/lina/algorithm/for_each_index.hpp
        include/lina/algorithm/hadamard_division.hpp
        include/lina/algorithm/hadamard_product.hpp
        include/lina/algorithm/make_diagonal.hpp
        include/lina/algorithm/make_identity.hpp
        include/lina/algorithm/make_one.hpp
        include/lina/algorithm/make_zero.hpp
        include/lina/algorithm/matrix_ostream.hpp
        include/lina/algorithm/matrix_product.hpp
        include/lina/algorithm/negate.hpp
        include/lina/algorithm/scalar_product.hpp
        include/lina/algorithm/sum.hpp
        include/lina/algorithm/trace.hpp
        include/lina/concepts/concepts.hpp
        include/lina/concepts/matrix.hpp
        include/lina/concepts/matrix_dimension.hpp
        include/lina/concepts/same_dimension.hpp
        include/lina/concepts/square_matrix.hpp
        include/lina/concepts/types.hpp
        include/lina/concepts/vector.hpp
        include/lina/lina.hpp
        include/lina/storage/basic_matrix.hpp
        include/lina/storage/detail/coordinate_index_conversion.hpp
        include/lina/storage/detail/index_iterator.hpp
        include/lina/storage/detail/launder_const_iterator.hpp
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