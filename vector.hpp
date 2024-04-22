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

#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <cmath>
#include <array>
#include <functional>
#include <limits>
#include <cstdint>
#include <type_traits>

namespace math {

template<typename T, size_t N>
struct vector {
    vector() :
      vector(T()) {}

    constexpr vector(const T& t)
    {
        std::fill(std::begin(values), std::end(values), t);
    }

    constexpr vector(const std::array<T, N>& a) :
      values(a) {}

    T& operator[](std::size_t i)
    {
        return values[i];
    }

    const T& operator[](std::size_t i) const
    {
        return values[i];
    }

    auto as_array() const
    {
        return values;
    }

    std::array<T, N> values{};
};

template<typename T>
struct vector<T, 1> {
    vector() :
      vector(T()) {}

    constexpr vector(const T& x) :
      x(x) {}

    constexpr vector(const std::array<T, 1>& a) :
      x(a[0]) {}

    operator T &()
    {
        return x;
    }

    operator T() const
    {
        return x;
    }

    T& operator[](std::size_t i)
    {
        return (&x)[i];
    }

    const T& operator[](std::size_t i) const
    {
        return (&x)[i];
    }

    auto as_array() const
    {
        const std::array<T, 1>& result{ x };
        return result;
    }

    T x;
};

template<typename T>
struct vector<T, 2> {
    vector() :
      vector(T()) {}

    constexpr vector(const T& t) :
      x(t), y(t) {}

    constexpr vector(const T& x, const T& y) :
      x(x), y(y) {}

    constexpr vector(const std::array<T, 2>& a) :
      x(a[0]), y(a[1]) {}

    T& operator[](std::size_t i)
    {
        return (&x)[i];
    }

    const T& operator[](std::size_t i) const
    {
        return (&x)[i];
    }

    auto as_array() const
    {
        const std::array<T, 2>& result{ x, y };
        return result;
    }

    template<typename S>
    constexpr auto swizzle() const
    {
        const auto result = S{}(*this);
        return result;
    }

    T x, y;
};

template<typename T>
struct vector<T, 3> {
    vector() :
      vector(T()) {}

    constexpr vector(const T& t) :
      x(t), y(t), z(t) {}

    constexpr vector(const T& x, const T& y, const T& z) :
      x(x), y(y), z(z) {}

    constexpr vector(const vector<T, 2>& _xy, const T& _z) :
      x(_xy.x), y(_xy.y), z(_z) {}

    constexpr vector(const T& _x, const vector<T, 2>& _yz) :
      x(_x), y(_yz.x), z(_yz.y) {}

    constexpr vector(const std::array<T, 3>& a) :
      x(a[0]), y(a[1]), z(a[2]) {}

    T& operator[](std::size_t i)
    {
        return (&x)[i];
    }

    const T& operator[](std::size_t i) const
    {
        return (&x)[i];
    }

    auto as_array() const
    {
        const std::array<T, 3>& result{ x, y, z };
        return result;
    }

    template<typename S>
    constexpr auto swizzle() const
    {
        const auto result = S{}(*this);
        return result;
    }

    T x, y, z;
};

template<typename T>
struct vector<T, 4> {
    vector() :
      vector(T()) {}

    constexpr vector(const T& t) :
      x(t), y(t), z(t), w(t) {}

    constexpr vector(const T& x, const T& y, const T& z, const T& w) :
      x(x), y(y), z(z), w(w) {}

    constexpr vector(const vector<T, 2>& _xy, const T& _z, const T& _w) :
      x(_xy.x), y(_xy.y), z(_z), w(_w) {}

    constexpr vector(const vector<T, 3>& _xyz, const T& _w) :
      x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}

    constexpr vector(const vector<T, 2>& _xy, const vector<T, 2>& _zw) :
      x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {}

    constexpr vector(const T& _x, const vector<T, 3>& _yzw) :
      x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}

    constexpr vector(const T& _x, const vector<T, 2>& _yz, const T& _w) :
      x(_x), y(_yz.x), z(_yz.y), w(_w) {}

    constexpr vector(const T& _x, const T& _y, const vector<T, 2>& _zw) :
      x(_x), y(_y), z(_zw.x), w(_zw.y) {}

    constexpr vector(const std::array<T, 4>& a) :
      x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}

    T& operator[](std::size_t i)
    {
        return (&x)[i];
    }

    const T& operator[](std::size_t i) const
    {
        return (&x)[i];
    }

    auto as_array() const
    {
        const std::array<T, 4>& result{ x, y, z, w };
        return result;
    }

    template<typename S>
    constexpr auto swizzle() const
    {
        const auto result = S{}(*this);
        return result;
    }

    T x, y, z, w;
};

template<typename T>
concept math_scalar = std::is_arithmetic_v<T>;

template<typename T>
concept math_vector = requires(T v) {
    v.as_array();
};

template<typename T>
concept vector_or_scalar = math_vector<T> || std::is_arithmetic_v<T>;

template<typename Op, math_scalar T, size_t N>
constexpr auto binary_op(const std::array<T, N>& lhs, const std::array<T, N>& rhs)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ Op{}(std::get<I>(lhs), std::get<I>(rhs))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename Op, math_scalar T, size_t N>
constexpr auto binary_op(const std::array<T, N>& lhs, const T& rhs)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ Op{}(std::get<I>(lhs), rhs)... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename Op, math_scalar T, size_t N>
constexpr auto binary_op(const T& lhs, const std::array<T, N>& rhs)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ Op{}(lhs, std::get<I>(rhs))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename Op, math_vector T, math_vector U>
constexpr auto binary(const T& lhs, const U& rhs)
{
    return binary_op<Op>(lhs.as_array(), rhs.as_array());
}

template<typename Op, math_vector T, math_scalar U>
constexpr auto binary(const T& lhs, const U& rhs)
{
    return binary_op<Op>(lhs.as_array(), rhs);
}

template<typename Op, math_scalar T, math_vector U>
constexpr auto binary(const T& lhs, const U& rhs)
{
    return binary_op<Op>(lhs, rhs.as_array());
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto add(const T& lhs, const U& rhs)
{
    const auto result = binary<std::plus<void>>(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto sub(const T& lhs, const U& rhs)
{
    const auto result = binary<std::minus<void>>(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto mul(const T& lhs, const U& rhs)
{
    const auto result = binary<std::multiplies<void>>(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto div(const T& lhs, const U& rhs)
{
    const auto result = binary<std::divides<void>>(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto operator+(const T& lhs, const U& rhs)
{
    const auto result = add(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto operator-(const T& lhs, const U& rhs)
{
    const auto result = sub(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto operator*(const T& lhs, const U& rhs)
{
    const auto result = mul(lhs, rhs);
    return result;
}

template<vector_or_scalar T, vector_or_scalar U>
constexpr auto operator/(const T& lhs, const U& rhs)
{
    const auto result = div(lhs, rhs);
    return result;
}

template<math_vector T, vector_or_scalar U>
constexpr auto operator+=(T& lhs, const U& rhs)
{
    lhs = lhs + rhs;
}

template<math_vector T, vector_or_scalar U>
constexpr auto operator-=(T& lhs, const U& rhs)
{
    lhs = lhs - rhs;
}

template<math_vector T, vector_or_scalar U>
constexpr auto operator*=(T& lhs, const U& rhs)
{
    lhs = lhs * rhs;
}

template<math_vector T, vector_or_scalar U>
constexpr auto operator/=(T& lhs, const U& rhs)
{
    lhs = lhs / rhs;
}

template<typename Op, math_scalar T, size_t N>
constexpr auto unary_op(const std::array<T, N>& v)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ Op{}(std::get<I>(v))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename Op, math_vector T>
constexpr auto unary(const T& v)
{
    return unary_op<Op>(v.as_array());
}

template<math_vector T>
constexpr auto operator-(const T& v)
{
    const auto result = unary<std::negate<void>>(v);
    return result;
}

template<typename Op = std::plus<void>, typename T, size_t N>
constexpr auto collapse(const vector<T, N>& a)
{
    if constexpr (N == 2)
        return Op{}(a.x, a.y);
    else if constexpr (N == 3)
        return Op{}(Op{}(a.x, a.y), a.z);
    else if constexpr (N == 4)
        return Op{}(Op{}(Op{}(a.x, a.y), a.z), a.w);
    else if constexpr (N > 4) {
        T result = a.values[0];
        for (size_t i = 1; i < N; i++)
            result = Op{}(result, a.values[i]);
        return result;
    }
}

template<typename T, size_t N>
constexpr auto dot(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = collapse(a * b);
    return result;
}

template<typename T>
constexpr auto cross(const vector<T, 3>& a, const vector<T, 3>& b)
{
    const vector<T, 3> result{
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
    return result;
}

template<typename T, size_t N>
constexpr auto length_squared(const vector<T, N>& a)
{
    const auto result = dot(a, a);
    return result;
}

template<typename T, size_t N>
constexpr auto length(const vector<T, N>& a)
{
    const auto result = std::sqrt(length_squared(a));
    return result;
}

template<typename T, size_t N>
constexpr auto length_non_zero(const vector<T, N>& a)
{
    const auto len = length_squared(a);
    const auto result = len > std::numeric_limits<T>::epsilon();
    return result;
}

template<typename T, size_t N>
constexpr auto distance_squared(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = length_squared(a - b);
    return result;
}

template<typename T, size_t N>
constexpr auto distance(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = length(a - b);
    return result;
}

template<typename T, size_t N>
constexpr auto distance_non_zero(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = length_non_zero(a - b);
    return result;
}

template<typename T, size_t N>
constexpr auto normalize(const vector<T, N>& t)
{
    const auto result = t / length(t);
    return result;
}

template<typename T, size_t N>
constexpr auto normalized_with_length(const vector<T, N>& a)
{
    const auto l = length(a);
    return std::make_tuple(a / l, l);
}

template<math_scalar T, math_scalar U, size_t N>
constexpr auto cast(const vector<U, N>& v)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ T(std::get<I>(v.as_array()))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

using float2 = vector<float, 2>;
using float3 = vector<float, 3>;
using float4 = vector<float, 4>;

using double2 = vector<double, 2>;
using double3 = vector<double, 3>;
using double4 = vector<double, 4>;

using short2 = vector<int16_t, 2>;
using short3 = vector<int16_t, 3>;
using short4 = vector<int16_t, 4>;

using int2 = vector<int32_t, 2>;
using int3 = vector<int32_t, 3>;
using int4 = vector<int32_t, 4>;

using long2 = vector<int64_t, 2>;
using long3 = vector<int64_t, 3>;
using long4 = vector<int64_t, 4>;

using ushort2 = vector<uint16_t, 2>;
using ushort3 = vector<uint16_t, 3>;
using ushort4 = vector<uint16_t, 4>;

using uint2 = vector<uint32_t, 2>;
using uint3 = vector<uint32_t, 3>;
using uint4 = vector<uint32_t, 4>;

using ulong2 = vector<uint64_t, 2>;
using ulong3 = vector<uint64_t, 3>;
using ulong4 = vector<uint64_t, 4>;

using bool2 = vector<bool, 2>;
using bool3 = vector<bool, 3>;
using bool4 = vector<bool, 4>;

}; // namespace math

#endif /* VECTOR_MATH_H */