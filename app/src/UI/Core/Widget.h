/**
 * @file      Widget.h
 * @brief     Generic Lvgl widget wrapper
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

#include <cassert>

#include <lvgl.h>

/*
 * A tiny typed layer over LVGL's lv_obj_t*, without writing real bindings.
 *
 * - Types name widgets, instead of an lv_obj_t* for everything
 * - Easy to define custom widgets on top of LVGL
 * - No overhead
 */
template <typename Derived, auto Constructor, const lv_obj_class_t* Class>
struct Widget {
    lv_obj_t* obj = nullptr;

    Widget() = default;

    explicit Widget(lv_obj_t* o) : obj(o) {
        assert((o == nullptr || lv_obj_get_class(o) == Class) && "Widget: class mismatch on construction");
    }

    static Derived Create(lv_obj_t* parent) { return Derived(Constructor(parent)); }

    static Derived From(lv_obj_t* obj) { return Derived(obj); }

    static Derived FromEvent(lv_event_t* e) { return Derived(static_cast<lv_obj_t*>(lv_event_get_user_data(e))); }

    operator lv_obj_t*() const { return obj; }

    explicit operator bool() const { return obj != nullptr; }
};

#define LV_WIDGET(Name, CreateFn, Class)                                                                          \
    struct Name : Widget<Name, CreateFn, Class> {                                                                 \
        using Widget::Widget;                                                                                     \
    }
