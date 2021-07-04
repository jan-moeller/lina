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

#ifndef LINA_DOT_PRODUCT_HPP
#define LINA_DOT_PRODUCT_HPP

#include "detail/dot_product_compatible.hpp"
#include "lina/algorithm/element_at.hpp"
#include "lina/algorithm/matrix_product.hpp"
#include "lina/concepts/vector.hpp"

#include <type_traits>
#include <utility>

namespace lina
{
template<vector Lhs, vector Rhs>
    requires(detail::dot_product_compatible_v<Lhs, Rhs>)
constexpr auto dot_product(Lhs const& lhs, Rhs const& rhs) noexcept -> decltype(auto)
{
    return element_at(matrix_product(lhs, rhs), 0);
}

} // namespace lina

#endif // LINA_DOT_PRODUCT_HPP
