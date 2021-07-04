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

#ifndef LINA_MATRIX_PRODUCT_RESULT_TYPE_HPP
#define LINA_MATRIX_PRODUCT_RESULT_TYPE_HPP

#include "lina/concepts/detail/shorthand.hpp"
#include "lina/concepts/matrix.hpp"
#include "lina/types/basic_matrix.hpp"

#include <type_traits>

namespace lina::detail
{
template<matrix... Ms>
struct matrix_product_result_type
{
};

template<matrix M>
struct matrix_product_result_type<M>
{
    using type = M;
};

template<matrix Lhs, matrix Rhs>
struct matrix_product_result_type<Lhs, Rhs>
{
    using type = std::enable_if_t<
        cols<Lhs> == rows<Rhs>,
        basic_matrix<std::common_type_t<value_type<Lhs>, value_type<Rhs>>, {cols<Rhs>, rows<Lhs>}>>;
};

template<matrix Lhs, matrix Rhs, matrix... More>
struct matrix_product_result_type<Lhs, Rhs, More...>
{
    using type = typename matrix_product_result_type<
        typename matrix_product_result_type<Lhs, Rhs>::type,
        More...>::type;
};
} // namespace lina::detail

#endif // LINA_MATRIX_PRODUCT_RESULT_TYPE_HPP
