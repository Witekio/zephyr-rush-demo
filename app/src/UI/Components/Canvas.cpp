/**
 * @file      Canvas.cpp
 * @brief     UI Canvas component implementation
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

#include "Canvas.h"

#include "Core/Inference/InferenceTask.h"
#include "UI/Core/Utils.h"

namespace {
    Vec2i ToPoint(lv_obj_t* obj) {
        lv_point_t p;
        lv_indev_get_point(lv_indev_active(), &p);
        p.x -= lv_obj_get_x(obj);
        p.y -= lv_obj_get_y(obj);
        return {p.x, p.y};
    }

} // namespace

Canvas::Canvas(DrawEngine& de) : drawEngine(de) {}

void Canvas::Create(lv_obj_t* parent) {
    canvas = LV::Canvas::Create(parent);

    const auto& deCanvas = drawEngine.GetCanvas();
    // LVGL requires a mutable buffer (void*), although we use this canvas as read-only and never use LVGL to
    // write to it.
    lv_canvas_set_buffer(canvas, const_cast<u8*>(deCanvas.Data()), deCanvas.Width(), deCanvas.Height(),
                         LV_COLOR_FORMAT_A8);
    lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_remove_flag(canvas, LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(canvas, LV_BIND_EVENT_CB(Canvas, OnPress), LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(canvas, LV_BIND_EVENT_CB(Canvas, OnPressing), LV_EVENT_PRESSING, this);
    lv_obj_add_event_cb(canvas, LV_BIND_EVENT_CB(Canvas, OnRelease), LV_EVENT_RELEASED, this);
}

void Canvas::Clear() const {
    drawEngine.Clear();
    lv_obj_invalidate(canvas);
}

void Canvas::Undo() const {
    drawEngine.Undo();
    lv_obj_invalidate(canvas);
}

void Canvas::Freeze() {
    drawEngine.EndStroke();
    state = State::Freeze;
}

void Canvas::UnFreeze() {
    state = State::UnFreeze;
}

lv_obj_t* Canvas::Obj() const {
    return canvas;
}

bool Canvas::Empty() const {
    return drawEngine.Empty();
}

bool Canvas::CaptureInto(InferenceTask& task) const {
    if (Empty() || !task.Ready() || task.ID() == drawEngine.Version())
        return false;

    task.Prepare(drawEngine.GetStrokes());
    task.SetID(drawEngine.Version());
    return true;
}

void Canvas::OnPress() {
    if (state == State::Freeze)
        return;

    if (state == State::UnFreeze)
        state = State::Normal;

    auto [x, y] = ToPoint(canvas);
    drawEngine.BeginStroke(x, y);
    lv_obj_invalidate(canvas);
}

void Canvas::OnPressing() {
    if (state == State::Freeze)
        return;

    auto [x, y] = ToPoint(canvas);
    if (state == State::UnFreeze) {
        drawEngine.BeginStroke(x, y);
        state = State::Normal;
        return;
    }

    if (drawEngine.AddPoint(x, y))
        lv_obj_invalidate(canvas);
}

void Canvas::OnRelease() {
    drawEngine.EndStroke();
    lv_obj_invalidate(canvas);
}
