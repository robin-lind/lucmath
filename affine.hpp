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

#ifndef AFFINE_MATH_H
#define AFFINE_MATH_H

#include "vector.hpp"
#include "matrix.hpp"

namespace math {

template<typename T>
struct affine {
    matrix<T, 3, 3> orientation;
    vector<T, 3> position;

    affine() = default;

    affine(const matrix<T, 3, 3>& rot) :
      orientation(rot) {}

    affine(const vector<T, 3>& pos) :
      position(pos) {}

    affine(const matrix<T, 3, 3>& rot, const vector<T, 3>& pos) :
      orientation(rot), position(pos) {}
};

template<typename T>
constexpr auto mul(const affine<T>& aff, const vector<T, 4>& vec)
{
    const auto rot = mul(aff.orientation, vec.xyz);
    const auto result = rot + aff.position * vec.w;
    return result;
}

template<typename T>
constexpr auto mul(const affine<T>& aff, const vector<T, 3>& vec)
{
    const auto result = mul(aff.orientation, vec);
    return result;
}

template<typename T>
constexpr auto mul(const affine<T>& aff, const math::matrix<T, 3, 3>& ori)
{
    const auto rot = mul(aff.orientation, ori);
    const affine<T> result(rot, aff.position);
    return result;
}

template<typename T>
constexpr auto inverse(const affine<T>& aff)
{
    const auto inv = inverse(aff.orientation);
    const affine<T> result(inv, -aff.position);
    return result;
}

} // namespace math

#endif /* AFFINE_MATH_H */