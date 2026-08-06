/**
 * @file      Canvas.h
 * @brief     Generic 2D byte storage
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

#include "Core/Base.h"

namespace Draw {
    template <u32 W, u32 H>
    class Canvas {
    public:
        static constexpr u32 kWidth = W;
        static constexpr u32 kHeight = H;

        Canvas() = default;

        void Clear(u8 c) {
            for (auto& p : pixels)
                p = c;
        }

        const u8* Data() const { return pixels.data(); }

        u8& operator[](u32 x, u32 y) { return pixels[y * W + x]; }

        u8 operator[](u32 x, u32 y) const { return pixels[y * W + x]; }

        constexpr u32 Width() const { return kWidth; }

        constexpr u32 Height() const { return kHeight; }

    private:
        std::array<u8, W * H> pixels{};
    };
} // namespace Draw
