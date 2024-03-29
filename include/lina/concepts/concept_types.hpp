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

#ifndef LINA_CONCEPT_TYPES_HPP
#define LINA_CONCEPT_TYPES_HPP

#include <cstdint>

namespace lina
{
using column_t     = std::uint8_t;
using row_t        = std::uint8_t;
using index_t      = std::uint16_t;
using difference_t = std::int16_t;
struct index2_t
{
    friend constexpr auto operator==(index2_t, index2_t) noexcept -> bool = default;
    column_t              col;
    row_t                 row;
};
struct dimension_t
{
    friend constexpr auto operator==(dimension_t, dimension_t) noexcept -> bool = default;
    column_t              cols;
    row_t                 rows;
};
} // namespace lina

#endif // LINA_CONCEPT_TYPES_HPP
