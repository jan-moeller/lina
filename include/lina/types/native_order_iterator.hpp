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

#ifndef LINA_NATIVE_ORDER_ITERATOR_HPP
#define LINA_NATIVE_ORDER_ITERATOR_HPP

#include "lina/concepts/detail/shorthand.hpp"
#include "lina/concepts/matrix.hpp"
#include "lina/types/detail/index_iterator.hpp"

namespace lina
{
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
using native_order_iterator = std::conditional_t<detail::native_matrix<std::remove_cvref_t<M>>,
                                                 typename std::remove_cvref_t<M>::iterator,
                                                 typename detail::index_iterator<M>>;

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
using native_order_const_iterator = std::conditional_t<
    detail::native_matrix<std::remove_cvref_t<M>>,
    typename std::remove_cvref_t<M>::const_iterator,
    typename detail::index_iterator<M const>>;

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_begin(M& m) noexcept -> decltype(auto)
{
    if constexpr (std::ranges::range<M>)
        return m.begin();
    else
        return native_order_iterator<M>{&m, 0};
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_end(M& m) noexcept -> decltype(auto)
{
    if constexpr (std::ranges::range<M>)
        return m.end();
    else
        return native_order_iterator<M>{&m, m.size()};
}

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_begin(M const& m) noexcept -> decltype(auto)
{
    return make_native_order_cbegin(m);
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_end(M const& m) noexcept -> decltype(auto)
{
    return make_native_order_cend(m);
}

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_cbegin(M const& m) noexcept -> decltype(auto)
{
    if constexpr (std::ranges::range<M>)
        return m.cbegin();
    else
        return native_order_iterator<M>{&m, 0};
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_native_order_cend(M const& m) noexcept -> decltype(auto)
{
    if constexpr (std::ranges::range<M>)
        return m.cend();
    else
        return native_order_iterator<M>{&m, m.size()};
}
} // namespace lina

namespace std
{
constexpr auto begin(lina::matrix auto& m) noexcept
{
    return lina::make_native_order_begin(m);
}
constexpr auto begin(lina::matrix auto const& m) noexcept
{
    return lina::make_native_order_begin(m);
}
constexpr auto cbegin(lina::matrix auto const& m) noexcept
{
    return lina::make_native_order_cbegin(m);
}

constexpr auto end(lina::matrix auto& m) noexcept
{
    return lina::make_native_order_end(m);
}
constexpr auto end(lina::matrix auto const& m) noexcept
{
    return lina::make_native_order_end(m);
}
constexpr auto cend(lina::matrix auto const& m) noexcept
{
    return lina::make_native_order_cend(m);
}
} // namespace std

#endif // LINA_NATIVE_ORDER_ITERATOR_HPP
