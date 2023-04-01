// MIT License
//
// Copyright (c) 2023 Robin Lind
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

#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#include "vector.h"
#include <utility>

namespace math {

template<typename T>
auto map(const T x, const T in_min, const T in_max, const T out_min, const T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T, size_t N>
auto map(const T x, const vector<T, N>& in_min, const vector<T, N>& in_max, const vector<T, N>& out_min, const vector<T, N>& out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T, typename U>
auto lerp(const U x, const T a, const T b)
{
    return (U(1) - x) * a + x * b;
}

template<typename T>
auto clamp(const T x, const T min, const T max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

template<typename T>
auto wrap(const T x, const T inclusive_min, const T exclusive_max)
{
    const auto range = exclusive_max - inclusive_min;
    auto result = x;
    while (result < inclusive_min) result += range;
    while (result >= exclusive_max) result -= range;
    return result;
}

template<size_t N>
bool all_true(vector<bool, N> t)
{
    bool result = std::apply([](auto&&...v) { return (v && ...); }, t.values);
    return result;
}

template<size_t N>
bool any_true(vector<bool, N> t)
{
    bool result = std::apply([](auto&&...v) { return (v || ...); }, t.values);
    return result;
}

template<typename T>
auto make_otho_normal_base(const vector<T, 3>& normal)
{
    // pixar technique
    // do not use sign(n.z), it can produce 0.0
    const auto sign_z = normal.z >= 0.f ? static_cast<T>(1) : static_cast<T>(-1);
    const auto a = static_cast<T>(-1) / (sign_z + normal.z);
    const auto b = normal.x * normal.y * a;
    const auto tangent = vector<T, 3>(static_cast<T>(1) + sign_z * normal.x * normal.x * a, sign_z * b, -sign_z * normal.x);
    const auto bi_tangent = vector<T, 3>(b, sign_z + normal.y * normal.y * a, -normal.y);
    return matrix<T, 3, 3>({ tangent, bi_tangent, normal });
}

} // namespace math

#endif /* UTILS_MATH_H */