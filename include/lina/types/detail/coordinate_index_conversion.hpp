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

#ifndef LINA_COORDINATE_INDEX_CONVERSION_HPP
#define LINA_COORDINATE_INDEX_CONVERSION_HPP

#include "lina/concepts/concept_types.hpp"

namespace lina::detail
{
constexpr auto row_major_to_index(index2_t idx, dimension_t dim) noexcept -> index_t
{
    return idx.col + idx.row * dim.cols;
}

constexpr auto column_major_to_index(index2_t idx, dimension_t dim) noexcept -> index_t
{
    return idx.row + idx.col * dim.rows;
}

constexpr auto index_to_row_major(index_t idx, dimension_t dim) noexcept -> index2_t
{
    return {static_cast<column_t>(idx % dim.cols), static_cast<row_t>(idx / dim.cols)};
}

constexpr auto index_to_column_major(index_t idx, dimension_t dim) noexcept -> index2_t
{
    return {static_cast<column_t>(idx / dim.rows), static_cast<row_t>(idx % dim.rows)};
}

static_assert(row_major_to_index(index_to_row_major(3, {2, 3}), {2, 3}) == 3);
static_assert(column_major_to_index(index_to_column_major(3, {2, 3}), {2, 3}) == 3);

static_assert(row_major_to_index(index_to_column_major(3, {2, 3}), {2, 3}) != 3);
static_assert(column_major_to_index(index_to_row_major(3, {2, 3}), {2, 3}) != 3);

struct row_major_to_index_t
{
    constexpr auto operator()(index2_t idx, dimension_t dim) const noexcept -> index_t
    {
        return row_major_to_index(idx, dim);
    }
};

struct index_to_row_major_t
{
    constexpr auto operator()(index_t idx, dimension_t dim) const noexcept -> index2_t
    {
        return index_to_row_major(idx, dim);
    }
};

struct column_major_to_index_t
{
    constexpr auto operator()(index2_t idx, dimension_t dim) const noexcept -> index_t
    {
        return column_major_to_index(idx, dim);
    }
};

struct index_to_column_major_t
{
    constexpr auto operator()(index_t idx, dimension_t dim) const noexcept -> index2_t
    {
        return index_to_column_major(idx, dim);
    }
};
} // namespace lina::detail

#endif // LINA_COORDINATE_INDEX_CONVERSION_HPP
