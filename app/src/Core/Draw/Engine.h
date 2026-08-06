/**
 * @file      Engine.h
 * @brief     Centralised management of all drawing-related systems
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
#include <utility>

#include "BufferStack.h"
#include "Canvas.h"
#include "Core/Base.h"
#include "Rasterizer.h"
#include "StrokeStorage.h"

namespace Draw {
    template <u32 W, u32 H, u32 MaxPoints, u32 UndoDepth>
    class Engine {
    public:
        Engine() : rasterizer(2.0f, 6, 255) {
            canvas.Clear(0);
            history.Push(canvas);
        }

        void BeginStroke(i32 x, i32 y) {
            assert(x >= 0 && y >= 0);
            assert(std::cmp_less(x, W) && std::cmp_less(y, H));

            last = Vec2f{static_cast<f32>(x), static_cast<f32>(y)};
            strokes.PushPoint(x, y);
            rasterizer.Line(canvas, last, last);
            version++;
        }

        bool AddPoint(i32 x, i32 y) {
            assert(x >= 0 && y >= 0);
            assert(std::cmp_less(x, W) && std::cmp_less(y, H));

            static constexpr f32 kSmoothingFactor = 0.60f; // [0;1]
            static constexpr f32 kMinDistSq = 6.0f * 6.0f;

            Vec2f cur = {static_cast<f32>(x), static_cast<f32>(y)};
            Vec2f smooth = last * kSmoothingFactor + cur * (1.0f - kSmoothingFactor);

            if (Vec2f::LengthSq(cur - last) < kMinDistSq)
                return false;

            strokes.PushPoint(static_cast<u16>(smooth.x), static_cast<u16>(smooth.y));
            rasterizer.Line(canvas, last, smooth);
            last = smooth;
            version++;
            return true;
        }

        void EndStroke() {
            strokes.PushSeparator();
            history.Push(canvas);
        }

        void Undo() {
            strokes.Undo();
            if (strokes.Empty()) {
                Clear();
                return;
            }

            version++;
            history.Undo(canvas);
        }

        void Clear() {
            version = 0;
            history.Reset();
            canvas.Clear(0);
            history.Push(canvas);
            strokes.Reset();
        }

        bool Empty() const { return version == 0; }

        const Canvas<W, H>& GetCanvas() const { return canvas; }

        const StrokeStorage<MaxPoints>& GetStrokes() const { return strokes; }

        u32 Version() const { return version; }

    private:
        Rasterizer rasterizer;
        Canvas<W, H> canvas;
        StrokeStorage<MaxPoints> strokes;
        BufferStack<W, H, UndoDepth> history;

        Vec2f last;
        u32 version = 0;
    };
} // namespace Draw
