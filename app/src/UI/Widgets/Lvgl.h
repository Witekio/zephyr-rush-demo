/**
 * @file      Lvgl.h
 * @brief     LVGL Widgets declaration
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

#include "UI/Core/Widget.h"

namespace LV {
    LV_WIDGET(Obj, lv_obj_create, &lv_obj_class);
    LV_WIDGET(Button, lv_button_create, &lv_button_class);
    LV_WIDGET(Label, lv_label_create, &lv_label_class);
    LV_WIDGET(Image, lv_image_create, &lv_image_class);
    LV_WIDGET(TabView, lv_tabview_create, &lv_tabview_class);
    LV_WIDGET(TileView, lv_tileview_create, &lv_tileview_class);
    LV_WIDGET(TextArea, lv_textarea_create, &lv_textarea_class);
    LV_WIDGET(Keyboard, lv_keyboard_create, &lv_keyboard_class);
    LV_WIDGET(Canvas, lv_canvas_create, &lv_canvas_class);
    LV_WIDGET(ButtonMatrix, lv_buttonmatrix_create, &lv_buttonmatrix_class);
} // namespace LV
