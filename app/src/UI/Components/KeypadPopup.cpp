/**
 * @file      KeypadPopup.cpp
 * @brief     UI Keypad popup component implementation
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

#include "KeypadPopup.h"

#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"

#include <cassert>
#include <cstring>

KeypadPopup& KeypadPopup::Create(lv_obj_t* parent) {
    auto* root = Popup::Create(parent);
    Build(root);
    Clear();
    return *this;
}

void KeypadPopup::Clear() {
    count = 0;
    for (auto& c : buffer)
        c = '.';
    buffer.back() = '\0';
}

void KeypadPopup::OnSucess(SuccessCb cb, void* usrData_) {
    onSucessCb = cb;
    usrData = usrData_;
}

void KeypadPopup::Build(lv_obj_t* parent) {
    auto vbox = VBox::Create(parent);
    lv_obj_set_size(vbox, 240, LV_SIZE_CONTENT);
    lv_obj_set_flex_align(vbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_center(vbox);

    lv_obj_add_style(vbox, &UI::Styles::Keypad::CONT, 0);

    {
        auto box = Box::Create(vbox);
        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);

        auto closeButton = LV::Button::Create(box);
        lv_obj_add_style(closeButton, &UI::Styles::Keypad::ITEMS, 0);
        lv_obj_set_size(closeButton, 32, 32);
        lv_obj_align(closeButton, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_obj_add_event_cb(
            closeButton,
            [](lv_event_t* e) {
                auto* self = static_cast<KeypadPopup*>(lv_event_get_user_data(e));
                self->Clear();
                self->Hide();
            },
            LV_EVENT_CLICKED, this);

        auto closeIcon = LV::Image::Create(closeButton);
        lv_image_set_src(closeIcon, &Assets::CloseIcon);
        lv_obj_center(closeIcon);
    }

    {
        auto box = Box::Create(vbox);
        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);

        codeLabel = LV::Label::Create(box);
        lv_obj_center(codeLabel);
        lv_label_set_text_static(codeLabel, buffer.data());
        lv_obj_add_style(codeLabel, &UI::Styles::Keypad::INPUT, 0);

        shakeParams = {
            .obj = codeLabel,
            .duration = 500,
            .cycles = 3.0f,
            .amplitude = 6.0f,
        };
    }

    {
        // clang-format off
        static constexpr const char* BTNM_MAP[] = {
            "1", "2", "3", "\n",
            "4", "5", "6", "\n",
            "7", "8", "9", "\n",
            " ", "0", " ",
            nullptr,
        };
        // clang-format on

        auto box = Box::Create(vbox);
        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_remove_flag(box, LV_OBJ_FLAG_SCROLLABLE);

        btnm = LV::ButtonMatrix::Create(box);
        lv_buttonmatrix_set_map(btnm, BTNM_MAP);
        lv_obj_set_size(btnm, 216, 260);
        lv_obj_center(btnm);

        auto items = static_cast<lv_style_selector_t>(LV_PART_ITEMS);
        lv_obj_add_style(btnm, &UI::Styles::Keypad::BTNM, 0);
        lv_obj_add_style(btnm, &UI::Styles::Keypad::ITEMS, items);
        lv_obj_add_style(btnm, &UI::Styles::Keypad::ITEMS_PRESSED, items | LV_STATE_CHECKED);

        lv_buttonmatrix_set_button_ctrl_all(btnm, LV_BUTTONMATRIX_CTRL_NO_REPEAT);
        lv_buttonmatrix_set_button_ctrl(btnm, 9, LV_BUTTONMATRIX_CTRL_HIDDEN);
        lv_buttonmatrix_set_button_ctrl(btnm, 11, LV_BUTTONMATRIX_CTRL_HIDDEN);

        lv_obj_add_event_cb(btnm, LV_BIND_EVENT_CB(KeypadPopup, HandleInput), LV_EVENT_VALUE_CHANGED, this);
    }

    lv_obj_remove_flag(vbox, LV_OBJ_FLAG_SCROLLABLE);
}

void KeypadPopup::HandleInput() {
    u32 id = lv_buttonmatrix_get_selected_button(btnm);
    const char* txt = lv_buttonmatrix_get_button_text(btnm, id);
    if (!txt)
        return;

    if (count < (N - 1))
        buffer[count++] = txt[0];

    if (count == (N - 1)) {
        bool valid = strcmp(buffer.data(), kPassword) == 0;
        if (valid) {
            assert(onSucessCb);
            onSucessCb(usrData);
        } else {
            Animation::Shake(&shakeParams);
        }
        Clear();
    }

    lv_label_set_text_static(codeLabel, buffer.data());
}
