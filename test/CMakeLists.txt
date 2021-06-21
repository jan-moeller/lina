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

include(FetchContent)
fetchcontent_declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.6)
fetchcontent_makeavailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/contrib)

add_executable(lina-tests
        algorithm/test_element_at.cpp
        algorithm/test_fill.cpp
        algorithm/test_for_each.cpp
        algorithm/test_for_each_index.cpp
        algorithm/test_make_diagonal.cpp
        algorithm/test_make_identity.cpp
        algorithm/test_make_one.cpp
        algorithm/test_make_zero.cpp
        algorithm/test_matrix_product.cpp
        algorithm/test_negate.cpp
        algorithm/test_sum.cpp
        algorithm/test_trace.cpp
        concepts/test_concepts.cpp
        storage/test_basic_matrix.cpp
        test_main.cpp
        )
target_link_libraries(lina-tests PRIVATE Catch2::Catch2 lina)
set_target_properties(lina-tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

include(CTest)
include(Catch)
catch_discover_tests(lina-tests)