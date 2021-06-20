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

#include "matrix_dimension.hpp"

#include <concepts>

namespace lina
{
template<typename M>
struct matrix_adapter;

template<typename M>
concept matrix = requires(M m, M const& mc, M& mm)
{
    typename matrix_adapter<M>::value_type;
    { matrix_adapter<M>::dim } -> std::convertible_to<matrix_dimension>;
    { matrix_adapter<M>::get(mc, std::declval<index_type>()) }
        -> std::convertible_to<typename matrix_adapter<M>::value_type>;
    { matrix_adapter<M>::get(mm, std::declval<index_type>()) }
        -> std::convertible_to<typename matrix_adapter<M>::value_type&>;
    { matrix_adapter<M>::index(mc, std::declval<column_type>(), std::declval<row_type>()) }
        -> std::convertible_to<index_type>;
};
} // namespace lina

#endif // LINA_MATRIX_HPP
