/**
 * @file      List.cpp
 * @brief     UI List component implementation
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

#include "List.h"

#include <cassert>

namespace {
    void ScrollEventHandler(lv_event_t* e) {
        auto* scrollbox = static_cast<lv_obj_t*>(lv_event_get_target(e));
        auto* box = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
        auto* bar = lv_obj_get_child(box, 0);

        i32 scrollY = lv_obj_get_scroll_y(scrollbox);
        i32 scrollBottom = lv_obj_get_scroll_bottom(scrollbox);
        i32 viewHeight = lv_obj_get_height(scrollbox);

        i32 maxScroll = scrollY + scrollBottom;

        if (maxScroll <= 0) {
            lv_obj_add_flag(box, LV_OBJ_FLAG_HIDDEN);
            return;
        }

        lv_obj_remove_flag(box, LV_OBJ_FLAG_HIDDEN);

        i32 totalContent = viewHeight + maxScroll;

        f32 viewRatio = viewHeight / static_cast<f32>(totalContent);
        f32 scrollRatio = scrollY / static_cast<f32>(maxScroll);

        i32 thumbSize = viewRatio * 100;
        i32 thumbStart = scrollRatio * (100 - thumbSize);
        i32 thumbEnd = thumbStart + thumbSize;

        lv_bar_set_start_value(bar, thumbStart, LV_ANIM_OFF);
        lv_bar_set_value(bar, thumbEnd, LV_ANIM_OFF);
    }
} // namespace

void List::Create(lv_obj_t* parent, const Style& style) {
    this->style = style;
    auto* body = CreateBody(parent);
    list = CreateScrollableList(body);
    CreateScrollbar(body, list);
}

u32 List::Size() const {
    return lv_obj_get_child_count(list);
}

lv_obj_t* List::Obj() {
    return list;
}

lv_obj_t* List::Add() {
    auto* section = lv_obj_create(list);
    lv_obj_remove_style_all(section);
    lv_obj_set_size(section, lv_pct(100), LV_SIZE_CONTENT);

    if (style.Section)
        lv_obj_add_style(section, style.Section, 0);

    return section;
}

lv_obj_t* List::Get(u32 idx) {
    assert(idx < lv_obj_get_child_count(list));
    return lv_obj_get_child(list, idx);
}

void List::Refresh() {
    lv_obj_update_layout(list);
    lv_obj_send_event(list, LV_EVENT_SCROLL, nullptr);
}

lv_obj_t* List::CreateBody(lv_obj_t* parent) const {
    auto* body = lv_obj_create(parent);
    lv_obj_remove_style_all(body);
    lv_obj_set_size(body, lv_pct(100), lv_pct(100));

    lv_obj_set_flex_align(body, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    if (style.Body)
        lv_obj_add_style(body, style.Body, 0);

    return body;
}

lv_obj_t* List::CreateScrollableList(lv_obj_t* parent) const {
    auto* scrollbox = lv_obj_create(parent);
    lv_obj_remove_style_all(scrollbox);
    lv_obj_set_height(scrollbox, lv_pct(100));
    lv_obj_set_flex_flow(scrollbox, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scrollbar_mode(scrollbox, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flex_grow(scrollbox, 1);

    if (style.List)
        lv_obj_add_style(scrollbox, style.List, 0);

    return scrollbox;
}

lv_obj_t* List::CreateScrollbar(lv_obj_t* parent, lv_obj_t* target) const {
    auto* box = lv_obj_create(parent);
    lv_obj_remove_style_all(box);
    lv_obj_set_size(box, style.ScrollWidth, lv_pct(100));

    lv_obj_add_flag(box, LV_OBJ_FLAG_HIDDEN);

    auto* bar = lv_bar_create(box);
    lv_obj_remove_style_all(bar);
    lv_obj_set_size(bar, lv_pct(100), lv_pct(100));
    lv_obj_center(bar);
    lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);
    lv_bar_set_range(bar, 100, 0);
    lv_obj_add_event_cb(target, ScrollEventHandler, LV_EVENT_SCROLL, box);

    if (style.BarBox)
        lv_obj_add_style(box, style.BarBox, 0);

    if (style.BarTrack)
        lv_obj_add_style(bar, style.BarTrack, 0);

    if (style.BarThumb)
        lv_obj_add_style(bar, style.BarThumb, LV_PART_INDICATOR);

    return box;
}
