/**
 * @file      ResultPopup.cpp
 * @brief     UI Result popup component implementation
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

#include "ResultPopup.h"

#include "UI/Core/Locale.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"

ResultPopup::ResultPopup(InferenceTask& task) : task(task) {}

void ResultPopup::Create(lv_obj_t* parent) {
    auto* root = Popup::Create(parent);
    Build(root);
    Clear();
}

void ResultPopup::Update() {
    if (task.Ready() && task.ID() == id) {
        Draw();
        SetID(-1);
    }
}

void ResultPopup::SetID(u32 id) {
    this->id = id == 0 ? -1 : id;
}

void ResultPopup::Clear() {
    canvasStorage.Clear(0);
    lv_obj_invalidate(canvas);
    for (u32 i = 0; i < list.Size(); i++)
        lv_obj_add_flag(list.Get(i), LV_OBJ_FLAG_HIDDEN);
}

void ResultPopup::Build(lv_obj_t* parent) {
    auto vbox = VBox::Create(parent);
    lv_obj_set_size(vbox, lv_pct(90), lv_pct(95));
    lv_obj_center(vbox);

    lv_obj_add_style(vbox, &UI::Styles::ResultPopup::VBOX, 0);

    {
        auto hbox = HBox::Create(vbox);
        lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        auto titleBox = Box::Create(hbox);
        lv_obj_set_height(titleBox, lv_pct(100));
        lv_obj_set_flex_grow(titleBox, 1);

        titleLabel = LV::Label::Create(titleBox);
        lv_obj_center(titleLabel);
        lv_obj_set_style_text_font(titleLabel, UI::Fonts::F22, 0);
        lv_obj_set_style_text_color(titleLabel, UI::Colors::WHITE, 0);

        auto closeButton = LV::Button::Create(hbox);
        lv_obj_remove_style_all(closeButton);
        lv_obj_add_style(closeButton, &UI::Styles::ResultPopup::CLOSE_BUTTON, 0);
        lv_obj_add_event_cb(closeButton, LV_BIND_EVENT_CB(ResultPopup, Hide), LV_EVENT_CLICKED, this);
        lv_obj_set_size(closeButton, 32, 32);
        lv_obj_align(closeButton, LV_ALIGN_RIGHT_MID, 0, 0);

        auto closeIcon = LV::Image::Create(closeButton);
        lv_image_set_src(closeIcon, &Assets::CloseIcon);
        lv_obj_center(closeIcon);
    }

    {
        auto box = Box::Create(vbox);
        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_grow(box, 1);

        list.Create(box, {
                             .Body = &UI::Styles::ResultPopup::BODY,
                             .List = &UI::Styles::ResultPopup::LIST,
                             .Section = &UI::Styles::ResultPopup::SECTION,
                             .BarTrack = &UI::Styles::InfoTab::SCROLLBAR_TRACK,
                             .BarThumb = &UI::Styles::InfoTab::SCROLLBAR_THUMB,
                         });

        for (u32 i = 0; i < TopN; i++) {
            auto* section = list.Add();
            lv_obj_remove_flag(section, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_flex_flow(section, LV_FLEX_FLOW_ROW);

            auto classLabel = LV::Label::Create(section);
            auto pctLabel = LV::Label::Create(section);

            lv_obj_set_width(classLabel, lv_pct(70));
            lv_obj_set_width(pctLabel, lv_pct(30));

            lv_label_set_long_mode(classLabel, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);

            lv_obj_add_flag(section, LV_OBJ_FLAG_HIDDEN);
        }
    }

    {
        auto box = Box::Create(vbox);

        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_add_style(box, &UI::Styles::ResultPopup::CANVAS_BOX, 0);

        canvasStorage.Clear(0);
        canvas = LV::Canvas::Create(box);
        // LVGL requires a mutable buffer (void*), although we use this canvas as read-only and never use LVGL to
        // write to it.
        lv_canvas_set_buffer(canvas, const_cast<u8*>(canvasStorage.Data()), canvasStorage.Width(),
                             canvasStorage.Height(), LV_COLOR_FORMAT_L8);
        lv_obj_center(canvas);
    }
}

void ResultPopup::Refresh() {
    lv_label_set_text_static(titleLabel, Locale::T(TKey::Infos));
    list.Refresh();
}

void ResultPopup::Draw() {
    DrawCanvas();
    DrawPredictions();
}

void ResultPopup::DrawCanvas() {
    const auto& inferenceCanvas = task.GetCanvas();

    canvasStorage.Clear(0);

    for (u32 y = 0; y < 28; y++) {
        for (u32 x = 0; x < 28; x++) {
            u8 pixelValue = inferenceCanvas[x, y];

            for (u32 dx = 0; dx < kBlockSize; dx++) {
                for (u32 dy = 0; dy < kBlockSize; dy++) {
                    u32 ddx = x * kBlockSize + dy;
                    u32 ddy = y * kBlockSize + dx;
                    canvasStorage[ddx, ddy] = pixelValue;
                }
            }
        }
    }

    lv_obj_invalidate(canvas);
}

void ResultPopup::DrawPredictions() {
    auto predictionBuffer = task.GetPredictions();

    for (u32 i = 0; i < list.Size(); i++) {
        auto* s = list.Get(i);
        auto* label = lv_obj_get_child(s, 0);
        auto* pct = lv_obj_get_child(s, 1);
        auto [predLbl, predPct] = predictionBuffer[i];
        lv_label_set_text_fmt(label, "%s", Locale::T(predLbl));
        lv_label_set_text_fmt(pct, "%u%%", static_cast<u32>(predPct));
        lv_obj_remove_flag(s, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_scroll_to_view(list.Get(0), LV_ANIM_OFF);
    list.Refresh();
}
