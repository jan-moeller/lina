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

#ifndef LINA_MATRIX_HPP
#define LINA_MATRIX_HPP

#include "concept_types.hpp"
#include "detail/native_matrix.hpp"
#include "detail/shorthand.hpp"
#include "matrix_adapter.hpp"

#include <concepts>

namespace lina
{
template<typename M>
concept matrix = detail::native_matrix<M> or requires(M const& mc, M& mm)
{
    // clang-format off
    typename detail::value_type<M>;
    { detail::dim<M> } -> std::convertible_to<dimension_t>;
    { detail::ma<M>::get(mc, std::declval<index_t>()) } -> std::convertible_to<detail::value_type<M> const&>;
    { detail::ma<M>::get(mc, std::declval<index2_t>()) } -> std::convertible_to<detail::value_type<M> const&>;
    { detail::ma<M>::get(mm, std::declval<index_t>()) } -> std::convertible_to<detail::value_type<M>&>;
    { detail::ma<M>::get(mm, std::declval<index2_t>()) } -> std::convertible_to<detail::value_type<M>&>;
    // clang-format on
};
} // namespace lina

#endif // LINA_MATRIX_HPP
