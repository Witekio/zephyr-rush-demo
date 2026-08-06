/**
 * @file      GameOverScreen.h
 * @brief     UI Game over screen header
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

#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class GameOverScreen final : public Screen {
public:
    explicit GameOverScreen(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;

    void OnEnter(const std::any& payload) override;

private:
    void OnSubmitPress();
    void OnKeyPress() const;

private:
    Payload::GameScore gameScore;

    LV::Label yourScoreIsLabel;
    LV::Label scoreLabel;

    LV::Keyboard keyboard;
    LV::TextArea textarea;
    LV::Button submitButton;
};
