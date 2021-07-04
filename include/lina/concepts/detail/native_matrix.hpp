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

#ifndef LINA_NATIVE_MATRIX_HPP
#define LINA_NATIVE_MATRIX_HPP

#include "lina/concepts/concept_types.hpp"
#include "lina/concepts/matrix_adapter.hpp"
#include "shorthand.hpp"

#include <concepts>
#include <ranges>
#include <type_traits>

namespace lina
{

namespace detail
{
template<typename M>
concept native_matrix = requires(M const& mc, M& mm)
{
    // clang-format off
    typename detail::nvalue_type<M>;
    { detail::ndim<M> } -> std::convertible_to<dimension_t>;
    { mc[std::declval<index_t>()] } -> std::convertible_to<detail::nvalue_type<M> const&>;
    { mc[std::declval<index2_t>()] } -> std::convertible_to<detail::nvalue_type<M> const&>;
    { mm[std::declval<index_t>()] } -> std::convertible_to<detail::nvalue_type<M>&>;
    { mm[std::declval<index2_t>()] } -> std::convertible_to<detail::nvalue_type<M>&>;
    std::ranges::contiguous_range<M>;
    // clang-format on
};
} // namespace detail

template<detail::native_matrix M>
struct matrix_adapter<M>
{
    using value_type                 = typename M::value_type;
    static constexpr dimension_t dim = M::dim;

    static constexpr auto get(M const& m, index_t i) noexcept -> decltype(auto) { return m[i]; }
    static constexpr auto get(M& m, index_t i) noexcept -> decltype(auto) { return m[i]; }
    static constexpr auto get(M const& m, index2_t i) noexcept -> decltype(auto) { return m[i]; }
    static constexpr auto get(M& m, index2_t i) noexcept -> decltype(auto) { return m[i]; }
};
} // namespace lina

#endif // LINA_NATIVE_MATRIX_HPP
