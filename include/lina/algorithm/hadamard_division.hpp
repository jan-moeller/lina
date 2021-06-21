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

#ifndef LINA_HADAMARD_DIVISION_HPP
#define LINA_HADAMARD_DIVISION_HPP

#include "detail/utility.hpp"
#include "for_each_index.hpp"
#include "lina/concepts/concepts.hpp"
#include "lina/storage/basic_matrix.hpp"

#include <utility>

namespace lina
{
template<matrix Lhs, matrix... Rhs>
    requires(same_dimension<Lhs, Rhs...>)
constexpr auto hadamard_division(Lhs const& lhs, Rhs const&... rhs) noexcept -> matrix auto
{
    using value_t  = std::common_type_t<detail::value_type<Lhs>, detail::value_type<Rhs>...>;
    using result_t = basic_matrix<value_t, detail::dim<Lhs>>;
    result_t result{lhs};
    return hadamard_division(std::in_place, result, rhs...);
}

template<matrix Lhs, matrix... Rhs>
    requires(same_dimension<Lhs, Rhs...>)
constexpr auto hadamard_division(std::in_place_t, Lhs& lhs, Rhs const&... rhs) noexcept -> Lhs&
{
    auto&& division = [&](index_t i)
    {
        matrix_adapter<Lhs>::get(lhs, i) /= (matrix_adapter<Rhs>::get(rhs, i) * ...);
    };
    for_each_index<Lhs>(division);
    return lhs;
}
} // namespace lina

#endif // LINA_HADAMARD_DIVISION_HPP
