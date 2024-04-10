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

#ifndef QUATERNION_MATH_H
#define QUATERNION_MATH_H

#include "vector.hpp"
#include "matrix.hpp"
#include <array>
#include <numeric>

namespace math {
template<typename T>
union quaternion {
    struct
    {
        T x;
        T y;
        T z;
        T w;
    };

    struct
    {
        vector<T, 3> ijk;
        T r;
    };

    struct
    {
        vector<T, 4> vec;
    };

    constexpr quaternion() :
      vec(T(0), T(0), T(0), T(1)) {}

    constexpr quaternion(const T& t) :
      vec(t, t, t, t) {}

    constexpr quaternion(const T& _x, const T& _y, const T& _z, const T& _w) :
      vec(_x, _y, _z, _w) {}

    constexpr quaternion(const vector<T, 3>& _xyz, const T& _w) :
      vec(_xyz, _w) {}

    constexpr quaternion(const vector<T, 4>& _vec) :
      vec(_vec) {}
};

template<typename T>
constexpr auto operator+(const quaternion<T>& lhs, const quaternion<T>& rhs)
{
    const quaternion<T> result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    return result;
}

template<typename T>
constexpr auto operator-(const quaternion<T>& lhs, const quaternion<T>& rhs)
{
    const quaternion<T> result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    return result;
}

template<typename T>
constexpr auto operator/(const quaternion<T>& lhs, const quaternion<T>& rhs)
{
    const quaternion<T> result(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
    return result;
}

template<typename T>
constexpr auto operator*(const quaternion<T>& lhs, const quaternion<T>& rhs)
{
    const quaternion<T> result(
      lhs.x * rhs.w + lhs.w * rhs.x + lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.y * rhs.w + lhs.w * rhs.y + lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.z * rhs.w + lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x,
      lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
    return result;
}

template<typename T>
constexpr auto operator*(const quaternion<T>& lhs, const T& rhs)
{
    const quaternion<T> result(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
    return result;
}

template<typename T>
constexpr auto operator*(const T& lhs, const quaternion<T>& rhs)
{
    const quaternion<T> result(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    return result;
}

template<typename T>
constexpr auto operator+=(quaternion<T>& lhs, const quaternion<T>& rhs)
{
    lhs = lhs + rhs;
}

template<typename T>
constexpr auto operator-=(quaternion<T>& lhs, const quaternion<T>& rhs)
{
    lhs = lhs - rhs;
}

template<typename T>
constexpr auto operator/=(quaternion<T>& lhs, const quaternion<T>& rhs)
{
    lhs = lhs / rhs;
}

template<typename T>
constexpr auto operator*=(quaternion<T>& lhs, const quaternion<T>& rhs)
{
    lhs = lhs * rhs;
}

template<typename T>
constexpr auto operator*=(quaternion<T>& lhs, const T& rhs)
{
    lhs = lhs * rhs;
}

template<typename T>
constexpr auto operator-(const quaternion<T>& t)
{
    const quaternion<T> result(-t.x, -t.y, -t.z, -t.w);
    return result;
}

template<typename T>
constexpr auto length_squared(const quaternion<T>& q)
{
    const auto result = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    return result;
}

template<typename T>
constexpr auto length(const quaternion<T>& q)
{
    const auto result = std::sqrt(length_squared(q));
    return result;
}

template<typename T>
constexpr auto normalize(const quaternion<T>& q)
{
    const auto len = length(q);
    const auto l = len == T(0) ? T(1) : len;
    const auto il = T(1) / l;
    const quaternion<T> result = q * il;
    return result;
}

template<typename T>
constexpr auto transform(const quaternion<T>& q, const matrix<T, 4, 4>& mat)
{
    const quaternion<T> result(
      mat.values[0] * q.x + mat.values[4] * q.y + mat.values[8] * q.z + mat.values[12] * q.w,
      mat.values[1] * q.x + mat.values[5] * q.y + mat.values[9] * q.z + mat.values[13] * q.w,
      mat.values[2] * q.x + mat.values[6] * q.y + mat.values[10] * q.z + mat.values[14] * q.w,
      mat.values[3] * q.x + mat.values[7] * q.y + mat.values[11] * q.z + mat.values[15] * q.w);
    return result;
}

template<typename T>
constexpr auto rotation4(const quaternion<T>& q)
{
    const auto a2 = q.x * q.x;
    const auto b2 = q.y * q.y;
    const auto c2 = q.z * q.z;
    const auto ac = q.x * q.z;
    const auto ab = q.x * q.y;
    const auto bc = q.y * q.z;
    const auto ad = q.w * q.x;
    const auto bd = q.w * q.y;
    const auto cd = q.w * q.z;
    matrix<T, 4, 4> result;
    result.values[0] = T(1) - T(2) * (b2 + c2);
    result.values[1] = T(2) * (ab + cd);
    result.values[2] = T(2) * (ac - bd);
    result.values[4] = T(2) * (ab - cd);
    result.values[5] = T(1) - T(2) * (a2 + c2);
    result.values[6] = T(2) * (bc + ad);
    result.values[8] = T(2) * (ac + bd);
    result.values[9] = T(2) * (bc - ad);
    result.values[10] = T(1) - T(2) * (a2 + b2);
    return result;
}

template<typename T>
constexpr auto rotation3(const quaternion<T>& q)
{
    const auto a2 = q.x * q.x;
    const auto b2 = q.y * q.y;
    const auto c2 = q.z * q.z;
    const auto ac = q.x * q.z;
    const auto ab = q.x * q.y;
    const auto bc = q.y * q.z;
    const auto ad = q.w * q.x;
    const auto bd = q.w * q.y;
    const auto cd = q.w * q.z;
    matrix<T, 3, 3> result;
    result.values[0] = T(1) - T(2) * (b2 + c2);
    result.values[1] = T(2) * (ab + cd);
    result.values[2] = T(2) * (ac - bd);
    result.values[3] = T(2) * (ab - cd);
    result.values[4] = T(1) - T(2) * (a2 + c2);
    result.values[5] = T(2) * (bc + ad);
    result.values[6] = T(2) * (ac + bd);
    result.values[7] = T(2) * (bc - ad);
    result.values[8] = T(1) - T(2) * (a2 + b2);
    return result;
}

// template<typename T>
// constexpr auto rotation(vector<T, 4> q)
// {
//     const matrix<T, 4, 4> m(
//       { q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, (q.x * q.y + q.z * q.w) * T(2), (q.z * q.x - q.y * q.w) * T(2), T(0) },
//       { (q.x * q.y - q.z * q.w) * T(2), q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, (q.y * q.z + q.x * q.w) * T(2), T(0) },
//       { (q.z * q.x + q.y * q.w) * T(2), (q.y * q.z - q.x * q.w) * T(2), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z, T(0) },
//       { T(0), T(0), T(0), T(1) });
//     return m;
// }

template<typename T>
constexpr auto inverse(const quaternion<T>& q)
{
    const auto ls = length_squared(q);
    if (ls == T(0))
        return q;
    const auto il = T(1) / ls;
    const quaternion<T> result(q.x * -il, q.y * -il, q.z * -il, q.w * il);
    return result;
}

template<typename T>
constexpr auto lerp(const T& x, const quaternion<T>& a, const quaternion<T>& b)
{
    const auto c = b - a;
    const quaternion<T> result(a.x + x * c.x, a.y + x * c.y, a.z + x * c.z, a.w + x * c.w);
    return result;
}

template<typename T>
auto lerp_normalized(const T& x, const quaternion<T>& a, const quaternion<T>& b)
{
    const auto regular = lerp(x, a, b);
    const auto result = normalize(regular);
    return result;
}

template<typename T>
auto slerp(const T& x, const quaternion<T>& a, const quaternion<T>& b)
{
    quaternion<T> result;
    const auto cos_half_theta = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    const auto cos_half_theta1 = cos_half_theta < 0 ? -cos_half_theta : cos_half_theta;
    const auto b1 = cos_half_theta < 0 ? -b : b;
    if (std::abs(cos_half_theta1) >= T(1)) {
        const auto result = a;
        return result;
    }
    else if (cos_half_theta1 > T(0.95)) {
        const auto result = lerp_normalized(x, a, b1);
        return result;
    }
    else {
        const auto half_theta = std::acos(cos_half_theta1);
        const auto sin_half_theta = std::sqrt(T(1) - cos_half_theta1 * cos_half_theta1);
        if (std::abs(sin_half_theta) < std::numeric_limits<T>::epsilon()) {
            const auto result = a * T(.5) + b1 * T(.5);
            return result;
        }
        else {
            const auto A = std::sin((T(1) - x) * half_theta) / sin_half_theta;
            const auto B = std::sin(x * half_theta) / sin_half_theta;
            const auto result = a * A + b1 * B;
            return result;
        }
    }

    return result;
}

template<typename T>
constexpr auto from_euler(const vector<T, 3>& e)
{
    const auto x0 = std::cos(e.x * T(.5));
    const auto x1 = std::sin(e.x * T(.5));
    const auto y0 = std::cos(e.y * T(.5));
    const auto y1 = std::sin(e.y * T(.5));
    const auto z0 = std::cos(e.z * T(.5));
    const auto z1 = std::sin(e.z * T(.5));
    const math::quaternion<T> result(
      x1 * y0 * z0 - x0 * y1 * z1,
      x0 * y1 * z0 + x1 * y0 * z1,
      x0 * y0 * z1 - x1 * y1 * z0,
      x0 * y0 * z0 + x1 * y1 * z1);
    return result;
}

template<typename T>
constexpr auto from_euler(const T& pitch, const T& roll, const T& yaw)
{
    return from_euler(vector<T, 3>(pitch, roll, yaw));
}

template<typename T>
constexpr auto to_euler(const quaternion<T>& q)
{
    const auto x0 = T(2) * (q.w * q.x + q.y * q.z);
    const auto x1 = T(1) - T(2) * (q.x * q.x + q.y * q.y);
    const auto y0 = T(2) * (q.w * q.y - q.z * q.x);
    const auto y1 = y0 > T(1) ? T(1) : y0;
    const auto y2 = y1 < -T(1) ? -T(1) : y1;
    const auto z0 = T(2) * (q.w * q.z + q.x * q.y);
    const auto z1 = T(1) - T(2) * (q.y * q.y + q.z * q.z);
    const auto x = std::atan2(x0, x1);
    const auto y = std::asin(y2);
    const auto z = std::atan2(z0, z1);
    const vector<T, 3> result(x, y, z);
    return result;
}

using quaternionf = quaternion<float>;
using quaterniond = quaternion<double>;

} // namespace math

#endif /* QUATERNION_MATH_H */