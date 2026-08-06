/**
 * @file      KeypadPopup.h
 * @brief     UI Keypad popup component header
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
#include "UI/Components/Animation.h"
#include "UI/Core/Popup.h"
#include "UI/Widgets/Widgets.h"

#include <array>

#include <lvgl.h>

class KeypadPopup final : public Popup {
public:
    using SuccessCb = void (*)(void* usrData);

    KeypadPopup() = default;

    KeypadPopup& Create(lv_obj_t* parent);

    void OnSucess(SuccessCb cb, void* usrData);

private:
    void Clear();
    void Build(lv_obj_t* parent);

    void HandleInput();

private:
    LV::Label codeLabel;
    LV::ButtonMatrix btnm;
    Animation::ShakeParams shakeParams;

    // Password
    static constexpr const char kPassword[] = "00120";
    static constexpr uint32_t N = std::size(kPassword);
    std::array<char, N> buffer;
    u8 count = 0;

    // Callbacks
    SuccessCb onSucessCb = nullptr;
    void* usrData = nullptr;
};
