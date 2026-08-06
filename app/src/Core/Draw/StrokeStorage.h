/**
 * @file      StrokeStorage.h
 * @brief     Compact storage for strokes
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

#include <array>

#include "CircularIndex.h"
#include "Core/Base.h"
#include "Rasterizer.h"

namespace Draw {
    template <u32 MaxPoints>
    class StrokeStorage {
        using Point = Math::Vec2<u16>;

    public:
        void PushPoint(u16 x, u16 y) { Push(Point{x, y}); }

        void PushSeparator() { Push(MakeSeparator()); }

        bool Undo() {
            if (index.Empty())
                return false;

            index.Pop();
            index.Pop();

            while (index.CanPop() && !IsSeparator(points[index.Pop()]))
                ;

            if (index.Empty()) {
                index.Reset();
                return true;
            }

            index.Push();
            return true;
        }

        void Reset() { index.Reset(); }

        bool Empty() const { return index.Empty(); }

        template <u32 W, u32 H>
        void RasterTo(Canvas<W, H>& canvas, Rasterizer& rasterizer) const {
            Point prev = MakeSeparator();
            for (u32 i = 0; i < index.Size(); i++) {
                Point point = points[index.Nth(i)];

                if (IsSeparator(point)) {
                    prev = MakeSeparator();
                    continue;
                }

                auto a = Vec2f::From(IsSeparator(prev) ? point : prev);
                auto b = Vec2f::From(point);

                rasterizer.Line(canvas, a, b);
                prev = point;
            }
        }

        using BBox = Math::BoundingBox<u16>;

        BBox ComputeBBox() const {
            BBox bbox;
            for (u32 i = 0; i < index.Size(); i++) {
                auto point = points[index.Nth(i)];
                if (!IsSeparator(point))
                    bbox.Extend(point);
            }
            return bbox;
        }

    private:
        static constexpr u16 kSeparator = UINT16_MAX;

        static Point MakeSeparator() { return Point{kSeparator, kSeparator}; }

        static bool IsSeparator(Point p) { return p.x == kSeparator; }

        void Push(Point p) { points[index.Push()] = p; }

    private:
        std::array<Point, MaxPoints> points;
        CircularIndex<MaxPoints> index;
    };
} // namespace Draw
