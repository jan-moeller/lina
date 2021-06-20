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

#ifndef LINA_SUM_HPP
#define LINA_SUM_HPP

#include "for_each_index.hpp"
#include "lina/concepts/concepts.hpp"
#include "lina/storage/basic_matrix.hpp"

namespace lina
{
template<matrix Lhs, matrix... Rhs>
    requires(same_dimension<Lhs, Rhs...>)
constexpr auto sum(Lhs const& lhs, Rhs const&... rhs) noexcept -> matrix auto
{
    using value_t  = std::common_type_t<typename matrix_adapter<Lhs>::value_type,
                                       typename matrix_adapter<Rhs>::value_type...>;
    using result_t = basic_matrix<value_t, matrix_adapter<Lhs>::dim>;
    result_t result{lhs};

    auto&& adder = [&](index_t i)
    {
        matrix_adapter<result_t>::get(result, i) += (matrix_adapter<Rhs>::get(rhs, i) + ...);
    };
    for_each_index<result_t>(adder);
    return result;
}
} // namespace lina

#endif // LINA_SUM_HPP
