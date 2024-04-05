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

#ifndef TRIANGLE_MATH_H
#define TRIANGLE_MATH_H

#include "vector.hpp"

namespace math {

template<typename T>
auto triangle_center(const vector<T, 3>& a, const vector<T, 3>& b, const vector<T, 3>& c)
{
    return (a + b + c) * (1.f / 3.f);
}

template<typename T>
auto triangle_normal(const vector<T, 3>& a, const vector<T, 3>& b, const vector<T, 3>& c)
{
    return normalize(cross(b - a, c - a));
}

template<typename T>
auto triangle_area(const vector<T, 3>& a, const vector<T, 3>& b, const vector<T, 3>& c)
{
    return length(cross(b - a, c - a)) * .5f;
}

template<typename T>
auto triangle_signed_volume(const vector<T, 3>& a, const vector<T, 3>& b, const vector<T, 3>& c)
{
    return dot(a, cross(b, c)) * (1.f / 6.f);
}

} // namespace math

#endif /* TRIANGLE_MATH_H */