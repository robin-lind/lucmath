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

#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#include "matrix.hpp"
#include "vector.hpp"
#include "quaternion.hpp"
#include <cmath>
#include <utility>
#include <optional>

namespace math {
template<typename T, size_t N>
constexpr auto min(const vector<T, N>& t, const vector<T, N>& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::min(std::get<I>(t.as_array()), std::get<I>(u.as_array()))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto max(const vector<T, N>& t, const vector<T, N>& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::max(std::get<I>(t.as_array()), std::get<I>(u.as_array()))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto min(const vector<T, N>& t, const T& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::min(std::get<I>(t.as_array()), u)... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto max(const vector<T, N>& t, const T& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::max(std::get<I>(t.as_array()), u)... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, typename U, typename V>
constexpr auto map(const T& x, const U& in_min, const U& in_max, const V& out_min, const V& out_max)
{
    return (x - T(in_min)) * T(out_max - out_min) / T(in_max - in_min) + T(out_min);
}

template<typename T, typename U>
constexpr auto lerp(const T& x, const U& a, const U& b)
{
    return (T(1) - x) * a + x * b;
}

template<typename T>
constexpr auto clamp(const T& x, const T& min, const T& max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

template<typename T>
constexpr auto bounded(const T& x, const T& min, const T& max)
{
    return (min < x) && (x < max);
}

template<typename T>
auto wrap(const T& x, const T& min, const T& max)
{
    const auto range = max - min;
    // const auto result = x - range * std::floor((x - min) / range);
    auto result = x;
    while (result < min) result += range;
    while (result >= max) result -= range;
    return result;
}

template<typename T>
constexpr auto sanitize(const T& x)
{
    if (std::isfinite(x))
        return x;
    return T(0);
}

template<typename T, size_t N>
constexpr auto sanitize(const vector<T, N>& v)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ sanitize(std::get<I>(v.as_array()))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T>
constexpr auto saturate(const T& x)
{
    return clamp(x, T(0), T(1));
}

template<typename T, size_t N>
constexpr auto saturate(const vector<T, N>& v)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ saturate(std::get<I>(v.as_array()))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T>
constexpr auto sign(const T& x)
{
    if (x > T(0))
        return T(1);
    if (x < T(0))
        return T(-1);
    return T(0);
}

template<typename T>
constexpr auto reflect(const vector<T, 3>& w, const vector<T, 3>& n)
{
    const auto result = n * (dot(n, w) * static_cast<T>(2)) - w;
    return result;
}

template<typename T, size_t N>
constexpr auto mean(const vector<T, N>& v)
{
    const auto m = T(1) / T(N);
    const auto result = collapse(v) * m;
    return result;
}

template<typename T, size_t N>
constexpr auto face_forward(const vector<T, N>& n, const vector<T, N>& v)
{
    const auto result = dot(n, v) < T(0) ? -n : n;
    return result;
}

template<typename T, size_t N>
constexpr auto rotate_axis_angle(const vector<T, N>& v, const vector<T, N>& axis, const T& angle)
{
    const auto axis_len = length(axis);
    const auto axis_len1 = axis_len == T(0) ? T(1) : axis_len;
    const auto scaled_axis = axis / axis_len1;

    const T a = std::sin(angle * T(.5));
    const float3 w = scaled_axis * a;
    const auto wv = cross(w, v);
    const auto v1 = cross(w, wv) * T(2);
    const auto b = std::cos(angle * T(.5)) * T(2);
    const auto v2 = wv * b;

    const float3 result = v + v1 + v2;

    return result;
}

template<typename T>
constexpr auto atan2(const vector<T, 2>& v)
{
    const auto result = std::atan2(v.y, v.x);
    return result;
}

template<typename T>
constexpr auto separation_angle(const vector<T, 2>& a, const vector<T, 2>& b)
{
    const auto angle_a = atan2(a);
    const auto angle_b = atan2(b);
    const auto result = angle_b - angle_a;
    return result;
}

template<typename T>
constexpr auto vector_angle(const vector<T, 3>& a, const vector<T, 3>& b)
{
    const auto c = cross(a, b);
    const auto l = length(c);
    const auto d = dot(a, b);
    const auto result = std::atan2(l, d);
    return result;
}

template<typename T>
constexpr auto perpendicular(const vector<T, 3>& v)
{
    auto min = std::abs(v.x);
    vector<T, 3> axis(1, 0, 0);
    if (std::abs(v.y) < min) {
        min = std::abs(v.y);
        axis = vector<T, 3>(0, 1, 0);
    }
    if (std::abs(v.z) < min)
        axis = vector<T, 3>(0, 0, 1);
    const vector<T, 3> result = cross(v, axis);
    return result;
}

template<typename T>
constexpr auto unproject(const vector<T, 3>& source, const matrix<T, 4, 4>& projection, const matrix<T, 4, 4>& view)
{
    const auto view_proj = mul(projection, transpose(view)); // why does view need to be transposed now?!
    const auto inv_view_proj = inverse(view_proj);
    const quaternion<T> quat(source.x, source.y, source.z, T(1));
    const auto qtransformed = transform(quat, inv_view_proj);
    const auto result = qtransformed.ijk / qtransformed.r;
    return result;
}

template<typename T>
constexpr auto ortho_normalize(vector<T, 3>& v1, vector<T, 3>& v2)
{
    v1 = normalize(v1);
    const auto vn1 = normalize(cross(v1, v2));
    v2 = cross(vn1, v1);
}

template<size_t N>
bool all_true(const vector<bool, N>& t)
{
    const bool result = std::apply([](auto&&...v) { return (v && ...); }, t.values);
    return result;
}

template<size_t N>
bool any_true(const vector<bool, N>& t)
{
    const bool result = std::apply([](auto&&...v) { return (v || ...); }, t.values);
    return result;
}

template<typename T>
constexpr auto rotate(const vector<T, 3>& v, const quaternion<T>& q)
{
    const vector<T, 3> a((q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z),
                         (T(2) * q.x * q.y - T(2) * q.w * q.z),
                         (T(2) * q.x * q.z + T(2) * q.w * q.y));
    const vector<T, 3> b((T(2) * q.w * q.z + T(2) * q.x * q.y),
                         (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z),
                         (T(-2) * q.w * q.x + T(2) * q.y * q.z));
    const vector<T, 3> c((T(-2) * q.w * q.y + T(2) * q.x * q.z),
                         (T(2) * q.w * q.x + T(2) * q.y * q.z),
                         (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
    const vector<T, 3> result(dot(v, a), dot(v, b), dot(v, c));
    return result;
}

template<typename T>
auto same_hemisphere(const vector<T, 3>& a, const vector<T, 3>& b)
{
    const auto d = dot(a, b);
    const auto result = d > T(0);
    return result;
}

template<typename T>
struct ortho_normal_base {
    vector<T, 3> tangent, bitangent, normal;

    ortho_normal_base() = default;

    ortho_normal_base(const vector<T, 3>& tangent, const vector<T, 3>& bitangent, const vector<T, 3>& normal) :
      tangent(tangent), bitangent(bitangent), normal(normal)
    {
    }

    ortho_normal_base(const vector<T, 3>& normal) :
      normal(normal)
    {
        const auto sign_z = normal.z >= 0 ? static_cast<T>(1) : static_cast<T>(-1);
        const auto a = static_cast<T>(-1) / (sign_z + normal.z);
        const auto b = normal.x * normal.y * a;
        tangent = vector<T, 3>(static_cast<T>(1) + sign_z * normal.x * normal.x * a, sign_z * b, -sign_z * normal.x);
        bitangent = vector<T, 3>(b, sign_z + normal.y * normal.y * a, -normal.y);
    }

    vector<T, 3> local(const vector<T, 3>& dir) const
    {
        return { dot(dir, tangent), dot(dir, bitangent), dot(dir, normal) };
    }

    vector<T, 3> world(const vector<T, 3>& dir) const
    {
        return dir.x * tangent + dir.y * bitangent + dir.z * normal;
    }
};

namespace onb {
template<typename T>
auto cos_theta(const vector<T, 3>& w)
{
    const auto result = w.z;
    return result;
}

template<typename T>
auto abs_cos_theta(const vector<T, 3>& w)
{
    const auto result = std::abs(cos_theta(w));
    return result;
}

template<typename T>
auto cos_theta_sq(const vector<T, 3>& w)
{
    const auto result = w.z * w.z;
    return result;
}

template<typename T>
auto sin_theta_sq(const vector<T, 3>& w)
{
    const auto result = std::max(T(0), T(1) - cos_theta_sq(w));
    return result;
}

template<typename T>
auto sin_theta(const vector<T, 3>& w)
{
    const auto result = std::sqrt(sin_theta_sq(w));
    return result;
}

template<typename T>
auto tan_theta(const vector<T, 3>& w)
{
    const auto result = sin_theta(w) / cos_theta(w);
    return result;
}

template<typename T>
auto tan_theta_sq(const vector<T, 3>& w)
{
    const auto result = sin_theta_sq(w) / cos_theta_sq(w);
    return result;
}

template<typename T>
auto cos_phi(const vector<T, 3>& w)
{
    const auto st = sin_theta(w);
    const auto result = st == T(0) ? T(0) : clamp(w.x / st, T(-1), T(1));
    return result;
}

template<typename T>
auto sin_phi(const vector<T, 3>& w)
{
    const auto st = sin_theta(w);
    const auto result = st == T(0) ? T(0) : clamp(w.y / st, T(-1), T(1));
    return result;
}

template<typename T>
auto cos_phi_sq(const vector<T, 3>& w)
{
    const auto cp = cos_phi(w);
    const auto result = cp * cp;
    return result;
}

template<typename T>
auto sin_phi_sq(const vector<T, 3>& w)
{
    const auto sp = sin_phi(w);
    const auto result = sp * sp;
    return result;
}

template<typename T>
auto same_hemisphere(const vector<T, 3>& wo, const vector<T, 3>& wi)
{
    const auto result = wo.z * wi.z > T(0);
    return result;
}
} // namespace onb

template<typename T>
struct plane {
    vector<T, 3> normal;
    T d;

    plane() = default;

    plane(const vector<T, 3>& p, const vector<T, 3>& n) :
      normal(n)
    {
        d = -dot(p, n);
    }

    auto distance(const vector<T, 3>& p) const
    {
        return (dot(p, normal) + d);
    }

    auto above(const vector<T, 3>& p) const
    {
        return distance(p) > 0.f;
    }

    std::optional<vector<T, 3>> intersect(const vector<T, 3>& P0, const vector<T, 3>& P1) const
    {
        const auto P0P1 = P1 - P0;
        const auto denominator = dot(normal, P0P1);
        if (std::abs(denominator) < std::numeric_limits<T>::epsilon())
            return {};
        const auto u = distance(P0) / -denominator;
        if (u < 0.f || u > 1.f)
            return {};
        return P0 + P0P1 * u;
    }
};

using planef = plane<float>;
using planed = plane<double>;

} // namespace math

#endif /* UTILS_MATH_H */