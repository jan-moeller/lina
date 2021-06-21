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

TEST_CASE("scalar_product", "[algorithm]")
{
    constexpr basic_matrix<double, {3, 2}> m{1, 2, 3, 4, 5, 6};
    constexpr basic_matrix<double, {3, 2}> expected{3, 6, 9, 12, 15, 18};
    constexpr float                        scalar = 3;

    SECTION("copy")
    {
        auto const result1 = scalar_product(scalar, m);
        auto const result2 = scalar_product(m, scalar);
        CHECK(result1 == expected);
        CHECK(result1 == result2);
    }
    SECTION("in place")
    {
        auto m1 = m;
        auto m2 = m;
        scalar_product(std::in_place, scalar, m1);
        scalar_product(std::in_place, m2, scalar);
        CHECK(m1 == expected);
        CHECK(m1 == m2);
    }
}