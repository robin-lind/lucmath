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
#include <cstdint>

namespace math
{

template<typename T, size_t N>
union vector
{
    vector() : vector(static_cast<T>(0)) {}
    vector(const T& t) { std::fill(std::begin(E), std::end(E), t); }
    vector(const std::array<T, N>& a) : E(a) {}
    std::array<T, N> E{};
};
template<typename T>
union vector<T, 2>
{
	vector() : vector(static_cast<T>(0)) {}
	vector(const T& t) : E{ t, t } {}
	vector(const T& _x, const T& _y) : E{ _x, _y } {}
    vector(const std::array<T, 2>& a) : E(a) {}
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
union vector<T, 3>
{
	vector() : vector(static_cast<T>(0)) {}
	vector(const T& t) : E{ t, t, t } {}
	vector(const T& _x, const T& _y, const T& _z) : E{ _x, _y, _z } {}
	vector(const vector<T,2>& _xy, const T& _z) : E{ _xy.x, _xy.y, _z } {}
	vector(const T& _x, const vector<T,2>& _yz) : E{ _x, _yz.x, _yz.y } {}
    vector(const std::array<T, 3>& a) : E(a) {}
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
		vector<T,2> uv;
	};
	std::array<T, 3> E{};
};

template<typename T>
union vector<T, 4>
{
	vector() : vector(static_cast<T>(0)) {}
	vector(const T& t) : E{ t, t, t, t } {}
	vector(const T& _x, const T& _y, const T& _z, const T& _w) : E{ _x, _y, _z, _w } {}
	vector(const vector<T,2>& _xy, const T& _z, const T& _w) : E{ _xy.x, _xy.y, _z, _w } {}
	vector(const vector<T,3>& _xyz, const T& _w) : E{ _xyz.x, _xyz.y, _xyz.z, _w } {}
	vector(const vector<T,2>& _xy, const vector<T,2>& _zw) : E{ _xy.x, _xy.y, _zw.x, _zw.y } {}
	vector(const T& _x, const vector<T,3>& _yzw) : E{ _x, _yzw.x, _yzw.y, _yzw.z } {}
	vector(const T& _x, const vector<T,2>& _yz, const T& _w) : E{ _x, _yz.x, _yz.y, _w } {}
	vector(const T& _x, const T& _y, const vector<T,2>& _zw) : E{ _x, _y, _zw.x, _zw.y } {}
    vector(const std::array<T, 4>& a) : E(a) {}
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
		vector<T,3> xyz;
	};
	struct
	{
		vector<T,3> uvw;
	};
	struct
	{
		vector<T,3> rgb;
	};
	struct
	{
		vector<T,2> uv;
	};
	std::array<T, 4> E{};
};

#define vector_vector_arithmetic_op(op) \
template<typename T, size_t N> \
auto operator op (const vector<T, N>& lhs, const vector<T, N>& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<T, N>{std::get<I>(lhs.E) op std::get<I>(rhs.E)...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector<T, N>(result); \
}
#define vector_scalar_arithmetic_op(op) \
template<typename T, size_t N> \
auto operator op (const vector<T, N>& lhs, const T& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<T, N>{std::get<I>(lhs.E) op rhs...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector<T, N>(result); \
}
#define scalar_vector_arithmetic_op(op) \
template<typename T, size_t N> \
auto operator op (const T& lhs, const vector<T, N>& rhs) \
{ \
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    { \
        return std::array<T, N>{lhs op std::get<I>(rhs.E)...}; \
    } \
    (std::make_index_sequence<N>{}); \
    return vector<T, N>(result); \
}

#define vector_arithmetic_op(op) \
vector_vector_arithmetic_op(op) \
vector_scalar_arithmetic_op(op) \
scalar_vector_arithmetic_op(op)

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

#define vector_vector_assignment_op(op,opequals) \
template<typename T, size_t N> \
auto operator opequals (vector<T, N>& lhs, const vector<T, N>& rhs) \
{ \
	lhs = lhs op rhs; \
}

#define vector_t_assignment_op(op,opequals) \
template<typename T, size_t N> \
auto operator opequals (vector<T, N>& lhs, const T& rhs) \
{ \
	lhs = lhs op rhs; \
}

#define vector_assignment_op(op,opequals) \
vector_vector_assignment_op(op,opequals) \
vector_t_assignment_op(op,opequals)

#define every_assignment_op(macro) \
macro(+,+=) \
macro(-,-=) \
macro(*,*=) \
macro(/,/=)

every_arithmetic_op(vector_arithmetic_op)
every_assignment_op(vector_assignment_op)

template<typename T, size_t N>
auto operator-(const vector<T, N>& t)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>) \
    {
        return vector<T, N>(-std::get<I>(t.E)...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

using float2 = vector<float,2>;
using float3 = vector<float,3>;
using float4 = vector<float,4>;

using double2 = vector<double,2>;
using double3 = vector<double,3>;
using double4 = vector<double,4>;

using short2 = vector<int16_t,2>;
using short3 = vector<int16_t,3>;
using short4 = vector<int16_t,4>;

using int2 = vector<int32_t,2>;
using int3 = vector<int32_t,3>;
using int4 = vector<int32_t,4>;

using long2 = vector<int64_t,2>;
using long3 = vector<int64_t,3>;
using long4 = vector<int64_t,4>;

using ushort2 = vector<uint16_t,2>;
using ushort3 = vector<uint16_t,3>;
using ushort4 = vector<uint16_t,4>;

using uint2 = vector<uint32_t,2>;
using uint3 = vector<uint32_t,3>;
using uint4 = vector<uint32_t,4>;

using ulong2 = vector<uint64_t,2>;
using ulong3 = vector<uint64_t,3>;
using ulong4 = vector<uint64_t,4>;

using bool2 = vector<bool,2>;
using bool3 = vector<bool,3>;
using bool4 = vector<bool,4>;

template<typename Op = std::plus<void>, typename T, size_t N>
auto collapse(const vector<T, N>& a)
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
auto dot(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = collapse(a * b);
    return result;
}

template<typename T>
auto cross(const vector<T, 3>& a, const vector<T, 3>& b)
{
    const vector<T, 3> result{
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
    return result;
}

template<typename T, size_t N>
auto length_squared(const vector<T, N>& a)
{
    const auto result = dot(a, a);
    return result;
}

template<typename T, size_t N>
auto length(const vector<T, N>& a)
{
    const auto result = std::sqrt(length_squared(a));
    return result;
}

template<typename T, size_t N>
auto distance_squared(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = length_squared(a - b);
    return result;
}

template<typename T, size_t N>
auto distance(const vector<T, N>& a, const vector<T, N>& b)
{
    const auto result = length(a - b);
    return result;
}

template<typename T, size_t N>
auto normalize(const vector<T, N>& t)
{
    const auto result = t / length(t);
    return result;
}

template<typename T, size_t N>
auto normalized_with_length(const vector<T, N>& a)
{
    const auto l = length(a);
    return std::make_tuple(a / l, l);
}

template<typename T, size_t N>
auto min(const vector<T, N>& t, const vector<T, N>& u)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return vector<T, N>(std::min(std::get<I>(t.E), std::get<I>(u.E))...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

template<typename T, size_t N>
auto max(const vector<T, N>& t, const vector<T, N>& u)
{
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return vector<T, N>(std::max(std::get<I>(t.E), std::get<I>(u.E))...);
    }
    (std::make_index_sequence<N>{});
    return result;
}

}; // namespace math

#endif /* VECTOR_MATH_H */