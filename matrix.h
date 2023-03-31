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

// adjugate and determinate from sgorsten/linalg *chefs kiss*
// https://github.com/sgorsten/linalg/blob/a3e87da35e32b781a4b6c01cdd5efbe7ae51c737/linalg.h

#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "vector.h"
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
        std::fill(std::begin(Elements), std::end(Elements), t);
    }

    matrix(const std::array<T, R * C>& a) :
      Elements(a) {}

    matrix(const std::array<vector<T, R>, C>& c) :
      Columns(c) {}

    std::array<vector<T, R>, C> Columns;
    std::array<T, R * C> Elements{};
};

template<typename T>
union matrix<T, 4, 4> {
    matrix() :
      matrix(identity<T, 4, 4>()) {}

    matrix(T t)
    {
        std::fill(std::begin(Elements), std::end(Elements), t);
    }

    matrix(const std::array<T, 16>& a) :
      Elements(a) {}

    matrix(const std::array<vector<T, 4>, 4>& c) :
      Columns(c) {}

    matrix(const vector<T, 4>& _x, const vector<T, 4>& _y, const vector<T, 4>& _z, const vector<T, 4>& _w) :
      x(_x), y(_y), z(_z), w(_w)  {}

    std::array<vector<T, 4>, 4> Columns;
    std::array<T, 16> Elements{};

    struct
    {
        vector<T, 4> x, y, z, w;
    };
};

template<typename T>
auto quat_to_matrix(vector<T, 4> q)
{
    matrix<T, 4, 4> m;
    m.x = { q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, (q.x * q.y + q.z * q.w) * 2, (q.z * q.x - q.y * q.w) * 2, 0 };
    m.y = { (q.x * q.y - q.z * q.w) * 2, q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, (q.y * q.z + q.x * q.w) * 2, 0 };
    m.z = { (q.z * q.x + q.y * q.w) * 2, (q.y * q.z - q.x * q.w) * 2, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z, 0 };
    m.w = { 0, 0, 0, 1 };
    return m;
}

template<typename T, size_t R, size_t C>
vector<T, R> mul(const matrix<T, R, C>& m, const vector<T, R>& v)
{
    const auto e = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return std::array<vector<T, R>, C>{ std::get<I>(m.Columns) * std::get<I>(v.E)... };
    }
    (std::make_index_sequence<C>{});
    auto result = e[0];
    for (size_t i = 1; i < C; i++)
        result += e[i];
    return result;
}

template<typename T, size_t R, size_t C>
matrix<T, R, C> mul(const matrix<T, R, C>& a, const matrix<T, R, C>& b)
{
    const auto e = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return std::array<vector<T, R>, C>{ mul(a, std::get<I>(b.Columns))... };
    }
    (std::make_index_sequence<C>{});
    return { e };
}

template<typename T, size_t R, size_t C, size_t N>
auto scale(const vector<T, N>& v)
{
    constexpr auto countRC = std::min(R, C);
    constexpr auto countN = std::min(countRC, N);
    matrix<T, R, C> result;
    for (size_t i = 0; i < countRC; i++)
        result.Columns[i].E[i] = static_cast<T>(1);
    for (size_t i = 0; i < countN; i++)
        result.Columns[i].E[i] = v.E[i];
    return result;
}

template<typename T>
auto translation(const vector<T, 3>& v)
{
    matrix<T, 4, 4> result;
    result.w.xyz = v;
    return result;
}

template<typename T, size_t R, size_t C>
auto transpose(const matrix<T, R, C>& m)
{
    matrix<T, C, R> result;
    for (size_t c = 0; c < C; c++)
        for (size_t r = 0; r < R; r++)
            result.Columns[r].E[c] = m.Columns[c].E[r];
    return result;
}

template<class T>
constexpr matrix<T, 1, 1> adjugate(const matrix<T, 1, 1>& a)
{
    return { vector<T, 1>{ 1 } };
}

template<class T>
constexpr matrix<T, 2, 2> adjugate(const matrix<T, 2, 2>& a)
{
    return {
        {a.y.y,   -a.x.y},
        { -a.y.x, a.x.x }
    };
}

template<class T>
constexpr matrix<T, 3, 3> adjugate(const matrix<T, 3, 3>& a)
{
    return {
        {a.y.y * a.z.z - a.z.y * a.y.z,  a.z.y * a.x.z - a.x.y * a.z.z, a.x.y * a.y.z - a.y.y * a.x.z},
        { a.y.z * a.z.x - a.z.z * a.y.x, a.z.z * a.x.x - a.x.z * a.z.x, a.x.z * a.y.x - a.y.z * a.x.x},
        { a.y.x * a.z.y - a.z.x * a.y.y, a.z.x * a.x.y - a.x.x * a.z.y, a.x.x * a.y.y - a.y.x * a.x.y}
    };
}

template<class T>
constexpr matrix<T, 4, 4> adjugate(const matrix<T, 4, 4>& a)
{
    return {
        {a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w,
         a.x.y * a.w.z * a.z.w + a.z.y * a.x.z * a.w.w + a.w.y * a.z.z * a.x.w - a.w.y * a.x.z * a.z.w - a.z.y * a.w.z * a.x.w - a.x.y * a.z.z * a.w.w,
         a.x.y * a.y.z * a.w.w + a.w.y * a.x.z * a.y.w + a.y.y * a.w.z * a.x.w - a.x.y * a.w.z * a.y.w - a.y.y * a.x.z * a.w.w - a.w.y * a.y.z * a.x.w,
         a.x.y * a.z.z * a.y.w + a.y.y * a.x.z * a.z.w + a.z.y * a.y.z * a.x.w - a.x.y * a.y.z * a.z.w - a.z.y * a.x.z * a.y.w - a.y.y * a.z.z * a.x.w},
        { a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x,
         a.x.z * a.z.w * a.w.x + a.w.z * a.x.w * a.z.x + a.z.z * a.w.w * a.x.x - a.x.z * a.w.w * a.z.x - a.z.z * a.x.w * a.w.x - a.w.z * a.z.w * a.x.x,
         a.x.z * a.w.w * a.y.x + a.y.z * a.x.w * a.w.x + a.w.z * a.y.w * a.x.x - a.x.z * a.y.w * a.w.x - a.w.z * a.x.w * a.y.x - a.y.z * a.w.w * a.x.x,
         a.x.z * a.y.w * a.z.x + a.z.z * a.x.w * a.y.x + a.y.z * a.z.w * a.x.x - a.x.z * a.z.w * a.y.x - a.y.z * a.x.w * a.z.x - a.z.z * a.y.w * a.x.x},
        { a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y,
         a.x.w * a.w.x * a.z.y + a.z.w * a.x.x * a.w.y + a.w.w * a.z.x * a.x.y - a.x.w * a.z.x * a.w.y - a.w.w * a.x.x * a.z.y - a.z.w * a.w.x * a.x.y,
         a.x.w * a.y.x * a.w.y + a.w.w * a.x.x * a.y.y + a.y.w * a.w.x * a.x.y - a.x.w * a.w.x * a.y.y - a.y.w * a.x.x * a.w.y - a.w.w * a.y.x * a.x.y,
         a.x.w * a.z.x * a.y.y + a.y.w * a.x.x * a.z.y + a.z.w * a.y.x * a.x.y - a.x.w * a.y.x * a.z.y - a.z.w * a.x.x * a.y.y - a.y.w * a.z.x * a.x.y},
        { a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z,
         a.x.x * a.z.y * a.w.z + a.w.x * a.x.y * a.z.z + a.z.x * a.w.y * a.x.z - a.x.x * a.w.y * a.z.z - a.z.x * a.x.y * a.w.z - a.w.x * a.z.y * a.x.z,
         a.x.x * a.w.y * a.y.z + a.y.x * a.x.y * a.w.z + a.w.x * a.y.y * a.x.z - a.x.x * a.y.y * a.w.z - a.w.x * a.x.y * a.y.z - a.y.x * a.w.y * a.x.z,
         a.x.x * a.y.y * a.z.z + a.z.x * a.x.y * a.y.z + a.y.x * a.z.y * a.x.z - a.x.x * a.z.y * a.y.z - a.y.x * a.x.y * a.z.z - a.z.x * a.y.y * a.x.z}
    };
}

template<class T>
constexpr T determinant(const matrix<T, 1, 1>& a)
{
    return a.x.x;
}

template<class T>
constexpr T determinant(const matrix<T, 2, 2>& a)
{
    return a.x.x * a.y.y - a.x.y * a.y.x;
}

template<class T>
constexpr T determinant(const matrix<T, 3, 3>& a)
{
    return a.x.x * (a.y.y * a.z.z - a.z.y * a.y.z) + a.x.y * (a.y.z * a.z.x - a.z.z * a.y.x) + a.x.z * (a.y.x * a.z.y - a.z.x * a.y.y);
}

template<class T>
constexpr T determinant(const matrix<T, 4, 4>& a)
{
    return a.x.x * (a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w) + a.x.y * (a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x) + a.x.z * (a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y) + a.x.w * (a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z);
}

template<class T, size_t N>
constexpr matrix<T, N, N> inverse(const matrix<T, N, N>& a)
{
    const auto adj = adjugate(a);
    const auto det = determinant(a);
    matrix<T, N, N> result;
    for (size_t i = 0; i < result.Elements.size(); i++) {
        result.Elements[i] = adj.Elements[i] / det;
    }
    return result;
}

template<typename T>
std::pair<vector<T, 3>, vector<T, 3>> transform_ray(const matrix<T, 4, 4>& transform, const vector<T, 3> org, const vector<T, 3>& dir)
{
    const auto _org = mul(transform, vector<T, 4>(org, 1));
    const auto _dir = mul(transform, vector<T, 4>(dir, 0));
    return std::make_pair(_org.xyz, _dir.xyz);
}

using matrix4 = matrix<float, 4, 4>;

}; // namespace math

#endif /* MATRIX_MATH_H */
