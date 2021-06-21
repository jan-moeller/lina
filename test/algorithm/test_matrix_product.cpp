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
constexpr bool can_matrix_product = requires
{
    matrix_product(std::declval<Ts>()...);
};

template<typename... Ts>
constexpr bool can_matrix_product_inplace = requires
{
    matrix_product(std::in_place, std::declval<Ts>()...);
};

TEST_CASE("matrix product", "[linalg]")
{
    GIVEN("two matrices with compatible dimensions")
    {
        basic_matrix<float, {3, 2}>  m1{1, 2, 3, 4, 5, 6};
        basic_matrix<double, {4, 3}> m2{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
        WHEN("calling matrix_product() with them")
        {
            auto const result = matrix_product(m1, m2);
            THEN("the result should be correct")
            {
                REQUIRE(result == basic_matrix<double, {4, 2}>{6, 12, 18, 24, 15, 30, 45, 60});
            }
        }
    }
    GIVEN("three matrices with compatible dimensions")
    {
        basic_matrix<float, {3, 2}>  m1{1, 2, 3, 4, 5, 6};
        basic_matrix<double, {4, 3}> m2{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
        basic_matrix<double, {1, 4}> m3{1, 2, 3, 4};
        WHEN("calling matrix_product() with them")
        {
            auto const result = matrix_product(m1, m2, m3);
            THEN("the result should be correct")
            {
                REQUIRE(result == basic_matrix<double, {1, 2}>{90 * 2, 90 * 5});
            }
        }
    }
    GIVEN("two matrices with incompatible dimensions")
    {
        THEN("they cannot be matrix-multiplied")
        {
            static_assert(
                !can_matrix_product<basic_matrix<float, {2, 3}>, basic_matrix<double, {3, 1}>>);
            CHECK(!can_matrix_product<basic_matrix<float, {2, 3}>, basic_matrix<double, {3, 1}>>);

            static_assert(!can_matrix_product_inplace<basic_matrix<float, {2, 3}>&,
                                                      basic_matrix<double, {3, 1}>>);
            CHECK(!can_matrix_product_inplace<basic_matrix<float, {2, 3}>&,
                                              basic_matrix<double, {3, 1}>>);
        }
    }
    GIVEN("two matrices with compatible dimensions such that they can be multiplied in place")
    {
        basic_matrix<float, {2, 3}>  m1{2, 7, 6, 9, 5, 1};
        basic_matrix<double, {2, 2}> m2{1, 2, 3, 4};
        WHEN("calling matrix_product() with them")
        {
            matrix_product(std::in_place, m1, m2);
            THEN("the result should be correct")
            {
                REQUIRE(m1 == basic_matrix<float, {2, 3}>{23, 32, 33, 48, 8, 14});
            }
        }
    }
    GIVEN("four matrices with compatible dimensions such that they can be multiplied in place")
    {
        basic_matrix<double, {2, 3}> m1{2, 7, 6, 9, 5, 1};
        basic_matrix<double, {2, 2}> m2{1, 2, 3, 4};
        basic_matrix<double, {3, 2}> m3{1, 2, 3, 1, 2, 3};
        basic_matrix<double, {2, 3}> m4{1, 1, 1, 1, 1, 1};
        WHEN("calling matrix_product() with them")
        {
            auto const result = matrix_product(m1, m2, m3, m4);
            matrix_product(std::in_place, m1, m2, m3, m4);
            THEN("the result should be correct")
            {
                CHECK(m1 == result);
                CHECK(m1 == basic_matrix<double, {2, 3}>{6*55, 6*55, 6*81, 6*81, 6*22, 6*22});
            }
        }
    }
}