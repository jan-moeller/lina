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

TEMPLATE_TEST_CASE("make_identity (success-test)", "[algorithm]", (mat2d), (mat3d), (mat4f))
{
    TestType const m    = make_identity<TestType>();
    auto           iter = make_row_major_begin(m);
    auto const     end  = make_row_major_end(m);
    for (; iter != end; ++iter)
    {
        if (iter.index().row == iter.index().col)
            CHECK(*iter == 1);
        else
            CHECK(*iter == 0);
    }
}

TEMPLATE_TEST_CASE("make_identity (fail-test)",
                   "[algorithm]",
                   (basic_matrix<double, {3, 2}>),
                   (cvec4d))
{

    static_assert(!requires(TestType t) { make_identity<TestType>(); });
    CHECK(!requires(TestType t) { make_identity<TestType>(); });
}