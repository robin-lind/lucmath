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

// adjugate and determinate from sgorsten/linalg *chefs kiss*
// https://github.com/sgorsten/linalg/blob/a3e87da35e32b781a4b6c01cdd5efbe7ae51c737/linalg.h

#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "vector.hpp"
#include "swizzle.hpp"
#include <array>
#include <algorithm>
#include <cstddef>
#include <utility>

namespace math {

template<typename T, size_t R, size_t C>
auto identity()
{
    constexpr auto count = std::min(R, C);
    std::array<T, R * C> result;
    std::fill(std::begin(result), std::end(result), static_cast<T>(0));
    for (size_t i = 0; i < count; i++)
        result[i * C + i] = static_cast<T>(1);
    return result;
}

template<typename T, size_t R, size_t C>
union matrix {
    matrix() :
      matrix(identity<T, R, C>()) {}

    matrix(T t)
    {
        std::fill(std::begin(values), std::end(values), t);
    }

    matrix(const std::array<T, R * C>& a) :
      values(a) {}

    matrix(const std::array<vector<T, R>, C>& c) :
      columns(c) {}

    T& operator[](std::size_t i)
    {
        return values[i];
    }

    const T& operator[](std::size_t i) const
    {
        return values[i];
    }

    std::array<vector<T, R>, C> columns;
    std::array<T, R * C> values{};
};

template<typename T>
union matrix<T, 3, 3> {
    matrix() :
      matrix(identity<T, 3, 3>()) {}

    matrix(T t)
    {
        std::fill(std::begin(values), std::end(values), t);
    }

    matrix(const std::array<T, 9>& a) :
      values(a) {}

    matrix(const std::array<vector<T, 3>, 3>& c) :
      columns(c) {}

    matrix(const vector<T, 3>& _x, const vector<T, 3>& _y, const vector<T, 3>& _z) :
      x(_x), y(_y), z(_z) {}

    T& operator[](std::size_t i)
    {
        return values[i];
    }

    const T& operator[](std::size_t i) const
    {
        return values[i];
    }

    std::array<vector<T, 3>, 3> columns;
    std::array<T, 9> values{};

    struct
    {
        vector<T, 3> x, y, z;
    };
};

template<typename T>
union matrix<T, 4, 4> {
    matrix() :
      matrix(identity<T, 4, 4>()) {}

    matrix(T t)
    {
        std::fill(std::begin(values), std::end(values), t);
    }

    matrix(const std::array<T, 16>& a) :
      values(a) {}

    matrix(const std::array<vector<T, 4>, 4>& c) :
      columns(c) {}

    matrix(const vector<T, 4>& _x, const vector<T, 4>& _y, const vector<T, 4>& _z, const vector<T, 4>& _w) :
      x(_x), y(_y), z(_z), w(_w) {}

    T& operator[](std::size_t i)
    {
        return values[i];
    }

    const T& operator[](std::size_t i) const
    {
        return values[i];
    }

    std::array<vector<T, 4>, 4> columns;
    std::array<T, 16> values{};

    struct
    {
        vector<T, 4> x, y, z, w;
    };
};

template<typename T, size_t R, size_t C, size_t N>
constexpr auto diagonal_matrix(const vector<T, N>& v)
{
    constexpr size_t RC = std::min(R, C), RCN = std::min(RC, N);
    matrix<T, R, C> result;
    for (size_t i = 0; i < RCN; i++)
        result.values[i * C + i] = v.values[i];
    return result;
}

template<typename T, size_t R, size_t C>
constexpr auto mul(const vector<T, R>& v, const matrix<T, R, C>& m)
{
    const auto e = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<vector<T, R>, C>{ std::get<I>(m.columns) * std::get<I>(v.as_array())... };
    }(std::make_index_sequence<C>{});
    auto result = e[0];
    for (size_t i = 1; i < C; i++)
        result += e[i];
    return result;
}

template<typename T, size_t R, size_t C>
constexpr auto mul(const matrix<T, R, C>& a, const matrix<T, R, C>& b)
{
    const matrix<T, R, C> result([&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<vector<T, C>, R>{ mul(std::get<I>(b.columns), a)... };
    }(std::make_index_sequence<R>{}));
    return result;
}

template<typename T, size_t R, size_t C, size_t N>
constexpr auto scale(const vector<T, N>& v)
{
    constexpr auto countRC = std::min(R, C);
    constexpr auto countN = std::min(countRC, N);
    matrix<T, R, C> result;
    for (size_t i = 0; i < countRC; i++)
        result.columns[i][i] = static_cast<T>(1);
    for (size_t i = 0; i < countN; i++)
        result.columns[i][i] = v[i];
    return result;
}

template<typename T>
constexpr auto translation(const vector<T, 3>& v)
{
    matrix<T, 4, 4> result;
    result[12] = v.x;
    result[13] = v.y;
    result[14] = v.z;
    return result;
}

template<typename T, size_t R, size_t C>
constexpr auto transpose(const matrix<T, R, C>& m)
{
    matrix<T, C, R> result;
    for (size_t c = 0; c < C; c++)
        for (size_t r = 0; r < R; r++)
            result.columns[r][c] = m.columns[c][r];
    return result;
}

template<typename T>
constexpr auto adjugate(const matrix<T, 1, 1>& a)
{
    const matrix<T, 1, 1> result(vector<T, 1>(1));
    return result;
}

template<typename T>
constexpr auto adjugate(const matrix<T, 2, 2>& a)
{
    const matrix<T, 2, 2> result(
      { a.y.y, -a.x.y },
      { -a.y.x, a.x.x });
    return result;
}

template<typename T>
constexpr auto adjugate(const matrix<T, 3, 3>& a)
{
    const matrix<T, 3, 3> result(
      { a.y.y * a.z.z - a.z.y * a.y.z, a.z.y * a.x.z - a.x.y * a.z.z, a.x.y * a.y.z - a.y.y * a.x.z },
      { a.y.z * a.z.x - a.z.z * a.y.x, a.z.z * a.x.x - a.x.z * a.z.x, a.x.z * a.y.x - a.y.z * a.x.x },
      { a.y.x * a.z.y - a.z.x * a.y.y, a.z.x * a.x.y - a.x.x * a.z.y, a.x.x * a.y.y - a.y.x * a.x.y });
    return result;
}

template<typename T>
constexpr auto adjugate(const matrix<T, 4, 4>& a)
{
    const matrix<T, 4, 4> result(
      { a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w,
        a.x.y * a.w.z * a.z.w + a.z.y * a.x.z * a.w.w + a.w.y * a.z.z * a.x.w - a.w.y * a.x.z * a.z.w - a.z.y * a.w.z * a.x.w - a.x.y * a.z.z * a.w.w,
        a.x.y * a.y.z * a.w.w + a.w.y * a.x.z * a.y.w + a.y.y * a.w.z * a.x.w - a.x.y * a.w.z * a.y.w - a.y.y * a.x.z * a.w.w - a.w.y * a.y.z * a.x.w,
        a.x.y * a.z.z * a.y.w + a.y.y * a.x.z * a.z.w + a.z.y * a.y.z * a.x.w - a.x.y * a.y.z * a.z.w - a.z.y * a.x.z * a.y.w - a.y.y * a.z.z * a.x.w },
      { a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x,
        a.x.z * a.z.w * a.w.x + a.w.z * a.x.w * a.z.x + a.z.z * a.w.w * a.x.x - a.x.z * a.w.w * a.z.x - a.z.z * a.x.w * a.w.x - a.w.z * a.z.w * a.x.x,
        a.x.z * a.w.w * a.y.x + a.y.z * a.x.w * a.w.x + a.w.z * a.y.w * a.x.x - a.x.z * a.y.w * a.w.x - a.w.z * a.x.w * a.y.x - a.y.z * a.w.w * a.x.x,
        a.x.z * a.y.w * a.z.x + a.z.z * a.x.w * a.y.x + a.y.z * a.z.w * a.x.x - a.x.z * a.z.w * a.y.x - a.y.z * a.x.w * a.z.x - a.z.z * a.y.w * a.x.x },
      { a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y,
        a.x.w * a.w.x * a.z.y + a.z.w * a.x.x * a.w.y + a.w.w * a.z.x * a.x.y - a.x.w * a.z.x * a.w.y - a.w.w * a.x.x * a.z.y - a.z.w * a.w.x * a.x.y,
        a.x.w * a.y.x * a.w.y + a.w.w * a.x.x * a.y.y + a.y.w * a.w.x * a.x.y - a.x.w * a.w.x * a.y.y - a.y.w * a.x.x * a.w.y - a.w.w * a.y.x * a.x.y,
        a.x.w * a.z.x * a.y.y + a.y.w * a.x.x * a.z.y + a.z.w * a.y.x * a.x.y - a.x.w * a.y.x * a.z.y - a.z.w * a.x.x * a.y.y - a.y.w * a.z.x * a.x.y },
      { a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z,
        a.x.x * a.z.y * a.w.z + a.w.x * a.x.y * a.z.z + a.z.x * a.w.y * a.x.z - a.x.x * a.w.y * a.z.z - a.z.x * a.x.y * a.w.z - a.w.x * a.z.y * a.x.z,
        a.x.x * a.w.y * a.y.z + a.y.x * a.x.y * a.w.z + a.w.x * a.y.y * a.x.z - a.x.x * a.y.y * a.w.z - a.w.x * a.x.y * a.y.z - a.y.x * a.w.y * a.x.z,
        a.x.x * a.y.y * a.z.z + a.z.x * a.x.y * a.y.z + a.y.x * a.z.y * a.x.z - a.x.x * a.z.y * a.y.z - a.y.x * a.x.y * a.z.z - a.z.x * a.y.y * a.x.z });
    return result;
}

template<typename T>
constexpr auto determinant(const matrix<T, 1, 1>& a)
{
    return a.x.x;
}

template<typename T>
constexpr auto determinant(const matrix<T, 2, 2>& a)
{
    return a.x.x * a.y.y - a.x.y * a.y.x;
}

template<typename T>
constexpr auto determinant(const matrix<T, 3, 3>& a)
{
    return a.x.x * (a.y.y * a.z.z - a.z.y * a.y.z) + a.x.y * (a.y.z * a.z.x - a.z.z * a.y.x) + a.x.z * (a.y.x * a.z.y - a.z.x * a.y.y);
}

template<typename T>
constexpr auto determinant(const matrix<T, 4, 4>& a)
{
    return a.x.x * (a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w) + a.x.y * (a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x) + a.x.z * (a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y) + a.x.w * (a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z);
}

template<typename T, size_t N>
constexpr auto inverse(const matrix<T, N, N>& a)
{
    const auto adj = adjugate(a);
    const auto det = determinant(a);
    matrix<T, N, N> result;
    for (size_t i = 0; i < result.values.size(); i++)
        result.values[i] = adj.values[i] / det;
    return result;
}

template<typename T>
constexpr auto look_at(const vector<T, 3>& eye, const vector<T, 3>& target, const vector<T, 3>& up)
{
    const auto vz = normalize(eye - target);
    const auto vx = normalize(cross(up, vz));
    const auto vy = cross(vz, vx);
    const matrix<T, 4, 4> result({ vx.x,
                                   vy.x,
                                   vz.x,
                                   0.0f,
                                   vx.y,
                                   vy.y,
                                   vz.y,
                                   0.0f,
                                   vx.z,
                                   vy.z,
                                   vz.z,
                                   0.0f,
                                   -dot(vx, eye),
                                   -dot(vy, eye),
                                   -dot(vz, eye),
                                   1.0f });
    return transpose(result); // this isn't transposed in raylib, suffering from skill issues
}

template<typename T>
constexpr auto perspective(const T& fovY, const T& aspect, const T& near, const T& far)
{
    const auto top = near * std::tan(fovY * T(.5));
    const auto bottom = -top;
    const auto right = top * aspect;
    const auto left = -right;
    const auto rl = right - left;
    const auto tb = top - bottom;
    const auto fn = far - near;
    matrix<T, 4, 4> result;
    result.values[0] = (near * T(2)) / rl;
    result.values[5] = (near * T(2)) / tb;
    result.values[8] = (right + left) / rl;
    result.values[9] = (top + bottom) / tb;
    result.values[10] = -(far + near) / fn;
    result.values[11] = T(-1);
    result.values[14] = -(far * near * T(2)) / fn;
    return result;
}

template<typename T>
constexpr auto orthographic(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far)
{
    const auto rl = right - left;
    const auto tb = top - bottom;
    const auto fn = far - near;
    matrix<T, 4, 4> result({ T(2) / rl,
                             T(0),
                             T(0),
                             T(0),
                             T(0),
                             T(2) / tb,
                             T(0),
                             T(0),
                             T(0),
                             T(0),
                             T(-2) / fn,
                             T(0),
                             -(left + right) / rl,
                             -(top + bottom) / tb,
                             -(far + near) / fn,
                             T(1) });
    return result;
}

template<typename T>
constexpr auto rotation(const vector<T, 3>& axis, const T& angle)
{
    const auto na = normalize(axis);
    const auto s = std::sin(angle);
    const auto c = std::cos(angle);
    const auto t = T(1) - c;
    const matrix<T, 4, 4> result({ na.x * na.x * t + c,
                                   na.y * na.x * t + na.z * s,
                                   na.z * na.x * t - na.y * s,
                                   T(0),
                                   na.x * na.y * t - na.z * s,
                                   na.y * na.y * t + c,
                                   na.z * na.y * t + na.x * s,
                                   T(0),
                                   na.x * na.z * t + na.y * s,
                                   na.y * na.z * t - na.x * s,
                                   na.z * na.z * t + c,
                                   T(0),
                                   T(0),
                                   T(0),
                                   T(0),
                                   T(1) });
    return result;
}

template<math_scalar T, math_scalar U, size_t R, size_t C>
constexpr auto cast(const matrix<U, R, C>& m)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, R * C>{ T(std::get<I>(m.values))... };
    }(std::make_index_sequence<R * C>{});
    return matrix<T, R, C>(result);
}

using matrix3 = matrix<float, 3, 3>;
using matrix4 = matrix<float, 4, 4>;
using matrixd3 = matrix<double, 3, 3>;
using matrixd4 = matrix<double, 4, 4>;

}; // namespace math

#endif /* MATRIX_MATH_H */
