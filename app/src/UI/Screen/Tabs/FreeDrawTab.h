/**
 * @file      FreeDrawTab.h
 * @brief     UI Free draw tab header
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

#include "UI/Components/Canvas.h"
#include "UI/Components/ResultPopup.h"
#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class FreeDrawTab final : public Screen {
public:
    explicit FreeDrawTab(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;
    void Update() override;

    void OnEnter(const std::any& payload) override;
    void OnExit() override;

private:
    void OnClearPress();
    void OnUndoPress();
    void OnInfoPress();

    void ResetState();

private:
    Canvas canvas;

    LV::Label inferenceLabel;
    LV::Label inferencePctLabel;
    LV::Button infoButton;

    ResultPopup popup;
    u32 inferenceID = -1;
    bool predictionApplied = true;
};
