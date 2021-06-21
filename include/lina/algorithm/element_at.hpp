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

#ifndef LINA_ELEMENT_AT_HPP
#define LINA_ELEMENT_AT_HPP

#include "lina/concepts/matrix.hpp"

namespace lina
{
template<matrix M>
constexpr auto element_at(M const& m, index_t i) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    return A::get(m, i);
}

template<matrix M>
constexpr auto element_at(M& m, index_t i) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    return A::get(m, i);
}

template<matrix M>
constexpr auto element_at(M const& m, column_t c, row_t r) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    return A::get(m, A::index(m, c, r));
}

template<matrix M>
constexpr auto element_at(M& m, column_t c, row_t r) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    return A::get(m, A::index(m, c, r));
}
} // namespace lina

#endif // LINA_ELEMENT_AT_HPP
