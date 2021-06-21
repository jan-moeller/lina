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

#ifndef LINA_MATRIX_PRODUCT_HPP
#define LINA_MATRIX_PRODUCT_HPP

#include "detail/lazy_matrix_product_evaluator.hpp"
#include "detail/matrix_product_compatible.hpp"
#include "detail/matrix_product_result_type.hpp"
#include "lina/algorithm/element_at.hpp"
#include "lina/concepts/matrix.hpp"
#include "lina/concepts/same_dimension.hpp"

#include <array>
#include <utility>

namespace lina
{
template<matrix... Ms>
    requires detail::matrix_product_compatible_v<Ms...>
constexpr auto matrix_product(Ms const&... args) noexcept
    -> detail::matrix_product_result_type<Ms...>::type
{
    using result_t = typename detail::matrix_product_result_type<Ms...>::type;

    detail::lazy_matrix_product_evaluator<Ms...> evaluator{args...};
    result_t                                     result;
    for (row_t row = 0; row < detail::rows<result_t>; ++row)
    {
        for (column_t col = 0; col < detail::cols<result_t>; ++col)
            element_at(result, col, row) = evaluator(col, row);
    }
    return result;
}

template<matrix M, matrix... Ms>
    requires detail::matrix_product_compatible_v<M, Ms...> and
             same_dimension<M, typename detail::matrix_product_result_type<M, Ms...>::type>
constexpr auto matrix_product(std::in_place_t, M& m, Ms const&... args) noexcept -> M&
{
    detail::lazy_matrix_product_evaluator<M, Ms...> evaluator{m, args...};
    for (row_t row = 0; row < detail::rows<M>; ++row)
    {
        std::array<detail::value_type<M>, detail::cols<M>> tmp;
        for (column_t col = 0; col < detail::cols<M>; ++col)
            tmp[col] = evaluator(col, row);
        for (column_t col = 0; col < detail::cols<M>; ++col)
            element_at(m, col, row) = tmp[col];
    }
    return m;
}
} // namespace lina

#endif // LINA_MATRIX_PRODUCT_HPP
