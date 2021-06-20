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

#ifndef LINA_FOR_EACH_INDEX_HPP
#define LINA_FOR_EACH_INDEX_HPP

#include "lina/concepts/concepts.hpp"

#include <concepts>
#include <utility>

namespace lina
{
enum class traversal_order
{
    row_major,
    column_major,
};

template<matrix M, std::invocable<index_t> Fun>
constexpr auto for_each_index(Fun&& f) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    for (std::size_t i = 0; i < (A::dim.cols * A::dim.rows); ++i)
        std::forward<Fun>(f)(i);
    return std::forward<Fun>(f);
}

template<matrix                                M,
         traversal_order                       Order = traversal_order::row_major,
         std::invocable<column_t, row_t> Fun>
constexpr auto for_each_index(Fun&& f) noexcept -> decltype(auto)
{
    using A = matrix_adapter<M>;
    static_assert(Order == traversal_order::row_major || Order == traversal_order::column_major);
    if constexpr (Order == traversal_order::row_major)
    {
        for (row_t r = 0; r < A::dim.cols; ++r)
        {
            for (column_t c = 0; c < A::dim.rows; ++c)
                std::forward<Fun>(f)(c, r);
        }
    }
    else if constexpr (Order == traversal_order::column_major)
    {
        for (column_t c = 0; c < A::dim.rows; ++c)
        {
            for (row_t r = 0; r < A::dim.cols; ++r)
                std::forward<Fun>(f)(c, r);
        }
    }
    return std::forward<Fun>(f);
}
} // namespace lina

#endif // LINA_FOR_EACH_INDEX_HPP
