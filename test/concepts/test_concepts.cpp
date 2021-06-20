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

TEMPLATE_TEST_CASE("matrix concept (success-test)",
                   "[concepts]",
                   (basic_matrix<double, {0, 0}>),
                   (basic_matrix<double, {1, 1}>),
                   (basic_matrix<float, {1, 3}>),
                   (basic_matrix<int, {3, 3}>))
{
    static_assert(matrix<TestType>);
    CHECK(matrix<TestType>);
}

TEMPLATE_TEST_CASE("matrix concept (fail-test)", "[concepts]", (double), (std::array<float, 3>))
{
    static_assert(!matrix<TestType>);
    CHECK(!matrix<TestType>);
}

TEMPLATE_TEST_CASE("row_vector concept (success-test)",
                   "[concepts]",
                   (basic_matrix<double, {1, 1}>),
                   (basic_matrix<float, {2, 1}>),
                   (basic_matrix<int, {3, 1}>))
{
    static_assert(row_vector<TestType>);
    CHECK(row_vector<TestType>);
}

TEMPLATE_TEST_CASE("row_vector concept (fail-test)",
                   "[concepts]",
                   (double),
                   (std::array<float, 3>),
                   (basic_matrix<double, {0, 0}>),
                   (basic_matrix<double, {0, 1}>),
                   (basic_matrix<double, {2, 2}>))
{
    static_assert(!row_vector<TestType>);
    CHECK(!row_vector<TestType>);
}

TEMPLATE_TEST_CASE("column_vector concept (success-test)",
                   "[concepts]",
                   (basic_matrix<double, {1, 1}>),
                   (basic_matrix<float, {1, 2}>),
                   (basic_matrix<int, {1, 3}>))
{
    static_assert(column_vector<TestType>);
    CHECK(column_vector<TestType>);
}

TEMPLATE_TEST_CASE("column_vector concept (fail-test)",
                   "[concepts]",
                   (double),
                   (std::array<float, 3>),
                   (basic_matrix<double, {0, 0}>),
                   (basic_matrix<double, {1, 0}>),
                   (basic_matrix<double, {2, 2}>))
{
    static_assert(!column_vector<TestType>);
    CHECK(!column_vector<TestType>);
}