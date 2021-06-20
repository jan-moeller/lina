//
// MIT License
//
// Copyright (c) 2021 Jan Möller
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "lina/lina.hpp"

#include <catch2/catch.hpp>

using namespace lina;

TEMPLATE_TEST_CASE("for_each_index",
                   "[algorithm]",
                   (basic_matrix<double, {3, 3}>),
                   (basic_matrix<double, {3, 3}> const))
{
    using M = std::remove_cvref_t<TestType>;
    SECTION("any order")
    {
        TestType m{1, 2, 3, 4, 5, 6, 7, 8, 9};
        for_each_index<M>([&, d = 1.](index_type i) mutable { CHECK(m[i] == d++); });
    }
    SECTION("row-major")
    {
        TestType m{1, 2, 3, 4, 5, 6, 7, 8, 9};
        for_each_index<M, traversal_order::row_major>([&, d = 1.](column_type c, row_type r) mutable
                                                      { CHECK(m(c, r) == d++); });
    }
    SECTION("column-major")
    {
        TestType m{1, 4, 7, 2, 5, 8, 3, 6, 9};
        for_each_index<M, traversal_order::column_major>(
            [&, d = 1.](column_type c, row_type r) mutable { CHECK(m(c, r) == d++); });
    }
}