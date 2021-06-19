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

#ifndef LINA_LAUNDER_CONST_ITERATOR_HPP
#define LINA_LAUNDER_CONST_ITERATOR_HPP

#include "index_iterator.hpp"

#include <type_traits>

namespace lina::detail
{
template<typename Iter>
    requires(std::is_pointer_v<Iter>)
constexpr auto launder_const_iterator(Iter iter) noexcept
{
    using T = std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<Iter>>>;
    return const_cast<T>(iter);
}

template<typename Iter>
    requires(std::is_pointer_v<Iter>)
constexpr auto launder_const_iterator(std::reverse_iterator<Iter> iter) noexcept
{
    return std::make_reverse_iterator(launder_const_iterator(iter.base()));
}

template<typename ContainerPtr>
    requires(std::is_pointer_v<ContainerPtr>)
constexpr auto launder_const_iterator(index_iterator<ContainerPtr> iter) noexcept
{
    auto const ptr  = iter.container();
    using T         = std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<ContainerPtr>>>;
    auto const mptr = const_cast<T>(ptr);
    return index_iterator(mptr, iter.index());
}

template<typename ContainerPtr>
    requires(std::is_pointer_v<ContainerPtr>)
constexpr auto
launder_const_iterator(std::reverse_iterator<index_iterator<ContainerPtr>> iter) noexcept
{
    return std::make_reverse_iterator(launder_const_iterator(iter.base()));
}
} // namespace lina::detail

#endif // LINA_LAUNDER_CONST_ITERATOR_HPP
