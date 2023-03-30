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

#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <cmath>
#include <array>
#include <functional>
#include <limits>

namespace math
{

template<typename T, size_t N>
union vector_tn
{
    vector_tn() : vector_tn(static_cast<T>(0)) {}
    vector_tn(const T& t) { std::fill(std::begin(E), std::end(E), t); }
    vector_tn(const std::array<T, N>& a) : E(a) {}
    std::array<T, N> E{};
};
template<typename T>
union vector_tn<T, 2>
{
	vector_tn() : vector_tn(static_cast<T>(0)) {}
	vector_tn(const T& t) : E{ t, t } {}
	vector_tn(const T& _x, const T& _y) : E{ _x, _y } {}
    vector_tn(const std::array<T, 2>& a) : E(a) {}
	struct
	{
		T x;
		T y;
	};
	struct
	{
		T u;
		T v;
	};
	struct
	{
		T w;
		T h;
	};
	std::array<T, 2> E{};
};

template<typename T>
union vector_tn<T, 3>
{
	vector_tn() : vector_tn(static_cast<T>(0)) {}
	vector_tn(const T& t) : E{ t, t, t } {}
	vector_tn(const T& _x, const T& _y, const T& _z) : E{ _x, _y, _z } {}
	vector_tn(const vector_tn<T,2>& _xy, const T& _z) : E{ _xy.x, _xy.y, _z } {}
	vector_tn(const T& _x, const vector_tn<T,2>& _yz) : E{ _x, _yz.x, _yz.y } {}
    vector_tn(const std::array<T, 3>& a) : E(a) {}
	struct
	{
		T x;
		T y;
		T z;
	};
	struct
	{
		T r;
		T g;
		T b;
	};
	struct
	{
		T u;
		T v;
		T w;
	};
	struct
	{
		vector_tn<T,2> uv;
	};
	std::array<T, 3> E{};
};

template<typename T>
union vector_tn<T, 4>
{
	vector_tn() : vector_tn(static_cast<T>(0)) {}
	vector_tn(const T& t) : E{ t, t, t, t } {}
	vector_tn(const T& _x, const T& _y, const T& _z, const T& _w) : E{ _x, _y, _z, _w } {}
	vector_tn(const vector_tn<T,2>& _xy, const T& _z, const T& _w) : E{ _xy.x, _xy.y, _z, _w } {}
	vector_tn(const vector_tn<T,3>& _xyz, const T& _w) : E{ _xyz.x, _xyz.y, _xyz.z, _w } {}
	vector_tn(const vector_tn<T,2>& _xy, const vector_tn<T,2>& _zw) : E{ _xy.x, _xy.y, _zw.x, _zw.y } {}
	vector_tn(const T& _x, const vector_tn<T,3>& _yzw) : E{ _x, _yzw.x, _yzw.y, _yzw.z } {}
	vector_tn(const T& _x, const vector_tn<T,2>& _yz, const T& _w) : E{ _x, _yz.x, _yz.y, _w } {}
	vector_tn(const T& _x, const T& _y, const vector_tn<T,2>& _zw) : E{ _x, _y, _zw.x, _zw.y } {}
    vector_tn(const std::array<T, 4>& a) : E(a) {}
	struct
	{
		T x;
		T y;
		T z;
		T w;
	};
	struct
	{
		T r;
		T g;
		T b;
		T a;
	};
	struct
	{
		vector_tn<T,3> xyz;
	};
	struct
	{
		vector_tn<T,3> uvw;
	};
	struct
	{
		vector_tn<T,3> rgb;
	};
	struct
	{
		vector_tn<T,2> uv;
	};
	std::array<T, 4> E{};
};

#define vectortn_vectortn_arithmetic_op(op) \
template<typename Scalar, size_t N> \
auto operator op (const vector_tn<Scalar, N>& lhs, const vector_tn<Scalar, N>& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<Scalar, N>{std::get<I>(lhs.E) op std::get<I>(rhs.E)...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector_tn<Scalar, N>(result); \
}
#define vectortn_scalar_arithmetic_op(op) \
template<typename Scalar, size_t N> \
auto operator op (const vector_tn<Scalar, N>& lhs, const Scalar& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<Scalar, N>{std::get<I>(lhs.E) op rhs...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector_tn<Scalar, N>(result); \
}
#define scalar_vectortn_arithmetic_op(op) \
template<typename Scalar, size_t N> \
auto operator op (const Scalar& lhs, const vector_tn<Scalar, N>& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<Scalar, N>{lhs op std::get<I>(rhs.E)...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector_tn<Scalar, N>(result); \
}

#define vectortn_arithmetic_op(op) \
vectortn_vectortn_arithmetic_op(op) \
vectortn_scalar_arithmetic_op(op) \
scalar_vectortn_arithmetic_op(op)

#define every_arithmetic_op(macro) \
macro(+) \
macro(-) \
macro(*) \
macro(/) \
macro(<) \
macro(<=) \
macro(>) \
macro(>=) \
macro(==) \
macro(!=)

#define vectortn_vectortn_assignment_op(op,opequals) \
template<typename Scalar, size_t N> \
auto operator opequals (vector_tn<Scalar, N>& lhs, const vector_tn<Scalar, N>& rhs) \
{ \
	lhs = lhs op rhs; \
}

#define vectortn_scalar_assignment_op(op,opequals) \
template<typename Scalar, size_t N> \
auto operator opequals (vector_tn<Scalar, N>& lhs, const Scalar& rhs) \
{ \
	lhs = lhs op rhs; \
}

#define vectortn_assignment_op(op,opequals) \
vectortn_vectortn_assignment_op(op,opequals) \
vectortn_scalar_assignment_op(op,opequals)

#define every_assignment_op(macro) \
macro(+,+=) \
macro(-,-=) \
macro(*,*=) \
macro(/,/=)

every_arithmetic_op(vectortn_arithmetic_op)
every_assignment_op(vectortn_assignment_op)

template<typename Scalar, size_t N>
auto operator-(const vector_tn<Scalar, N>& t)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    {
        return vector_tn<Scalar, N>(-std::get<I>(t.E)...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

using float2 = vector_tn<float,2>;
using float3 = vector_tn<float,3>;
using float4 = vector_tn<float,4>;

using double2 = vector_tn<double,2>;
using double3 = vector_tn<double,3>;
using double4 = vector_tn<double,4>;

using int2 = vector_tn<int32_t,2>;
using int3 = vector_tn<int32_t,3>;
using int4 = vector_tn<int32_t,4>;

using long2 = vector_tn<int64_t,2>;
using long3 = vector_tn<int64_t,3>;
using long4 = vector_tn<int64_t,4>;

using bool2 = vector_tn<bool,2>;
using bool3 = vector_tn<bool,3>;
using bool4 = vector_tn<bool,4>;

template<typename Op = std::plus<void>, typename T, size_t N>
auto collapse(const vector_tn<T, N>& a)
{
    if constexpr (N == 2)
        return Op{}(a.x, a.y);
    else if constexpr (N == 3)
        return Op{}(Op{}(a.x, a.y), a.z);
    else if constexpr (N == 4)
        return Op{}(Op{}(Op{}(a.x, a.y), a.z), a.w);
    else if constexpr (N > 4)
    {
        T result = a.E[0];
        for (size_t i = 1; i < N; i++)
            result = Op{}(result, a.E[i]);
        return result;
    }
}

template<typename T, size_t N>
auto dot(const vector_tn<T, N>& a, const vector_tn<T, N>& b)
{
    const auto result = collapse(a * b);
    return result;
}

template<typename T>
auto cross(const vector_tn<T, 3>& a, const vector_tn<T, 3>& b)
{
    const vector_tn<T, 3> result{
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
    return result;
}

template<typename T, size_t N>
auto length_squared(const vector_tn<T, N>& a)
{
    const auto result = dot(a, a);
    return result;
}

template<typename T, size_t N>
auto length(const vector_tn<T, N>& a)
{
    const auto result = std::sqrt(length_squared(a));
    return result;
}

template<typename T, size_t N>
auto distance_squared(const vector_tn<T, N>& a, const vector_tn<T, N>& b)
{
    const auto result = length_squared(a - b);
    return result;
}

template<typename T, size_t N>
auto distance(const vector_tn<T, N>& a, const vector_tn<T, N>& b)
{
    const auto result = length(a - b);
    return result;
}

template<typename T, size_t N>
auto normalize(const vector_tn<T, N>& t)
{
    const auto result = t / length(t);
    return result;
}

template<typename T, size_t N>
auto normalized_with_length(const vector_tn<T, N>& a)
{
    const auto l = length(a);
    return std::make_tuple(a / l, l);
}

template<typename T, size_t N>
auto min(const vector_tn<T, N>& t, const vector_tn<T, N>& u)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return vector_tn<T, N>(std::min(std::get<I>(t.E), std::get<I>(u.E))...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

template<typename T, size_t N>
auto max(const vector_tn<T, N>& t, const vector_tn<T, N>& u)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return vector_tn<T, N>(std::max(std::get<I>(t.E), std::get<I>(u.E))...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

}; // namespace math

#endif /* VECTOR_MATH_H */