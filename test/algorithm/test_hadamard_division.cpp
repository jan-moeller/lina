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

TEST_CASE("hadamard_division", "[algorithm]")
{
    basic_matrix<double, {3, 2}> m1{1, 2, 3, 4, 5, 6};
    basic_matrix<double, {3, 2}> m2{1, 2, 1, 2, 1, 3};
    basic_matrix<double, {3, 2}> m3{2, 2, 3, 2, 5, 2};

    auto const result  = hadamard_division(m1, m2, m3);
    auto const result2 = hadamard_division(hadamard_division(m1, m2), m3);
    hadamard_division(std::in_place, m1, m2, m3);
    CHECK(result == basic_matrix<double, {3, 2}>{0.5, 0.5, 1, 1, 1, 1});
    CHECK(result == result2);
    CHECK(m1 == result);
}