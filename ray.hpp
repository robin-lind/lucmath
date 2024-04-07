// MIT License
//
// Copyright (c) 2024 Robin Lind
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

#ifndef RAY_MATH_H
#define RAY_MATH_H

#include "vector.hpp"
#include "utils.hpp"
#include <array>
#include <numeric>

namespace math {
template<typename T, size_t N>
struct ray {
    vector<T, N> p;
    vector<T, N> d;

    auto along(const T& t) const
    {
        return p + d * t;
    }
};

template<typename T, size_t N>
auto along_ray(const vector<T, N>& p, const vector<T, N>& d, const T& t)
{
    return p + d * t;
}

using rayf3 = ray<float, 3>;
using rayd3 = ray<double, 3>;

namespace r2 {
using rayf2 = ray<float, 2>;
using rayd2 = ray<double, 2>;
using rayi2 = ray<int32_t, 2>;
} // namespace r2
} // namespace math

#endif /* RAY_MATH_H */