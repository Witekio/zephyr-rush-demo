/**
 * @file      Box.cpp
 * @brief     Layout related widgets implementation
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

#include "Box.h"

LV::Obj Box::Create(lv_obj_t* parent) {
    auto obj = LV::Obj::Create(parent);
    lv_obj_remove_style_all(obj);
    return obj;
}

LV::Obj HBox::Create(lv_obj_t* parent) {
    auto obj = Box::Create(parent);
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
    return obj;
}

LV::Obj VBox::Create(lv_obj_t* parent) {
    auto obj = Box::Create(parent);
    lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
    return obj;
}
