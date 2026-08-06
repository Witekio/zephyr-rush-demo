/**
 * @file      BufferStack.h
 * @brief     Buffer stack storage for undoing / redoing
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

#include "Canvas.h"
#include "CircularIndex.h"
#include "Core/Base.h"

namespace Draw {
    template <u32 W, u32 H, u32 Depth>
    class BufferStack {
        static constexpr u32 kCapacity = Depth;

    public:
        void Push(const Canvas<W, H>& canvas) { buffers[index.Push()] = canvas; }

        bool Undo(Canvas<W, H>& out) {
            if (index.Size() <= 1)
                return false;

            index.Pop();
            out = buffers[index.Top()];
            return true;
        }

        void Reset() { index.Reset(); }

    private:
        std::array<Canvas<W, H>, Depth> buffers;
        CircularIndex<Depth> index;
    };
} // namespace Draw
