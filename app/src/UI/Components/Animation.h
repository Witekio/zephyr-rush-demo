/**
 * @file      Animation.h
 * @brief     UI Animation component header
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

#include "Core/Base.h"

#include <lvgl.h>

namespace Animation {
    struct ShakeParams {
        lv_obj_t* obj = nullptr;
        u32 duration = 500;
        f32 cycles = 3.0f;
        f32 amplitude = 6.0f;
    };

    void Shake(ShakeParams* params);
} // namespace Animation
