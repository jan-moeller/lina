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

template<typename M>
constexpr bool can_compute_trace = requires(M m)
{
    trace(m);
};

TEST_CASE("trace", "[algorithm]")
{
    SECTION("empty matrix")
    {
        basic_matrix<double, {0, 0}> m{};
        CHECK(trace(m) == 0);
    }
    SECTION("square matrix")
    {
        basic_matrix<double, {3, 3}> m{2, 7, 6, 9, 5, 1, 4, 3, 8};
        CHECK(trace(m) == 15);
    }
    SECTION("non-square matrix")
    {
        SECTION("wide")
        {
            static_assert(!can_compute_trace<basic_matrix<double, {3, 2}>>);
            CHECK(!can_compute_trace<basic_matrix<double, {3, 2}>>);
        }
        SECTION("tall")
        {
            static_assert(!can_compute_trace<basic_matrix<double, {2, 3}>>);
            CHECK(!can_compute_trace<basic_matrix<double, {2, 3}>>);
        }
    }
}