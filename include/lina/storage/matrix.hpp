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

#include "detail/launder_const_iterator.hpp"
#include "lina/concepts/is_matrix.hpp"
#include "lina/concepts/types.hpp"
#include "lina/storage/detail/coordinate_index_conversion.hpp"

#include <array>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <utility>

#define LINA_GEN_COMMON_TYPEDEFS(T)                                                                \
    using value_type      = std::remove_cvref_t<T>;                                                \
    using size_type       = lina::index_type;                                                      \
    using difference_type = lina::difference_type;                                                 \
    using reference       = value_type&;                                                           \
    using const_reference = value_type const&;                                                     \
    using pointer         = value_type*;                                                           \
    using const_pointer   = value_type const*;
#define LINA_GEN_CONTIGUOUS_ITER_TYPEDEFS                                                          \
    using iterator       = value_type*;                                                            \
    using const_iterator = value_type const*;
#define LINA_GEN_INDEX_ITER_TYPEDEFS(...)                                                          \
    using iterator       = detail::index_iterator<__VA_ARGS__*>;                                   \
    using const_iterator = detail::index_iterator<__VA_ARGS__ const*>;
#define LINA_GEN_REVERSE_ITER_TYPEDEFS                                                             \
    using reverse_iterator       = std::reverse_iterator<iterator>;                                \
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
#define LINA_GEN_ITER_FUNS                                                                         \
    constexpr auto begin() noexcept->iterator                                                      \
    {                                                                                              \
        return detail::launder_const_iterator(std::as_const(*this).begin());                       \
    }                                                                                              \
    constexpr auto cbegin() const noexcept->const_iterator { return begin(); }                     \
    constexpr auto end() noexcept->iterator                                                        \
    {                                                                                              \
        return detail::launder_const_iterator(std::as_const(*this).end());                         \
    }                                                                                              \
    constexpr auto cend() const noexcept->const_iterator { return end(); }                         \
    constexpr auto rbegin() noexcept->reverse_iterator                                             \
    {                                                                                              \
        return detail::launder_const_iterator(std::as_const(*this).rbegin());                      \
    }                                                                                              \
    constexpr auto crbegin() const noexcept->const_reverse_iterator { return rbegin(); }           \
    constexpr auto rend() noexcept->reverse_iterator                                               \
    {                                                                                              \
        return detail::launder_const_iterator(std::as_const(*this).rend());                        \
    }                                                                                              \
    constexpr auto crend() const noexcept->const_reverse_iterator { return rend(); }
#define LINA_GEN_2D_ACCESSOR                                                                       \
    constexpr auto operator()(size_type col, size_type row)->reference                             \
    {                                                                                              \
        return (*this)[detail::row_major_index(col, row, dim)];                                    \
    }                                                                                              \
    constexpr auto operator()(size_type col, size_type row) const->const_reference                 \
    {                                                                                              \
        return (*this)[detail::row_major_index(col, row, dim)];                                    \
    }
#define LINA_GEN_SIZE_FUN                                                                          \
    constexpr static auto size() noexcept->size_type { return dim.cols * dim.rows; }

namespace lina
{
template<typename T, extent E>
struct matrix
{
    LINA_GEN_COMMON_TYPEDEFS(T)
    LINA_GEN_CONTIGUOUS_ITER_TYPEDEFS
    LINA_GEN_REVERSE_ITER_TYPEDEFS

    [[nodiscard]] constexpr auto operator[](index_type idx) const noexcept -> value_type const&
    {
        return storage[idx];
    }
    [[nodiscard]] constexpr auto operator[](index_type idx) noexcept -> value_type&
    {
        return storage[idx];
    }

    LINA_GEN_2D_ACCESSOR

    constexpr auto begin() const noexcept -> const_iterator { return storage.begin(); }
    constexpr auto end() const noexcept -> const_iterator { return storage.end(); }
    constexpr auto rbegin() const noexcept -> const_reverse_iterator { return storage.rbegin(); }
    constexpr auto rend() const noexcept -> const_reverse_iterator { return storage.rend(); }

    LINA_GEN_ITER_FUNS
    LINA_GEN_SIZE_FUN

    std::array<value_type, E.cols * E.rows> storage;
    static constexpr extent                 dim = E;
};

template<typename T>
struct matrix<T, extent{.cols = 1, .rows = 1}>
{
    LINA_GEN_COMMON_TYPEDEFS(T)
    LINA_GEN_CONTIGUOUS_ITER_TYPEDEFS
    LINA_GEN_REVERSE_ITER_TYPEDEFS

    [[nodiscard]] constexpr auto operator[](index_type /*idx*/) const noexcept -> value_type const&
    {
        return x;
    }
    [[nodiscard]] constexpr auto operator[](index_type /*idx*/) noexcept -> value_type&
    {
        return x;
    }

    LINA_GEN_2D_ACCESSOR

    constexpr auto begin() const noexcept -> const_iterator { return &x; }
    constexpr auto end() const noexcept -> const_iterator { return &x + 1; }
    constexpr auto rbegin() const noexcept -> const_reverse_iterator
    {
        return std::make_reverse_iterator(end());
    }
    constexpr auto rend() const noexcept -> const_reverse_iterator
    {
        return std::make_reverse_iterator(begin());
    }

    LINA_GEN_ITER_FUNS
    LINA_GEN_SIZE_FUN

    value_type              x;
    static constexpr extent dim = extent{.cols = 1, .rows = 1};
};

#define LINA_GEN_VECTOR_STORAGE_LOOKUP3(NAME) &matrix::NAME
#define LINA_GEN_VECTOR_STORAGE_LOOKUP2(NAME, ...)                                                 \
    LINA_GEN_VECTOR_STORAGE_LOOKUP3(NAME) __VA_OPT__(, LINA_GEN_VECTOR_STORAGE_LOOKUP3(__VA_ARGS__))
#define LINA_GEN_VECTOR_STORAGE_LOOKUP1(NAME, ...)                                                 \
    LINA_GEN_VECTOR_STORAGE_LOOKUP3(NAME) __VA_OPT__(, LINA_GEN_VECTOR_STORAGE_LOOKUP2(__VA_ARGS__))
#define LINA_GEN_VECTOR_STORAGE_LOOKUP(NAME, ...)                                                  \
    LINA_GEN_VECTOR_STORAGE_LOOKUP3(NAME) __VA_OPT__(, LINA_GEN_VECTOR_STORAGE_LOOKUP1(__VA_ARGS__))

#define LINA_GEN_VECTOR_STORAGE_MEMBER3(NAME) value_type NAME;
#define LINA_GEN_VECTOR_STORAGE_MEMBER2(NAME, ...)                                                 \
    LINA_GEN_VECTOR_STORAGE_MEMBER3(NAME)                                                          \
    __VA_OPT__(LINA_GEN_VECTOR_STORAGE_MEMBER3(__VA_ARGS__))
#define LINA_GEN_VECTOR_STORAGE_MEMBER1(NAME, ...)                                                 \
    LINA_GEN_VECTOR_STORAGE_MEMBER3(NAME)                                                          \
    __VA_OPT__(LINA_GEN_VECTOR_STORAGE_MEMBER2(__VA_ARGS__))
#define LINA_GEN_VECTOR_STORAGE_MEMBER(NAME, ...)                                                  \
    LINA_GEN_VECTOR_STORAGE_MEMBER3(NAME)                                                          \
    __VA_OPT__(LINA_GEN_VECTOR_STORAGE_MEMBER1(__VA_ARGS__))

#define LINA_GEN_VECTOR_SPECIALIZATION(COLS, ROWS, ...)                                            \
    template<typename T>                                                                           \
    struct matrix<T, extent{.cols = COLS, .rows = ROWS}>                                           \
    {                                                                                              \
      private:                                                                                     \
        using self_t = matrix<T, extent{.cols = COLS, .rows = ROWS}>;                              \
                                                                                                   \
      public:                                                                                      \
        LINA_GEN_COMMON_TYPEDEFS(T)                                                                \
        LINA_GEN_INDEX_ITER_TYPEDEFS(self_t)                                                       \
        LINA_GEN_REVERSE_ITER_TYPEDEFS                                                             \
        [[nodiscard]] constexpr auto operator[](index_type idx) const noexcept                     \
            -> value_type const&                                                                   \
        {                                                                                          \
            return this->*(lookup[idx]);                                                           \
        }                                                                                          \
        [[nodiscard]] constexpr auto operator[](index_type idx) noexcept -> value_type&            \
        {                                                                                          \
            return this->*(lookup[idx]);                                                           \
        }                                                                                          \
        LINA_GEN_2D_ACCESSOR                                                                       \
        constexpr auto begin() const noexcept -> const_iterator { return const_iterator{this}; }   \
        constexpr auto end() const noexcept -> const_iterator                                      \
        {                                                                                          \
            return const_iterator{this, size()};                                                   \
        }                                                                                          \
        constexpr auto rbegin() const noexcept -> const_reverse_iterator                           \
        {                                                                                          \
            return std::make_reverse_iterator(end());                                              \
        }                                                                                          \
        constexpr auto rend() const noexcept -> const_reverse_iterator                             \
        {                                                                                          \
            return std::make_reverse_iterator(begin());                                            \
        }                                                                                          \
        LINA_GEN_ITER_FUNS                                                                         \
        LINA_GEN_SIZE_FUN                                                                          \
        LINA_GEN_VECTOR_STORAGE_MEMBER(__VA_ARGS__)                                                \
        static constexpr extent dim = extent{.cols = COLS, .rows = ROWS};                          \
                                                                                                   \
      private:                                                                                     \
        constexpr static value_type self_t::*const lookup[]{                                       \
            LINA_GEN_VECTOR_STORAGE_LOOKUP(__VA_ARGS__)};                                          \
    };

LINA_GEN_VECTOR_SPECIALIZATION(1, 2, x, y)
LINA_GEN_VECTOR_SPECIALIZATION(2, 1, x, y)
LINA_GEN_VECTOR_SPECIALIZATION(1, 3, x, y, z)
LINA_GEN_VECTOR_SPECIALIZATION(3, 1, x, y, z)
LINA_GEN_VECTOR_SPECIALIZATION(1, 4, x, y, z, w)
LINA_GEN_VECTOR_SPECIALIZATION(4, 1, x, y, z, w)

template<typename T, extent E>
struct matrix_adapter<matrix<T, E>>
{
    using value_type = matrix<T, E>::value_type;

    static constexpr extent dim = E;

    constexpr static auto get(matrix<T, E> const& m, column_type c, row_type r) noexcept
        -> decltype(auto)
    {
        return m(c, r);
    }
    constexpr static auto get(matrix<T, E>& m, column_type c, row_type r) noexcept -> decltype(auto)
    {
        return m(c, r);
    }
};
} // namespace lina

#undef LINA_GEN_COMMON_TYPEDEFS
#undef LINA_GEN_CONTIGUOUS_ITER_TYPEDEFS
#undef LINA_GEN_INDEX_ITER_TYPEDEFS
#undef LINA_GEN_REVERSE_ITER_TYPEDEFS
#undef LINA_GEN_ITER_FUNS
#undef LINA_GEN_2D_ACCESSOR
#undef LINA_GEN_VECTOR_STORAGE_LOOKUP3
#undef LINA_GEN_VECTOR_STORAGE_LOOKUP2
#undef LINA_GEN_VECTOR_STORAGE_LOOKUP1
#undef LINA_GEN_VECTOR_STORAGE_LOOKUP
#undef LINA_GEN_VECTOR_STORAGE_MEMBER3
#undef LINA_GEN_VECTOR_STORAGE_MEMBER2
#undef LINA_GEN_VECTOR_STORAGE_MEMBER1
#undef LINA_GEN_VECTOR_STORAGE_MEMBER
#undef LINA_GEN_VECTOR_SPECIALIZATION

#endif // LINA_MATRIX_HPP
