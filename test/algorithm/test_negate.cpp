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

TEMPLATE_TEST_CASE("negate",
                   "[algorithm]",
                   (basic_matrix<double, {3, 2}>),
                   (basic_matrix<double, {3, 2}> const))
{
    TestType m{1, 2, 3, 4, 5, 6};

    constexpr basic_matrix<double, {3, 2}> expected{-1, -2, -3, -4, -5, -6};

    auto const result = negate(m);
    CHECK(result == expected);

    if constexpr (std::is_const_v<TestType>)
    {
        static_assert(!requires(TestType t) { negate(std::in_place, t); });
        CHECK(!requires(TestType t) { negate(std::in_place, t); });
    }
    else
    {
        negate(std::in_place, m);
        CHECK(m == expected);
    }
}
