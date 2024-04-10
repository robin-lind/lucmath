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

#ifndef DEKKER_MATH_H
#define DEKKER_MATH_H

#include "vector.hpp"
#include <cmath>

namespace math {

struct dekker {
    double h, l;

    dekker() = default;

    constexpr dekker(const double& x)
    {
        constexpr double SCALE = 134217729;
        const double p = x * SCALE;
        h = x - p + p;
        l = x - h;
    }

    constexpr dekker(const double& h, const double& l) :
      h(h), l(l) {}

    double d() const
    {
        return h + l;
    }
};

constexpr dekker dekker_addition(const dekker& a, const dekker& b)
{
    const double T = a.h + b.h;
    double t{};
    if (std::abs(a.h) > std::abs(b.h))
        t = a.h - T + b.h + a.l + b.l;
    else
        t = b.h - T + a.h + a.l + b.l;
    const auto R = T + t;
    return { R, T - R + t };
}

constexpr dekker dekker_subtraction(const dekker& a, const dekker& b)
{
    const double T = a.h + b.h;
    double t{};
    if (std::abs(a.h) > std::abs(b.h))
        t = a.h - T - b.h + a.l - b.l;
    else
        t = -b.h - T + a.h + a.l - b.l;
    const auto R = T + t;
    return { R, T - R + t };
}

constexpr dekker dekker_split(const double& x)
{
    constexpr double SCALE = 134217729;
    const double p = x * SCALE;
    const double R = x - p + p;
    return { R, x - R };
}

constexpr dekker dekker_mul12(const double& a, const double& b)
{
    const auto A = dekker_split(a);
    const auto B = dekker_split(b);
    const auto p = A.h * B.h;
    const auto q = A.h * B.l + A.l * B.h;
    const auto R = p + q;
    return { R, p - R + q + A.l * b };
}

constexpr dekker dekker_multiplication(const dekker& a, const dekker& b)
{
    const auto T = dekker_mul12(a.h, b.h);
    const auto C = a.h * b.l + a.l * b.h + T.l;
    const auto R = T.h + C;
    return { R, T.h - R + C };
}

constexpr dekker dekker_division(const dekker& a, const dekker& b)
{
    const auto U = a.h / b.h;
    const auto T = dekker_mul12(U, b.h);
    const auto L = (a.h - T.h - T.l + a.l - U * b.l) / b.h;
    const auto R = U + L;
    return { R, U - R + L };
}

#define dekker_dekker_arithmetic_op(op, func) \
constexpr auto operator op(const dekker& lhs, const dekker& rhs) \
{ \
    return func(lhs, rhs); \
}
#define dekker_scalar_arithmetic_op(op, func) \
template<typename T> \
constexpr auto operator op(const dekker& lhs, const T& rhs) \
{ \
    return func(lhs, dekker_split(rhs)); \
}
#define scalar_dekker_arithmetic_op(op, func) \
template<typename T, size_t N> \
constexpr auto operator op(const T& lhs, const dekker& rhs) \
{ \
    return func(dekker_split(lhs), rhs); \
}

#define dekker_arithmetic_op(op, func) \
dekker_dekker_arithmetic_op(op, func) \
dekker_scalar_arithmetic_op(op, func) \
scalar_dekker_arithmetic_op(op, func)

#define dekker_every_arithmetic_op(macro) \
macro(+, dekker_addition) \
macro(-, dekker_subtraction) \
macro(*, dekker_multiplication) \
macro(/, dekker_division)

#define dekker_dekker_assignment_op(op, opequals) \
template<typename T, size_t N> \
constexpr auto operator opequals(dekker& lhs, const dekker& rhs) \
{ \
    lhs = lhs op rhs; \
}

#define dekker_t_assignment_op(op, opequals) \
template<typename T, size_t N> \
constexpr auto operator opequals(dekker& lhs, const T& rhs) \
{ \
    lhs = lhs op rhs; \
}

#define dekker_assignment_op(op, opequals)    \
dekker_dekker_assignment_op(op, opequals) \
dekker_t_assignment_op(op, opequals)

#define dekker_every_assignment_op(macro) \
macro(+, +=) \
macro(-, -=) \
macro(*, *=) \
macro(/, /=)

dekker_every_arithmetic_op(dekker_arithmetic_op)
dekker_every_assignment_op(dekker_assignment_op)

#undef dekker_dekker_arithmetic_op
#undef dekker_scalar_arithmetic_op
#undef scalar_dekker_arithmetic_op
#undef dekker_arithmetic_op
#undef dekker_every_arithmetic_op
#undef dekker_dekker_assignment_op
#undef dekker_t_assignment_op
#undef dekker_assignment_op
#undef dekker_every_assignment_op

template<typename T, size_t N>
constexpr auto operator-(const dekker& t)
{
    return t * -1.0;
}

template<size_t N>
constexpr auto length(const vector<dekker, N>& a)
{
    const auto result = math::dekker_split(sqrt(length_squared(a).d()));
    return result;
}

using dekker2 = vector<dekker, 2>;
using dekker3 = vector<dekker, 3>;
using dekker4 = vector<dekker, 4>;
} // namespace math

constexpr auto operator""_dk(long double x)
{
    return math::dekker(double(x));
}

constexpr auto operator""_dk(unsigned long long x)
{
    return math::dekker(double(x));
}

#endif /* DEKKER_MATH_H */