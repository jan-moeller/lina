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

#ifndef LINA_INDEX_ITERATOR_HPP
#define LINA_INDEX_ITERATOR_HPP

#include "lina/concepts/matrix.hpp"

#include <concepts>
#include <functional>
#include <iterator>
#include <type_traits>

namespace lina::detail
{
using index_identity = decltype([](index_t i, dimension_t) { return i; });

// clang-format off
template<typename M, std::regular_invocable<index_t, dimension_t> Fn = index_identity>
    requires std::convertible_to<std::invoke_result_t<Fn, index_t, dimension_t>, index_t>
          or std::convertible_to<std::invoke_result_t<Fn, index_t, dimension_t>, index2_t>
// clang-format on
class index_iterator
{
  private:
    using matrix_t = std::remove_const_t<M>;
    using ptr_t    = std::add_pointer_t<M>;
    using index_t  = typename matrix_t::size_type;
    index_t m_idx  = 0;
    ptr_t   m_ptr  = nullptr;

    static_assert(!std::is_pointer_v<M> && !std::is_reference_v<M>,
                  "Template type must be const-qualified matrix type");

  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename matrix_t::value_type;
    using difference_type   = typename matrix_t::difference_type;
    using pointer           = std::conditional_t<std::is_const_v<M>,
                                       typename matrix_t::const_pointer,
                                       typename matrix_t::pointer>;
    using reference         = std::conditional_t<std::is_const_v<M>,
                                         typename matrix_t::const_reference,
                                         typename matrix_t::reference>;

    constexpr index_iterator() noexcept = default;
    constexpr explicit index_iterator(ptr_t ptr, index_t idx = 0) noexcept
        : m_idx{idx}
        , m_ptr{ptr}
    {
    }

    [[nodiscard]] constexpr auto container() const noexcept -> ptr_t { return m_ptr; }
    [[nodiscard]] constexpr auto index() const noexcept -> decltype(auto)
    {
        return Fn{}(m_idx, dim<matrix_t>);
    }

    constexpr auto operator+=(difference_type n) noexcept -> index_iterator&
    {
        m_idx += n;
        return *this;
    }
    friend constexpr auto operator+(index_iterator lhs, difference_type rhs) noexcept
        -> index_iterator
    {
        return lhs += rhs;
    }
    friend constexpr auto operator+(difference_type lhs, index_iterator rhs) noexcept
        -> index_iterator
    {
        return rhs += lhs;
    }

    constexpr auto operator-=(difference_type n) noexcept -> index_iterator&
    {
        m_idx -= n;
        return *this;
    }
    friend constexpr auto operator-(index_iterator lhs, difference_type rhs) noexcept
        -> index_iterator
    {
        return lhs -= rhs;
    }

    friend constexpr auto operator-(index_iterator lhs, index_iterator rhs) noexcept -> difference_t
    {
        return static_cast<difference_t>(lhs.m_idx) - rhs.m_idx;
    }

    constexpr auto operator--() noexcept -> index_iterator&
    {
        *this -= 1;
        return *this;
    }
    constexpr auto operator--(int) noexcept -> index_iterator
    {
        index_iterator cp = *this;
        return --cp;
    }

    constexpr auto operator++() noexcept -> index_iterator&
    {
        *this += 1;
        return *this;
    }
    constexpr auto operator++(int) noexcept -> index_iterator
    {
        index_iterator cp = *this;
        return ++cp;
    }

    constexpr auto operator*() const noexcept -> reference { return (*m_ptr)[index()]; }
    constexpr auto operator->() const noexcept -> pointer { return &**this; }

    constexpr auto operator[](difference_type n) const noexcept -> reference
    {
        return *(*this + n);
    }

    constexpr auto        operator==(index_iterator const& rhs) const noexcept -> bool = default;
    friend constexpr auto operator<=>(index_iterator lhs, index_iterator rhs) noexcept = default;

    friend constexpr auto launder_const_iterator<M, Fn>(index_iterator<M, Fn>) noexcept;
};
} // namespace lina::detail

#endif // LINA_INDEX_ITERATOR_HPP
