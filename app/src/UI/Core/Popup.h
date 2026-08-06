/**
 * @file      Popup.h
 * @brief     Generic Popup abstraction
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

#include <lvgl.h>

class Popup {
public:
    Popup() = default;

    lv_obj_t* Create(lv_obj_t* parent) {
        obj = lv_obj_create(parent);
        lv_obj_remove_style_all(obj);
        lv_obj_set_size(obj, lv_pct(100), lv_pct(100));

        lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(obj, LV_OPA_50, 0);

        lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);

        return obj;
    }

    void Show() { lv_obj_remove_flag(obj, LV_OBJ_FLAG_HIDDEN); }

    void Hide() { lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN); }

    bool Hidden() { return lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN); }

private:
    lv_obj_t* obj = nullptr;
};
