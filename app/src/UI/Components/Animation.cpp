/**
 * @file      Animation.cpp
 * @brief     UI Animation component implementation
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

#include "Animation.h"

#include <cassert>
#include <cmath>
#include <numbers>

void Animation::Shake(Animation::ShakeParams* params) {
    constexpr auto kAnimationCb = [](void* data, i32 tick) {
        auto& [obj, duration, cycles, amplitude] = *static_cast<Animation::ShakeParams*>(data);
        f32 angle = static_cast<f32>(tick) / duration * 2.0f * std::numbers::pi_v<f32> * cycles;
        f32 t = static_cast<f32>(tick) / duration;
        i32 x = static_cast<i32>(std::sin(angle) * amplitude * (1.0f - t));
        lv_obj_set_style_translate_x(obj, x, 0);
    };

    assert(params->obj);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, params);
    lv_anim_set_exec_cb(&a, kAnimationCb);
    lv_anim_set_values(&a, 0, static_cast<int32_t>(params->duration));
    lv_anim_set_duration(&a, params->duration);
    lv_anim_start(&a);
}
