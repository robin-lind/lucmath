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

#include "vector.hpp"
#include <cmath>
#include <utility>
#include <optional>

namespace math {
template<typename T, size_t N>
constexpr auto min(const vector<T, N>& t, const vector<T, N>& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::min(std::get<I>(t.values), std::get<I>(u.values))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto max(const vector<T, N>& t, const vector<T, N>& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::max(std::get<I>(t.values), std::get<I>(u.values))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto min(const vector<T, N>& t, const T& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::min(std::get<I>(t.values), u)... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
}

template<typename T, size_t N>
constexpr auto max(const vector<T, N>& t, const T& u)
{
    const auto result = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<T, N>{ std::max(std::get<I>(t.values), u)... };
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
    return (T(1) - x) * T(a) + x * T(b);
}

template<typename T>
constexpr auto clamp(const T& x, const T& min, const T& max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

template<typename T>
auto wrap(const T& x, const T& inclusive_min, const T& exclusive_max)
{
    const auto range = exclusive_max - inclusive_min;
    auto result = x;
    while (result < inclusive_min) result += range;
    while (result >= exclusive_max) result -= range;
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
        return std::array<T, N>{ sanitize(std::get<I>(v.values))... };
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
        return std::array<T, N>{ saturate(std::get<I>(v.values))... };
    }(std::make_index_sequence<N>{});
    return vector<T, N>(result);
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
struct ortho_normal_base {
    vector<T, 3> tangent, bi_tangent, normal;

    ortho_normal_base() = default;

    ortho_normal_base(const vector<T, 3>& normal) :
      normal(normal)
    {
        const auto sign_z = normal.z >= 0 ? static_cast<T>(1) : static_cast<T>(-1);
        const auto a = static_cast<T>(-1) / (sign_z + normal.z);
        const auto b = normal.x * normal.y * a;
        tangent = vector<T, 3>(static_cast<T>(1) + sign_z * normal.x * normal.x * a, sign_z * b, -sign_z * normal.x);
        bi_tangent = vector<T, 3>(b, sign_z + normal.y * normal.y * a, -normal.y);
    }

    vector<T, 3> local(const vector<T, 3>& dir) const
    {
        return { dot(dir, tangent), dot(dir, bi_tangent), dot(dir, normal) };
    }

    vector<T, 3> world(const vector<T, 3>& dir) const
    {
        return dir.x * tangent + dir.y * bi_tangent + dir.z * normal;
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