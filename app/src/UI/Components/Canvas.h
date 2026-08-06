/**
 * @file      Canvas.h
 * @brief     UI Canvas component header
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

#include "Core/Inference/InferenceTask.h"
#include "UI/Core/Base.h"
#include "UI/Widgets/Widgets.h"

class Canvas final : public IntoInferenceTask {
public:
    explicit Canvas(DrawEngine& de);

    void Create(lv_obj_t* parent);

    void Clear() const;
    void Undo() const;
    void Freeze();
    void UnFreeze();

    lv_obj_t* Obj() const;
    bool Empty() const;

    // IntoInferenceTask
    bool CaptureInto(InferenceTask& task) const override;

private:
    void OnPress();
    void OnPressing();
    void OnRelease();

private:
    LV::Canvas canvas;
    DrawEngine& drawEngine;
    enum class State : u8 { Freeze, UnFreeze, Normal } state = State::Normal;
};
