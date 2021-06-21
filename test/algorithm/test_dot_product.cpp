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

template<typename... Ts>
constexpr bool can_dot_product = requires
{
    dot_product(std::declval<Ts>()...);
};

TEST_CASE("dot product", "[algorithm]")
{
    GIVEN("two vectors with compatible dimensions")
    {
        cvec3f rhs{1, 2, 3};
        rvec3d lhs{3, 2, 1};
        WHEN("calling dot_product() with them")
        {
            auto const result = dot_product(lhs, rhs);
            THEN("the result should be correct") { CHECK(result == 10); }
        }
    }
    GIVEN("two vectors with incompatible dimensions")
    {
        THEN("they cannot be matrix-multiplied")
        {
            static_assert(!can_dot_product<basic_matrix<float, {2, 3}>, rvec3d>);
            CHECK(!can_dot_product<basic_matrix<float, {2, 3}>, rvec3d>);

            static_assert(!can_dot_product<cvec3d, rvec3d>);
            CHECK(!can_dot_product<cvec3d, rvec3d>);
        }
    }
}