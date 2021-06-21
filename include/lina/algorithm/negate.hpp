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

#ifndef LINA_NEGATE_HPP
#define LINA_NEGATE_HPP

#include "lina/algorithm/for_each.hpp"
#include "lina/concepts/concepts.hpp"

#include <utility>

namespace lina
{
template<matrix M>
[[nodiscard]] constexpr auto negate(M const& m) noexcept -> M
{
    using A = matrix_adapter<M>;
    M result{m};
    return negate(std::in_place, result);
}

template<matrix M>
constexpr auto negate(std::in_place_t, M& m) noexcept -> M&
{
    using A = matrix_adapter<M>;
    for_each(m, [](A::value_type& v) { v = -v; });
    return m;
}
} // namespace lina

#endif // LINA_NEGATE_HPP
