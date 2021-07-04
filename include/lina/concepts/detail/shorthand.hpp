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

#ifndef LINA_SHORTHAND_HPP
#define LINA_SHORTHAND_HPP

#include "lina/concepts/matrix_adapter.hpp"

#include <type_traits>

namespace lina::detail
{
template<typename M>
using ma = typename ::lina::matrix_adapter<std::remove_cvref_t<M>>;

template<typename M>
    requires requires { std::remove_cvref_t<M>::dim; }
static constexpr auto ndim = std::remove_cvref_t<M>::dim;

template<typename M>
    requires requires { typename std::remove_cvref_t<M>::value_type; }
using nvalue_type = typename std::remove_cvref_t<M>::value_type;

// clang-format off
template<typename M>
    requires requires { ndim<M>; }
          or requires { std::remove_cvref_t<ma<M>>::dim; }
static constexpr auto dim = (requires { ndim<M>; })
                                ? ndim<M>
                                : std::remove_cvref_t<ma<M>>::dim;

template<typename M>
    requires requires { dim<M>.cols; }
static constexpr auto cols = dim<M>.cols;

template<typename M>
    requires requires { dim<M>.rows; }
static constexpr auto rows = dim<M>.rows;

template<typename M>
    requires requires { typename nvalue_type<M>; }
          or requires { typename std::remove_cvref_t<ma<M>>::value_type;  }
using value_type = std::conditional_t<(requires { typename std::remove_cvref_t<M>::value_type; }),
                                      nvalue_type<M>,
                                      typename std::remove_cvref_t<ma<M>>::value_type>;
// clang-format on
} // namespace lina::detail

#endif // LINA_SHORTHAND_HPP
