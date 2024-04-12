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

#ifndef SWIZZLE_H
#define SWIZZLE_H

#include "vector.hpp"

namespace math {

template<typename T, math_vector U>
constexpr auto swizzle(const U& v)
{
    const auto result = T{}(v);
    return result;
}

struct WW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.w,v.w);}};
struct WWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.w,v.w);}};
struct WWWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.w,v.w);}};
struct WWWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.w,v.x);}};
struct WWWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.w,v.y);}};
struct WWWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.w,v.z);}};
struct WWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.w,v.x);}};
struct WWXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.x,v.w);}};
struct WWXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.x,v.x);}};
struct WWXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.x,v.y);}};
struct WWXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.x,v.z);}};
struct WWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.w,v.y);}};
struct WWYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.y,v.w);}};
struct WWYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.y,v.x);}};
struct WWYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.y,v.y);}};
struct WWYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.y,v.z);}};
struct WWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.w,v.z);}};
struct WWZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.z,v.w);}};
struct WWZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.z,v.x);}};
struct WWZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.z,v.y);}};
struct WWZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.w,v.z,v.z);}};
struct WX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.w,v.x);}};
struct WXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.x,v.w);}};
struct WXWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.w,v.w);}};
struct WXWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.w,v.x);}};
struct WXWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.w,v.y);}};
struct WXWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.w,v.z);}};
struct WXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.x,v.x);}};
struct WXXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.x,v.w);}};
struct WXXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.x,v.x);}};
struct WXXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.x,v.y);}};
struct WXXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.x,v.z);}};
struct WXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.x,v.y);}};
struct WXYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.y,v.w);}};
struct WXYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.y,v.x);}};
struct WXYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.y,v.y);}};
struct WXYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.y,v.z);}};
struct WXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.x,v.z);}};
struct WXZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.z,v.w);}};
struct WXZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.z,v.x);}};
struct WXZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.z,v.y);}};
struct WXZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.x,v.z,v.z);}};
struct WY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.w,v.y);}};
struct WYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.y,v.w);}};
struct WYWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.w,v.w);}};
struct WYWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.w,v.x);}};
struct WYWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.w,v.y);}};
struct WYWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.w,v.z);}};
struct WYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.y,v.x);}};
struct WYXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.x,v.w);}};
struct WYXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.x,v.x);}};
struct WYXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.x,v.y);}};
struct WYXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.x,v.z);}};
struct WYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.y,v.y);}};
struct WYYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.y,v.w);}};
struct WYYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.y,v.x);}};
struct WYYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.y,v.y);}};
struct WYYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.y,v.z);}};
struct WYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.y,v.z);}};
struct WYZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.z,v.w);}};
struct WYZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.z,v.x);}};
struct WYZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.z,v.y);}};
struct WYZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.y,v.z,v.z);}};
struct WZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.w,v.z);}};
struct WZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.z,v.w);}};
struct WZWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.w,v.w);}};
struct WZWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.w,v.x);}};
struct WZWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.w,v.y);}};
struct WZWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.w,v.z);}};
struct WZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.z,v.x);}};
struct WZXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.x,v.w);}};
struct WZXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.x,v.x);}};
struct WZXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.x,v.y);}};
struct WZXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.x,v.z);}};
struct WZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.z,v.y);}};
struct WZYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.y,v.w);}};
struct WZYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.y,v.x);}};
struct WZYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.y,v.y);}};
struct WZYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.y,v.z);}};
struct WZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.w,v.z,v.z);}};
struct WZZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.z,v.w);}};
struct WZZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.z,v.x);}};
struct WZZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.z,v.y);}};
struct WZZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.w,v.z,v.z,v.z);}};
struct XW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.x,v.w);}};
struct XWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.w,v.w);}};
struct XWWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.w,v.w);}};
struct XWWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.w,v.x);}};
struct XWWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.w,v.y);}};
struct XWWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.w,v.z);}};
struct XWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.w,v.x);}};
struct XWXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.x,v.w);}};
struct XWXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.x,v.x);}};
struct XWXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.x,v.y);}};
struct XWXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.x,v.z);}};
struct XWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.w,v.y);}};
struct XWYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.y,v.w);}};
struct XWYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.y,v.x);}};
struct XWYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.y,v.y);}};
struct XWYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.y,v.z);}};
struct XWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.w,v.z);}};
struct XWZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.z,v.w);}};
struct XWZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.z,v.x);}};
struct XWZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.z,v.y);}};
struct XWZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.w,v.z,v.z);}};
struct XXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.x,v.w);}};
struct XXWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.w,v.w);}};
struct XXWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.w,v.x);}};
struct XXWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.w,v.y);}};
struct XXWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.w,v.z);}};
struct XXXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.w);}};
struct XXYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.w);}};
struct XXZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.w);}};
struct XYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.y,v.w);}};
struct XYWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.w,v.w);}};
struct XYWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.w,v.x);}};
struct XYWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.w,v.y);}};
struct XYWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.w,v.z);}};
struct XYXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.w);}};
struct XYYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.w);}};
struct XYZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.w);}};
struct XZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.z,v.w);}};
struct XZWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.w,v.w);}};
struct XZWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.w,v.x);}};
struct XZWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.w,v.y);}};
struct XZWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.w,v.z);}};
struct XZYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.w);}};
struct XZZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.w);}};
struct YW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.y,v.w);}};
struct YWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.w,v.w);}};
struct YWWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.w,v.w);}};
struct YWWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.w,v.x);}};
struct YWWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.w,v.y);}};
struct YWWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.w,v.z);}};
struct YWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.w,v.x);}};
struct YWXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.x,v.w);}};
struct YWXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.x,v.x);}};
struct YWXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.x,v.y);}};
struct YWXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.x,v.z);}};
struct YWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.w,v.y);}};
struct YWYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.y,v.w);}};
struct YWYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.y,v.x);}};
struct YWYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.y,v.y);}};
struct YWYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.y,v.z);}};
struct YWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.w,v.z);}};
struct YWZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.z,v.w);}};
struct YWZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.z,v.x);}};
struct YWZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.z,v.y);}};
struct YWZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.w,v.z,v.z);}};
struct YXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.x,v.w);}};
struct YXWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.w,v.w);}};
struct YXWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.w,v.x);}};
struct YXWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.w,v.y);}};
struct YXWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.w,v.z);}};
struct YXXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.w);}};
struct YXYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.w);}};
struct YXZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.w);}};
struct YYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.y,v.w);}};
struct YYWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.w,v.w);}};
struct YYWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.w,v.x);}};
struct YYWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.w,v.y);}};
struct YYWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.w,v.z);}};
struct YYXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.w);}};
struct YYYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.w);}};
struct YYZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.w);}};
struct YZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.z,v.w);}};
struct YZWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.w,v.w);}};
struct YZWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.w,v.x);}};
struct YZWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.w,v.y);}};
struct YZWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.w,v.z);}};
struct YZXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.w);}};
struct YZYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.w);}};
struct YZZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.w);}};
struct ZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.z,v.w);}};
struct ZWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.w,v.w);}};
struct ZWWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.w,v.w);}};
struct ZWWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.w,v.x);}};
struct ZWWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.w,v.y);}};
struct ZWWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.w,v.z);}};
struct ZWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.w,v.x);}};
struct ZWXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.x,v.w);}};
struct ZWXX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.x,v.x);}};
struct ZWXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.x,v.y);}};
struct ZWXZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.x,v.z);}};
struct ZWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.w,v.y);}};
struct ZWYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.y,v.w);}};
struct ZWYX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.y,v.x);}};
struct ZWYY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.y,v.y);}};
struct ZWYZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.y,v.z);}};
struct ZWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.w,v.z);}};
struct ZWZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.z,v.w);}};
struct ZWZX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.z,v.x);}};
struct ZWZY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.z,v.y);}};
struct ZWZZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.w,v.z,v.z);}};
struct ZXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.x,v.w);}};
struct ZXWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.w,v.w);}};
struct ZXWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.w,v.x);}};
struct ZXWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.w,v.y);}};
struct ZXWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.w,v.z);}};
struct ZXXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.w);}};
struct ZXYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.w);}};
struct ZXZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.w);}};
struct ZYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.y,v.w);}};
struct ZYWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.w,v.w);}};
struct ZYWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.w,v.x);}};
struct ZYWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.w,v.y);}};
struct ZYWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.w,v.z);}};
struct ZYXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.w);}};
struct ZYYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.w);}};
struct ZYZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.w);}};
struct ZZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.z,v.w);}};
struct ZZWW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.w,v.w);}};
struct ZZWX {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.w,v.x);}};
struct ZZWY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.w,v.y);}};
struct ZZWZ {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.w,v.z);}};
struct ZZXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.w);}};
struct ZZYW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.w);}};
struct ZZZW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.w);}};
struct XZXW {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.w);}};
struct XX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 2>(v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.x,v.x);}};
struct XXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.x,v.x);}};
struct XXXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.x);}};
struct XXXY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.y);}};
struct XXXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.x,v.z);}};
struct XXY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.x,v.y);}};
struct XXYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.x);}};
struct XXYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.y);}};
struct XXYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.y,v.z);}};
struct XXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.x,v.z);}};
struct XXZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.x);}};
struct XXZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.y);}};
struct XXZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.x,v.z,v.z);}};
struct XY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 2>(v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.x,v.y);}};
struct XYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.y,v.x);}};
struct XYXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.x);}};
struct XYXY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.y);}};
struct XYXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.x,v.z);}};
struct XYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.y,v.y);}};
struct XYYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.x);}};
struct XYYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.y);}};
struct XYYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.y,v.z);}};
struct XYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.y,v.z);}};
struct XYZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.x);}};
struct XYZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.y);}};
struct XYZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.y,v.z,v.z);}};
struct XZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.x,v.z);}};
struct XZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.z,v.x);}};
struct XZXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.x);}};
struct XZXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.y);}};
struct XZXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.x,v.z);}};
struct XZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.z,v.y);}};
struct XZYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.x);}};
struct XZYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.y);}};
struct XZYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.y,v.z);}};
struct XZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.x,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.x,v.z,v.z);}};
struct XZZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.x);}};
struct XZZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.y);}};
struct XZZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.x,v.z,v.z,v.z);}};
struct YX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 2>(v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.y,v.x);}};
struct YXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.x,v.x);}};
struct YXXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.x);}};
struct YXXY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.y);}};
struct YXXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.x,v.z);}};
struct YXY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.x,v.y);}};
struct YXYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.x);}};
struct YXYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.y);}};
struct YXYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.y,v.z);}};
struct YXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.x,v.z);}};
struct YXZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.x);}};
struct YXZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.y);}};
struct YXZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.x,v.z,v.z);}};
struct YY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 2>(v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.y,v.y);}};
struct YYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.y,v.x);}};
struct YYXX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.x);}};
struct YYXY {template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.y);}  template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.y);}};
struct YYXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.x,v.z);}};
struct YYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 3>(v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.y,v.y);}};
struct YYYX { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.x);}};
struct YYYY { template<math_scalar T>constexpr auto operator()(const vector<T, 2>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.y);}};
struct YYYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.y,v.z);}};
struct YYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.y,v.z);}};
struct YYZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.x);}};
struct YYZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.y);}};
struct YYZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.y,v.z,v.z);}};
struct YZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.y,v.z);}};
struct YZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.z,v.x);}};
struct YZXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.x);}};
struct YZXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.y);}};
struct YZXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.x,v.z);}};
struct YZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.z,v.y);}};
struct YZYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.x);}};
struct YZYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.y);}};
struct YZYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.y,v.z);}};
struct YZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.y,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.y,v.z,v.z);}};
struct YZZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.x);}};
struct YZZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.y);}};
struct YZZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.y,v.z,v.z,v.z);}};
struct ZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.z,v.x);}};
struct ZXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.x,v.x);}};
struct ZXXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.x);}};
struct ZXXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.y);}};
struct ZXXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.x,v.z);}};
struct ZXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.x,v.y);}};
struct ZXYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.x);}};
struct ZXYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.y);}};
struct ZXYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.y,v.z);}};
struct ZXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.x,v.z);}};
struct ZXZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.x);}};
struct ZXZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.y);}};
struct ZXZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.x,v.z,v.z);}};
struct ZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.z,v.y);}};
struct ZYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.y,v.x);}};
struct ZYXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.x);}};
struct ZYXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.y);}};
struct ZYXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.x,v.z);}};
struct ZYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.y,v.y);}};
struct ZYYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.x);}};
struct ZYYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.y);}};
struct ZYYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.y,v.z);}};
struct ZYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.y,v.z);}};
struct ZYZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.x);}};
struct ZYZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.y);}};
struct ZYZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.y,v.z,v.z);}};
struct ZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 2>(v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 2>(v.z,v.z);}};
struct ZZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.z,v.x);}};
struct ZZXX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.x);}};
struct ZZXY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.y);}};
struct ZZXZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.x,v.z);}};
struct ZZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.z,v.y);}};
struct ZZYX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.x);}};
struct ZZYY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.y);}};
struct ZZYZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.y,v.z);}};
struct ZZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 3>(v.z,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 3>(v.z,v.z,v.z);}};
struct ZZZX { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.x);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.x);}};
struct ZZZY { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.y);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.y);}};
struct ZZZZ { template<math_scalar T>constexpr auto operator()(const vector<T, 3>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.z);} template<math_scalar T>constexpr auto operator()(const vector<T, 4>& v)const{return vector<T, 4>(v.z,v.z,v.z,v.z);}};

} // namespace math

#endif /* SWIZZLE_H */