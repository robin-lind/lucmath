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

#ifndef BOUNDS_MATH_H
#define BOUNDS_MATH_H

#include "vector.hpp"
#include "utils.hpp"
#include <array>
#include <numeric>

namespace math {

template<typename T, size_t N>
struct bounds {
    bounds() :
      min(std::numeric_limits<T>::max()), max(-std::numeric_limits<T>::max()) {}

    template<typename... Ts>
    bounds(const vector<T, N>& t, const Ts&...args) :
      min(t), max(t)
    {
        constexpr auto Size = sizeof...(args);
        const std::array<vector<T, N>, Size> items{ vector<T, N>(args)... };
        for (const auto& v : items)
            extend(v);
    }

    auto& extend(const bounds<T, N>& t)
    {
        extend(t.min);
        extend(t.max);
        return *this;
    }

    auto& extend(const vector<T, N>& t)
    {
        min = math::min(min, t);
        max = math::max(max, t);
        return *this;
    }

    auto volume() const
    {
        auto result = max - min;
        return result;
    }

    auto center() const
    {
        auto result = (max + min) * T(.5);
        return result;
    }

    vector<T, N> min, max;
};

using bounds2 = bounds<float, 2>;
using bounds3 = bounds<float, 3>;
using bounds4 = bounds<float, 4>;

} // namespace math

#endif /* BOUNDS_MATH_H */