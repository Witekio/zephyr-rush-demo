/**
 * @file      ResultPopup.h
 * @brief     UI Result popup component header
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

#include "Core/Inference/InferenceTask.h"
#include "UI/Components/List.h"
#include "UI/Core/Popup.h"
#include "UI/Widgets/Widgets.h"

class ResultPopup final : public Popup {
public:
    explicit ResultPopup(InferenceTask& task);

    void Create(lv_obj_t* parent);
    void Refresh();

    void Update();
    void SetID(u32 id);
    void Clear();

private:
    void Build(lv_obj_t* parent);

    void Draw();
    void DrawCanvas();
    void DrawPredictions();

private:
    // Inference result list
    static constexpr u32 TopN = 10;

    // Canvas
    static constexpr u32 kBlockSize = 6;
    static constexpr u32 kWidth = 28 * kBlockSize;
    static constexpr u32 kHeight = 28 * kBlockSize;

private:
    List list;
    LV::Label titleLabel;
    LV::Canvas canvas;

    Draw::Canvas<kWidth, kHeight> canvasStorage;
    InferenceTask& task;
    u32 id = -1;
};
