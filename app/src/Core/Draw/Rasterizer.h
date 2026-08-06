/**
 * @file      Rasterizer.h
 * @brief     2D AA-Line rasterizer
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

#include "Canvas.h"
#include "Core/Base.h"
#include "Math.h"

#include <algorithm>

namespace Draw {
    class Rasterizer {
    public:
        Rasterizer(f32 antialias, u32 lineWidth, u8 color)
            : antialias(antialias),
              lineWidth(lineWidth),
              color(color) {}

        template <u32 W, u32 H>
        void Line(Canvas<W, H>& dst, Vec2f a, Vec2f b) const {
            a = a * scale + offset;
            b = b * scale + offset;

            f32 r = lineWidth * 0.5f;
            f32 pad = r + antialias;

            Vec2f min = Vec2f::Min(a, b) - Vec2f(pad);
            Vec2f max = Vec2f::Max(a, b) + Vec2f(pad);

            Vec2i start = Vec2i::Max(Vec2i(0), Vec2i(Vec2f::Floor(min)));
            Vec2i end = Vec2i::Min(Vec2i(W, H) - 1, Vec2i(Vec2f::Ceil(max)));

            for (i32 py = start.y; py <= end.y; py++) {
                for (i32 px = start.x; px <= end.x; px++) {
                    Vec2f p = Vec2f(px, py) + 0.5f;
                    f32 d = DistToSegment(p, a, b);
                    f32 t = std::clamp((r - d + antialias) / antialias, 0.0f, 1.0f);
                    f32 alpha = t * t * (3.0f - 2.0f * t); // smoothstep

                    if (alpha > 0.0f) {
                        u8 bg = dst[px, py];
                        dst[px, py] = static_cast<u8>(bg + (color - bg) * alpha);
                    }
                }
            }
        }

        void SetScale(f32 newScale) { scale = newScale; }

        void SetOffset(Vec2f newOffset) { offset = newOffset; }

    private:
        static f32 DistToSegment(Vec2f p, Vec2f a, Vec2f b) {
            Vec2f ab = b - a;
            f32 lenSq = Vec2f::Dot(ab, ab);

            if (lenSq == 0.0f)
                return Vec2f::Dist(p, a);

            f32 t = Vec2f::Dot(p - a, ab) / lenSq;
            t = std::clamp(t, 0.0f, 1.0f);

            Vec2f proj = a + ab * t;
            return Vec2f::Dist(p, proj);
        }

    private:
        Vec2f offset = {0.0f, 0.0f};
        f32 scale = 1.0f;
        f32 antialias;
        u32 lineWidth;
        u8 color;
    };
} // namespace Draw
