/**
 * @file      Math.h
 * @brief     Draw related math utilities (Vec2, BBox...)
 *
 * Copyright (C) Witekio
 *
 * This file is part of the Zephyr Rush demonstration.
 *
 * This demonstration is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This demonstration is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This demonstration. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <limits>

#include "Core/Base.h"

namespace Math {
    // clang-format off

    template <typename T>
    struct Vec2 {
        T x{}, y{};

        Vec2() = default;
        explicit Vec2(T v) : x(v), y(v) {}
        Vec2(T x, T y) : x(x), y(y) {}

        template <typename U>
        explicit Vec2(const Vec2<U>& v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

        template <typename U>
        static Vec2 From(const Vec2<U>& v) { return {static_cast<T>(v.x), static_cast<T>(v.y)}; }

        static T Length(const Vec2& v)              { return std::sqrt(v.x * v.x + v.y * v.y); }
        static T Dist(const Vec2& a, const Vec2& b) { return std::hypot(a.x - b.x, a.y - b.y); }
        static T Dot(const Vec2& a, const Vec2& b)  { return a.x * b.x + a.y * b.y; }
        static T LengthSq(const Vec2& v)            { return Dot(v, v); }
        static T Max(const Vec2& v)                 { return std::max(v.x, v.y); }
        static T Min(const Vec2& v)                 { return std::min(v.x, v.y); }

        static Vec2 Floor(const Vec2& v)                                  { return {std::floor(v.x), std::floor(v.y)}; }
        static Vec2 Ceil(const Vec2& v)                                   { return {std::ceil(v.x), std::ceil(v.y)}; }
        static Vec2 Min(const Vec2& a, const Vec2& b)                     { return {std::min(a.x, b.x), std::min(a.y, b.y)}; }
        static Vec2 Max(const Vec2& a, const Vec2& b)                     { return {std::max(a.x, b.x), std::max(a.y, b.y)}; }
        static Vec2 Clamp(const Vec2& v, const Vec2& mi, const Vec2& ma ) { return Max(Min(v, ma), mi); }

        template <typename U> friend Vec2 operator*(const Vec2& v, U scalar) { return {v.x * scalar, v.y * scalar}; }
        template <typename U> friend Vec2 operator*(U scalar, const Vec2& v) { return {scalar * v.x, scalar * v.y}; }
        template <typename U> friend Vec2 operator/(const Vec2& v, U scalar) { return {v.x / scalar, v.y / scalar}; }
        template <typename U> friend Vec2 operator/(U scalar, const Vec2& v) { return {scalar / v.x, scalar / v.y}; }
        template <typename U> friend Vec2 operator+(const Vec2& v, U scalar) { return {v.x + scalar, v.y + scalar}; }
        template <typename U> friend Vec2 operator+(U scalar, const Vec2& v) { return {scalar + v.x, scalar + v.y}; }
        template <typename U> friend Vec2 operator-(const Vec2& v, U scalar) { return {v.x - scalar, v.y - scalar}; }
        template <typename U> friend Vec2 operator-(U scalar, const Vec2& v) { return {scalar - v.x, scalar - v.y}; }

        friend Vec2 operator*(const Vec2& lhs, const Vec2& rhs) { return {lhs.x * rhs.x, lhs.y * rhs.y}; }
        friend Vec2 operator/(const Vec2& lhs, const Vec2& rhs) { return {lhs.x / rhs.x, lhs.y / rhs.y}; }
        friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }
        friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }

        friend Vec2 operator-(const Vec2& v) { return {-v.x, -v.y}; }

        friend bool operator==(const Vec2& lhs, const Vec2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
        friend bool operator!=(const Vec2& lhs, const Vec2& rhs) { return !(lhs == rhs); }

        Vec2& operator*=(const Vec2& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
        Vec2& operator/=(const Vec2& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
        Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
        Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

        template <typename U> Vec2& operator*=(U scalar) { x *= scalar; y *= scalar; return *this; }
        template <typename U> Vec2& operator/=(U scalar) { x /= scalar; y /= scalar; return *this; }
        template <typename U> Vec2& operator+=(U scalar) { x += scalar; y += scalar; return *this; }
        template <typename U> Vec2& operator-=(U scalar) { x -= scalar; y -= scalar; return *this; }
    };

    // clang-format on

    template <typename T>
    struct BoundingBox {
        Vec2<T> start;
        Vec2<T> end;

        BoundingBox() : start(std::numeric_limits<T>::max()), end(std::numeric_limits<T>::min()) {}

        void Extend(Vec2<T> p) {
            start = Vec2<T>::Min(start, p);
            end = Vec2<T>::Max(end, p);
        }

        void Reset() { *this = BoundingBox(); }

        Vec2<i32> SizeI() const { return Vec2<i32>(end) - Vec2<i32>(start); }

        Vec2<f32> SizeF() const { return Vec2<f32>(end) - Vec2<f32>(start); }
    };

} // namespace Math

using Vec2f = Math::Vec2<f32>;
using Vec2i = Math::Vec2<i32>;
using Vec2u = Math::Vec2<u32>;
