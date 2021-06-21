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

#ifndef LINA_SCALAR_DIVISION_HPP
#define LINA_SCALAR_DIVISION_HPP

#include "detail/utility.hpp"
#include "for_each.hpp"
#include "lina/concepts/concepts.hpp"
#include "lina/storage/basic_matrix.hpp"

#include <utility>

namespace lina
{
template<matrix Lhs, typename Rhs>
constexpr auto scalar_division(Lhs const& lhs, Rhs const& rhs) noexcept -> matrix auto
{
    using value_t  = std::common_type_t<detail::value_type<Lhs>, Rhs>;
    using result_t = basic_matrix<value_t, detail::dim<Lhs>>;
    result_t result{lhs};
    return scalar_division(std::in_place, result, rhs);
}

template<typename Lhs, matrix Rhs>
constexpr auto scalar_division(Lhs const& lhs, Rhs const& rhs) noexcept -> matrix auto
{
    using value_t  = std::common_type_t<detail::value_type<Rhs>, Lhs>;
    using result_t = basic_matrix<value_t, detail::dim<Rhs>>;
    result_t result{rhs};
    return scalar_division(std::in_place, lhs, result);
}

template<matrix Lhs, typename Rhs>
constexpr auto scalar_division(std::in_place_t, Lhs& lhs, Rhs const& rhs) noexcept -> Lhs&
{
    for_each(lhs, [&](detail::value_type<Lhs>& v) { v /= rhs; });
    return lhs;
}

template<typename Lhs, matrix Rhs>
constexpr auto scalar_division(std::in_place_t, Lhs const& lhs, Rhs& rhs) noexcept -> Rhs&
{
    for_each(rhs, [&](detail::value_type<Rhs>& v) { v = lhs / v; });
    return rhs;
}
} // namespace lina

#endif // LINA_SCALAR_DIVISION_HPP
