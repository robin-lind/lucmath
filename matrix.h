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

#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "vector.h"
#include <array>
#include <algorithm>

namespace math {

template<typename T, size_t N>
union matrix_tn {
    matrix_tn() :
      matrix_tn(static_cast<T>(0)) {}

    matrix_tn(T t)
    {
        std::fill(std::begin(E), std::end(E), t);
    }

    matrix_tn(const std::array<T, N * N>& a) :
      E(a) {}

    matrix_tn(const std::array<vector_tn<T, N>, N>& c) :
      C(c) {}

    std::array<vector_tn<T, N>, N> C;
    std::array<T, N * N> E{};
};

template<typename T>
union affine_t {
    affine_t() :
      E{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 } {}

    affine_t(T t)
    {
        std::fill(std::begin(E), std::end(E), t);
    }

    affine_t(const std::array<vector_tn<T, 3>, 4>& columns_) :
      columns(columns_) {}

    affine_t(const matrix_tn<T, 3>& transform_, const vector_tn<T, 3>& translation_) :
      transform(transform_), translation(translation_) {}

    affine_t(const vector_tn<T, 3>& tangent_, const vector_tn<T, 3>& bi_tangent_, const vector_tn<T, 3>& normal_, const vector_tn<T, 3>& offset_) :
      columns({ tangent_, bi_tangent_, normal_, offset_ }) {}

    std::array<vector_tn<T, 3>, 4> columns;
    vector_tn<T, 3> tangent, bi_tangent, normal, offset;

    struct
    {
        matrix_tn<T, 3> transform;
        vector_tn<T, 3> translation;
    };

    std::array<T, 12> E{};
};

template<typename T>
matrix_tn<T, 3> quat_to_matrix(vector_tn<T, 4> q)
{
    matrix_tn<T, 3> m;
    m.C[0] = { q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, (q.x * q.y + q.z * q.w) * 2, (q.z * q.x - q.y * q.w) * 2 };
    m.C[1] = { (q.x * q.y - q.z * q.w) * 2, q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, (q.y * q.z + q.x * q.w) * 2 };
    m.C[2] = { (q.z * q.x + q.y * q.w) * 2, (q.y * q.z - q.x * q.w) * 2, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z };
    return m;
}

template<typename T, size_t N>
vector_tn<T, N> mul(const matrix_tn<T, N>& m, const vector_tn<T, N>& v)
{
    const auto e = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return std::array<vector_tn<T, N>, N>{ std::get<I>(m.C) * std::get<I>(v.E)... };
    }
    (std::make_index_sequence<N>{});
    auto result = e[0];
    for (size_t i = 1; i < N; i++)
        result += e[i];
    return result;
}

template<typename T, size_t N>
matrix_tn<T, N> mul(const matrix_tn<T, N>& a, const matrix_tn<T, N>& b)
{
    const auto e = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return std::array<vector_tn<T, N>, N>{ mul(a, std::get<I>(b.C))... };
    }
    (std::make_index_sequence<N>{});
    return { e };
}

template<typename T, size_t N>
auto scale(const vector_tn<T, N>& v)
{
    matrix_tn<T, N> result;
    for (size_t i = 0; i < N; i++)
        result.E[i * i] = v.E[i];
    return result;
}

// template<class T, int M> constexpr vec<T,M> mul(const mat<T,M,4> & a, const vec<T,4> & b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }
// template<class T, int M, int N> constexpr mat<T,M,4> mul(const mat<T,M,N> & a, const mat<T,N,4> & b) { return {mul(a,b.x), mul(a,b.y), mul(a,b.z), mul(a,b.w)}; }

using affinef = affine_t<float>;
using affined = affine_t<double>;
}; // namespace math

#endif /* MATRIX_MATH_H */