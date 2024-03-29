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

#ifndef LINA_MATRIX_OSTREAM_HPP
#define LINA_MATRIX_OSTREAM_HPP

#include "element_at.hpp"
#include "lina/concepts/matrix.hpp"

#include <ostream>

namespace lina
{
template<matrix M>
auto operator<<(std::ostream& os, M const& m) -> std::ostream&
{
    using A         = matrix_adapter<M>;
    auto const& dim = A::dim;
    os << "{ ";
    if (dim.cols > 0)
    {
        for (row_t y = 0; y < dim.rows; ++y)
        {
            os << element_at(m, {0, y});
            for (column_t x = 1; x < dim.cols; ++x)
                os << ", " << element_at(m, {x, y});
            if (y < dim.rows - 1)
                os << "; ";
        }
    }
    os << " }";
    return os;
}
} // namespace lina

#endif // LINA_MATRIX_OSTREAM_HPP
