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
#include <ranges>
#include <tuple>

using namespace lina;

using test_types = std::tuple<basic_matrix<double, {0, 0}>,
                              basic_matrix<double, {1, 0}>,
                              basic_matrix<double, {0, 1}>,
                              basic_matrix<double, {1, 1}>,
                              basic_matrix<double, {2, 1}>,
                              basic_matrix<double, {3, 1}>,
                              basic_matrix<double, {4, 1}>,
                              basic_matrix<double, {5, 1}>,
                              basic_matrix<double, {4, 4}>>;

TEMPLATE_LIST_TEST_CASE("native_iterator traverses all elements", "[types]", test_types)
{
    SECTION("on const matrix")
    {
        TestType const mc = []
        {
            TestType mat;
            std::iota(mat.begin(), mat.end(), 0);
            return mat;
        }();
        auto const begin = make_native_order_begin(mc);
        auto const end   = make_native_order_end(mc);
        CAPTURE(mc, std::ranges::subrange(begin, end));
        CHECK(std::equal(begin, end, mc.begin()));
    }
    TestType m = []
    {
        TestType mat;
        std::iota(mat.begin(), mat.end(), 0);
        return mat;
    }();
    SECTION("const_iterator on mutable matrix")
    {
        auto const begin = make_native_order_cbegin(m);
        auto const end   = make_native_order_cend(m);
        CAPTURE(m, std::ranges::subrange(begin, end));
        CHECK(std::equal(begin, end, m.begin()));
    }
    SECTION("iterator on mutable matrix")
    {
        auto const begin = make_native_order_begin(m);
        auto const end   = make_native_order_end(m);
        CAPTURE(m, std::ranges::subrange(begin, end));
        CHECK(std::equal(begin, end, m.begin()));
    }
}