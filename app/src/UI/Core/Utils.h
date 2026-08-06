/**
 * @file      Utils.h
 * @brief     UI utilities
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

#define LV_BIND_TIMER_CB(T, Cb) [](lv_timer_t* t) { static_cast<T*>(lv_timer_get_user_data(t))->Cb(); }
#define LV_BIND_TIMER_CB_T(T, Cb) [](lv_timer_t* t) { static_cast<T*>(lv_timer_get_user_data(t))->Cb(t); }
#define LV_BIND_EVENT_CB(T, Cb) [](lv_event_t* e) { static_cast<T*>(lv_event_get_user_data(e))->Cb(); }
#define LV_BIND_EVENT_CB_E(T, Cb) [](lv_event_t* e) { static_cast<T*>(lv_event_get_user_data(e))->Cb(e); }

template <u32 Width>
lv_font_t FixWidthFontFrom(const lv_font_t& font) {
    static constexpr auto fix_w_get_glyph_dsc = [](const lv_font_t* f, lv_font_glyph_dsc_t* g, u32 letter,
                                                   u32 letter_next) -> bool {
        bool ret = lv_font_get_glyph_dsc_fmt_txt(f, g, letter, letter_next);
        if (!ret)
            return ret;

        g->adv_w = Width;
        g->ofs_x = (g->adv_w - g->box_w) / 2;

        return true;
    };

    lv_font_t mono;
    mono = font;
    mono.get_glyph_dsc = fix_w_get_glyph_dsc;
    return mono;
}
