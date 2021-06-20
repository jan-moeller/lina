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

#ifndef LINA_MAKE_DIAGONAL_HPP
#define LINA_MAKE_DIAGONAL_HPP

#include "lina/algorithm/element_at.hpp"
#include "lina/algorithm/make_zero.hpp"
#include "lina/concepts/concepts.hpp"

#include <algorithm>
#include <array>

namespace lina
{
template<matrix M, std::convertible_to<typename matrix_adapter<M>::value_type>... Us>
constexpr auto make_diagonal(Us... values) noexcept -> M
{
    using A          = matrix_adapter<M>;
    constexpr auto s = std::min(A::dim.rows, A::dim.cols);
    static_assert(sizeof...(Us) == s, "Must pass in exactly the right amount of values");

    std::array<typename A::value_type, s> diag{static_cast<A::value_type>(values)...};

    M m = make_zero<M>();
    for (column_t i = 0; i < s; ++i)
        element_at(m, i, i) = diag[i];
    return m;
}
} // namespace lina

#endif // LINA_MAKE_DIAGONAL_HPP
