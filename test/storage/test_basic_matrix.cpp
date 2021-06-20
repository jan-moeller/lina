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

TEMPLATE_LIST_TEST_CASE("Matrix properties", "[storage]", test_types)
{
    SECTION("Matrix is an aggregate")
    {
        static_assert(std::is_aggregate_v<TestType>);
        CHECK(std::is_aggregate_v<TestType>);
    }
    SECTION("Matrix is trivially default constructible")
    {
        static_assert(std::is_trivially_default_constructible_v<TestType>);
        CHECK(std::is_trivially_default_constructible_v<TestType>);
    }
    SECTION("Matrix is nothrow default constructible")
    {
        static_assert(std::is_nothrow_default_constructible_v<TestType>);
        CHECK(std::is_nothrow_default_constructible_v<TestType>);
    }
    SECTION("Matrix is trivially copy constructible")
    {
        static_assert(std::is_trivially_copy_constructible_v<TestType>);
        CHECK(std::is_trivially_copy_constructible_v<TestType>);
    }
    SECTION("Matrix is nothrow copy constructible")
    {
        static_assert(std::is_nothrow_copy_constructible_v<TestType>);
        CHECK(std::is_nothrow_copy_constructible_v<TestType>);
    }
    SECTION("Matrix is trivially move constructible")
    {
        static_assert(std::is_trivially_move_constructible_v<TestType>);
        CHECK(std::is_trivially_move_constructible_v<TestType>);
    }
    SECTION("Matrix is nothrow move constructible")
    {
        static_assert(std::is_nothrow_move_constructible_v<TestType>);
        CHECK(std::is_nothrow_move_constructible_v<TestType>);
    }
    SECTION("Matrix is trivially copy assignable")
    {
        static_assert(std::is_trivially_copy_assignable_v<TestType>);
        CHECK(std::is_trivially_copy_assignable_v<TestType>);
    }
    SECTION("Matrix is nothrow copy assignable")
    {
        static_assert(std::is_nothrow_copy_assignable_v<TestType>);
        CHECK(std::is_nothrow_copy_assignable_v<TestType>);
    }
    SECTION("Matrix is trivially move assignable")
    {
        static_assert(std::is_trivially_move_assignable_v<TestType>);
        CHECK(std::is_trivially_move_assignable_v<TestType>);
    }
    SECTION("Matrix is nothrow move assignable")
    {
        static_assert(std::is_nothrow_move_assignable_v<TestType>);
        CHECK(std::is_nothrow_move_assignable_v<TestType>);
    }
    SECTION("Matrix is trivially destructible")
    {
        static_assert(std::is_trivially_destructible_v<TestType>);
        CHECK(std::is_trivially_destructible_v<TestType>);
    }
    SECTION("Matrix is nothrow destructible")
    {
        static_assert(std::is_nothrow_destructible_v<TestType>);
        CHECK(std::is_nothrow_destructible_v<TestType>);
    }
    SECTION("Matrix is nothrow swappable")
    {
        static_assert(std::is_nothrow_swappable_v<TestType>);
        CHECK(std::is_nothrow_swappable_v<TestType>);
    }
    SECTION("Matrix is equality comparable")
    {
        static_assert(std::equality_comparable<TestType>);
        CHECK(std::equality_comparable<TestType>);
    }
    SECTION("Iterators are random access")
    {
        static_assert(std::random_access_iterator<typename TestType::const_iterator>);
        static_assert(std::random_access_iterator<typename TestType::iterator>);
        static_assert(std::random_access_iterator<typename TestType::const_reverse_iterator>);
        static_assert(std::random_access_iterator<typename TestType::reverse_iterator>);
        CHECK(std::random_access_iterator<typename TestType::const_iterator>);
        CHECK(std::random_access_iterator<typename TestType::iterator>);
        CHECK(std::random_access_iterator<typename TestType::const_reverse_iterator>);
        CHECK(std::random_access_iterator<typename TestType::reverse_iterator>);
    }
    SECTION("Matrix fulfills the is_matrix concept")
    {
        static_assert(is_matrix<TestType>);
        CHECK(is_matrix<TestType>);
    }
}

TEMPLATE_LIST_TEST_CASE("Matrix has static members that report rows, columns and total elements",
                        "[storage]",
                        test_types)
{
    static_assert(TestType::size() == TestType::dim.rows * TestType::dim.cols);
    CHECK(TestType::size() == TestType::dim.rows * TestType::dim.cols);
}

TEMPLATE_LIST_TEST_CASE("Can store and retrieve elements from matrix", "[storage]", test_types)
{
    using index_t = typename TestType::size_type;
    SECTION("forward")
    {
        TestType m;
        std::iota(m.begin(), m.end(), 0);
        CAPTURE(m);
        CHECK(
            std::equal(m.begin(), m.end(), std::views::iota(index_t{0}, TestType::size()).begin()));
    }
    SECTION("backward")
    {
        TestType m;
        std::iota(m.rbegin(), m.rend(), 0);
        CAPTURE(m);
        CHECK(std::equal(m.rbegin(),
                         m.rend(),
                         std::views::iota(index_t{0}, TestType::size()).begin()));
    }
    SECTION("const forward")
    {
        TestType const m = []
        {
            TestType mat;
            std::iota(mat.begin(), mat.end(), 0);
            return mat;
        }();
        CAPTURE(m);
        CHECK(
            std::equal(m.begin(), m.end(), std::views::iota(index_t{0}, TestType::size()).begin()));
    }
    SECTION("const backward")
    {
        TestType const m = []
        {
            TestType mat;
            std::iota(mat.rbegin(), mat.rend(), 0);
            return mat;
        }();
        CAPTURE(m);
        CHECK(std::equal(m.rbegin(),
                         m.rend(),
                         std::views::iota(index_t{0}, TestType::size()).begin()));
    }
}

TEST_CASE("Matrices can be compared for equality", "[storage]")
{
    basic_matrix<double, {3, 3}> m1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    basic_matrix<double, {3, 3}> m2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    basic_matrix<double, {3, 3}> m3{1, 1, 1, 1, 1, 1, 1, 1, 1};

    CHECK(m1 == m2);
    CHECK(m1 != m3);
}
