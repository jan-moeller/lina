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

#ifndef LINA_MATRIX_PRODUCT_COMPATIBLE_HPP
#define LINA_MATRIX_PRODUCT_COMPATIBLE_HPP

#include "lina/concepts/matrix.hpp"
#include "utility.hpp"

namespace lina::detail
{
template<matrix...>
struct matrix_product_compatible;

template<matrix M>
struct matrix_product_compatible<M>
{
    static constexpr bool value = true;
};

template<matrix Lhs, matrix Rhs>
struct matrix_product_compatible<Lhs, Rhs>
{
    static constexpr bool value = cols<Lhs> == rows<Rhs>;
};

template<matrix Lhs, matrix Rhs, matrix... More>
struct matrix_product_compatible<Lhs, Rhs, More...>
{
    static constexpr bool value = matrix_product_compatible<Lhs, Rhs>::value
                                  && matrix_product_compatible<Rhs, More...>::value;
};

template<matrix... Ms>
constexpr bool matrix_product_compatible_v = matrix_product_compatible<Ms...>::value;
} // namespace lina::detail

#endif // LINA_MATRIX_PRODUCT_COMPATIBLE_HPP
