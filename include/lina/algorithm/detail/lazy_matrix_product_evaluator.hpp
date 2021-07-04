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

#ifndef LINA_LAZY_MATRIX_PRODUCT_EVALUATOR_HPP
#define LINA_LAZY_MATRIX_PRODUCT_EVALUATOR_HPP

#include "lina/algorithm/element_at.hpp"
#include "lina/concepts/detail/shorthand.hpp"
#include "lina/concepts/matrix.hpp"
#include "matrix_product_result_type.hpp"

namespace lina::detail
{
template<matrix... Ms>
struct lazy_matrix_product_evaluator;

template<matrix M>
struct lazy_matrix_product_evaluator<M>
{
    using result_type = typename matrix_product_result_type<M>::type;
    constexpr explicit lazy_matrix_product_evaluator(M const& m) noexcept
        : m_mat{m}
    {
    }
    constexpr auto operator()(column_t col, row_t row) const noexcept
    {
        return element_at(m_mat, {col, row});
    }

    M const& m_mat;
};

template<matrix Lhs, matrix... Rhs>
struct lazy_matrix_product_evaluator<Lhs, Rhs...>
{
    using result_type = typename matrix_product_result_type<Lhs, Rhs...>::type;
    constexpr explicit lazy_matrix_product_evaluator(Lhs const& lhs, Rhs const&... rhs) noexcept
        : m_lhs{lhs}
        , m_rhs{rhs...}
    {
    }
    constexpr auto operator()(column_t col, row_t row) const noexcept
    {
        using value_t = value_type<result_type>;
        value_t sum   = 0;
        for (row_t r = 0; r < cols<Lhs>; ++r)
            sum += element_at(m_lhs, {r, row}) * m_rhs(col, r);
        return sum;
    }

    Lhs const&                            m_lhs;
    lazy_matrix_product_evaluator<Rhs...> m_rhs;
};
} // namespace lina::detail

#endif // LINA_LAZY_MATRIX_PRODUCT_EVALUATOR_HPP
