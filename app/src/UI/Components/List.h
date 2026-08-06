/**
 * @file      List.h
 * @brief     UI List component header
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

class List {
public:
    struct Style {
        lv_style_t* Body = nullptr;
        lv_style_t* List = nullptr;
        lv_style_t* Section = nullptr;
        lv_style_t* BarBox = nullptr;
        lv_style_t* BarTrack = nullptr;
        lv_style_t* BarThumb = nullptr;

        i32 ScrollWidth = 12;
    };

public:
    List() = default;

    void Create(lv_obj_t* parent, const Style& style);

    u32 Size() const;
    lv_obj_t* Obj();
    lv_obj_t* Add();
    lv_obj_t* Get(u32 idx);
    void Refresh();

private:
    lv_obj_t* CreateBody(lv_obj_t* parent) const;
    lv_obj_t* CreateScrollableList(lv_obj_t* parent) const;
    lv_obj_t* CreateScrollbar(lv_obj_t* parent, lv_obj_t* target) const;

private:
    lv_obj_t* list;
    Style style;
};
