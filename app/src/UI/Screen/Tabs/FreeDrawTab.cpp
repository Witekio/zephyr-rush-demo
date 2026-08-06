/**
 * @file      FreeDrawTab.cpp
 * @brief     UI Free draw tab implementation
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

#include "FreeDrawTab.h"

#include "UI/Core/Locale.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"

FreeDrawTab::FreeDrawTab(Context& ctx) noexcept : Screen(ctx), canvas(ctx.drawEngine), popup(ctx.inferenceTask) {}

void FreeDrawTab::Create() {
    // Canvas
    {
        canvas.Create(Root());
        lv_obj_set_size(canvas.Obj(), kScreenWidth, kScreenHeight);
    }

    {
        {
            auto box = Box::Create(Root());
            lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);
            lv_obj_align(box, LV_ALIGN_TOP_MID, 0, 0);
            lv_obj_add_style(box, &UI::Styles::FreeDrawTab::HEADER_BOX, 0);

            auto hbox = HBox::Create(box);
            lv_obj_set_size(hbox, lv_pct(100), 40);
            lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
            lv_obj_add_style(hbox, &UI::Styles::FreeDrawTab::HEADER_PILL, 0);

            auto* inferenceLabelBox = lv_obj_create(hbox);
            lv_obj_remove_style_all(inferenceLabelBox);
            lv_obj_set_size(inferenceLabelBox, lv_pct(80), lv_pct(100));
            lv_obj_add_style(inferenceLabelBox, &UI::Styles::FreeDrawTab::INFERENCE_LABEL_PILL, 0);

            auto* inferencePctLabelBox = lv_obj_create(hbox);
            lv_obj_remove_style_all(inferencePctLabelBox);
            lv_obj_set_size(inferencePctLabelBox, lv_pct(20), lv_pct(100));

            inferenceLabel = LV::Label::Create(inferenceLabelBox);
            lv_obj_set_size(inferenceLabel, lv_pct(100), lv_pct(90));
            lv_obj_center(inferenceLabel);
            lv_label_set_long_mode(inferenceLabel, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);
            lv_obj_add_style(inferenceLabelBox, &UI::Styles::FreeDrawTab::INFERENCE_LABEL, 0);

            inferencePctLabel = LV::Label::Create(inferencePctLabelBox);
            lv_obj_set_size(inferencePctLabel, lv_pct(100), lv_pct(90));
            lv_obj_center(inferencePctLabel);
            lv_obj_add_style(inferencePctLabel, &UI::Styles::FreeDrawTab::INFERENCE_PCT_LABEL, 0);
        }
    }

    {
        auto hbox = HBox::Create(Root());
        lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_align(hbox, LV_ALIGN_BOTTOM_MID, 0, 0);

        lv_obj_set_style_pad_all(hbox, 20, 0);

        auto clearButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(clearButton, LV_BIND_EVENT_CB(FreeDrawTab, OnClearPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(clearButton, 48, 48);
        lv_obj_add_style(clearButton, &UI::Styles::Button::BLUE, 0);

        auto clearIcon = LV::Image::Create(clearButton);
        lv_image_set_src(clearIcon, &Assets::ClearIcon);
        lv_obj_center(clearIcon);

        auto undoButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(undoButton, LV_BIND_EVENT_CB(FreeDrawTab, OnUndoPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(undoButton, 48, 48);
        lv_obj_add_style(undoButton, &UI::Styles::Button::BLUE, 0);

        auto undoIcon = LV::Image::Create(undoButton);
        lv_image_set_src(undoIcon, &Assets::UndoIcon);
        lv_obj_center(undoIcon);

        infoButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(infoButton, LV_BIND_EVENT_CB(FreeDrawTab, OnInfoPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(infoButton, 48, 48);
        lv_obj_add_style(infoButton, &UI::Styles::Button::ORANGE, 0);
        lv_obj_add_style(infoButton, &UI::Styles::Button::DISABLED, LV_STATE_DISABLED);
        lv_obj_add_state(infoButton, LV_STATE_DISABLED);

        auto infoIcon = LV::Image::Create(infoButton);
        lv_image_set_src(infoIcon, &Assets::PlusIcon);
        lv_obj_center(infoIcon);
    }

    // Popup
    {
        popup.Create(Root());
        popup.Hide();
        popup.Refresh();
    }
}

void FreeDrawTab::Refresh() {
    popup.Refresh();
}

void FreeDrawTab::OnEnter(const std::any&) {
    ResetState();
}

void FreeDrawTab::OnExit() {
    ResetState();
}

void FreeDrawTab::Update() {
    auto& task = ctx.inferenceTask;
    if (task.Ready()) {
        if (inferenceID == task.ID() && !predictionApplied) {
            auto prediction = task.GetPredictions()[0];
            lv_label_set_text_static(inferenceLabel, Locale::T(prediction.label));
            lv_label_set_text_fmt(inferencePctLabel, "%u%%", static_cast<u32>(prediction.percentage));
            predictionApplied = true;
            lv_obj_remove_state(infoButton, LV_STATE_DISABLED);
        }

        if (canvas.CaptureInto(task)) {
            inferenceID = task.ID();
            predictionApplied = false;
            WorkerThread::Get().Submit(task);
        }
    }

    if (!popup.Hidden()) {
        popup.Update();
    }
}

void FreeDrawTab::OnClearPress() {
    ResetState();
}

void FreeDrawTab::OnUndoPress() {
    canvas.Undo();
    if (canvas.Empty())
        ResetState();
}

void FreeDrawTab::OnInfoPress() {
    popup.SetID(ctx.drawEngine.Version());
    popup.Show();
}

void FreeDrawTab::ResetState() {
    if (!canvas.Empty())
        canvas.Clear();

    lv_label_set_text_static(inferenceLabel, "");
    lv_label_set_text_static(inferencePctLabel, "");
    popup.Clear();
    popup.Hide();
    inferenceID = -1;
    lv_obj_add_state(infoButton, LV_STATE_DISABLED);
}
