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

#ifndef LINA_COLUMN_MAJOR_ITERATOR_HPP
#define LINA_COLUMN_MAJOR_ITERATOR_HPP

#include "lina/concepts/detail/shorthand.hpp"
#include "lina/concepts/matrix.hpp"
#include "lina/types/detail/coordinate_index_conversion.hpp"
#include "lina/types/detail/index_iterator.hpp"

namespace lina
{
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
using column_major_iterator = detail::index_iterator<M, detail::index_to_column_major_t>;

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
using column_major_const_iterator = detail::index_iterator<M const, detail::index_to_column_major_t>;

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_begin(M& m) noexcept -> decltype(auto)
{
    return column_major_iterator<M>{&m, 0};
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_end(M& m) noexcept -> decltype(auto)
{
    return column_major_iterator<M>{&m, m.size()};
}

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_begin(M const& m) noexcept -> decltype(auto)
{
    return make_column_major_cbegin(m);
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_end(M const& m) noexcept -> decltype(auto)
{
    return make_column_major_cend(m);
}

template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_cbegin(M const& m) noexcept -> decltype(auto)
{
    return column_major_const_iterator<M>{&m, 0};
}
template<typename M>
    requires matrix<std::remove_cvref_t<M>>
constexpr auto make_column_major_cend(M const& m) noexcept -> decltype(auto)
{
    return column_major_const_iterator<M>{&m, m.size()};
}
} // namespace lina

#endif // LINA_COLUMN_MAJOR_ITERATOR_HPP
