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

#ifndef LINA_FOR_EACH_ZIPPED_HPP
#define LINA_FOR_EACH_ZIPPED_HPP

#include "lina/concepts/concepts.hpp"
#include "lina/types/row_major_iterator.hpp"

#include <concepts>
#include <utility>

namespace lina
{
template<typename Lhs,
         typename... Rhs,
         std::invocable<detail::value_type<std::remove_cvref_t<Lhs>>&,
                        detail::value_type<std::remove_cvref_t<Rhs>>&...> Fn>
    // clang-format off
    requires (matrix<std::remove_cvref_t<Lhs>>
         and (matrix<std::remove_cvref_t<Rhs>> and ...)
         and same_dimension<std::remove_cvref_t<Lhs>, std::remove_cvref_t<Rhs>...>)
// clang-format on
constexpr auto for_each_zipped(Fn&& fn, Lhs&& lhs, Rhs&&... rhs) noexcept -> Fn
{
    auto&& internal_fn = [&](auto& lhs_iter, auto&... rhs_iter)
    {
        fn(*lhs_iter, *rhs_iter...);
        ++lhs_iter;
        (++rhs_iter, ...);
    };
    // TODO: row-major order might not be optimal in all cases. Introduce mechanism to choose
    // optimal order in terms of the arguments?
    auto       lhs_iter = make_row_major_begin(lhs);
    auto const lhs_end  = make_row_major_end(lhs);
    auto       iters    = std::make_tuple(std::ref(lhs_iter), make_row_major_begin(rhs)...);
    while (lhs_iter != lhs_end)
        std::apply(internal_fn, iters);
    return std::forward<Fn>(fn);
}
} // namespace lina

#endif // LINA_FOR_EACH_ZIPPED_HPP
