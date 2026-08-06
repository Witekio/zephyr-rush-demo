/**
 * @file      Keyboard.cpp
 * @brief     LVGL opinionated keyboard implementation
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

#include "Keyboard.h"

#include <cstring>

#include "Core/Base.h"
#include "UI/Theme/Styles.h"

// clang-format off
#define SBS UI::Fonts::Symbols::BACKSPACE
#define SBG UI::Fonts::Symbols::GLOBE

#define W4 LV_BUTTONMATRIX_CTRL_WIDTH_4
#define W6 LV_BUTTONMATRIX_CTRL_WIDTH_6
#define H1 (lv_buttonmatrix_ctrl_t)(LV_BUTTONMATRIX_CTRL_HIDDEN | LV_BUTTONMATRIX_CTRL_WIDTH_1)
#define H2 (lv_buttonmatrix_ctrl_t)(LV_BUTTONMATRIX_CTRL_HIDDEN | LV_BUTTONMATRIX_CTRL_WIDTH_2)
#define H3 (lv_buttonmatrix_ctrl_t)(LV_BUTTONMATRIX_CTRL_HIDDEN | LV_BUTTONMATRIX_CTRL_WIDTH_3)

static const char* const kMapQwerty[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",      "\n", // 10
    " ", "A", "S", "D", "F", "G", "H", "J", "K", "L", " ", "\n", //  9
    SBG, " ", "Z", "X", "C", "V", "B", "N", "M", " ", SBS,       //  7
    nullptr,
};

static const lv_buttonmatrix_ctrl_t kCtrlQwerty[] = {
    W4, W4, W4, W4, W4, W4, W4, W4, W4, W4,
    H2, W4, W4, W4, W4, W4, W4, W4, W4, W4, H2,
    W6, H2, W4, W4, W4, W4, W4, W4, W4, H2, W6,
};

static const char* const kMapAzerty[] = {
    "A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", "\n", // 10
    "Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "\n", // 10
    SBG, " ", "W", "X", "C", "V", "B", "N", " ", SBS,       //  6
    nullptr,
};

static const lv_buttonmatrix_ctrl_t kCtrlAzerty[] = {
    W4, W4, W4, W4, W4, W4, W4, W4, W4, W4,
    W4, W4, W4, W4, W4, W4, W4, W4, W4, W4,
    W6, H3, W4, W4, W4, W4, W4, W4, H3, W6,
};
// clang-format on

namespace {
    void OnKeyboardEvent(lv_event_t* e) {
        auto* kb = lv_event_get_target_obj(e);
        auto* ta = lv_keyboard_get_textarea(kb);

        u32 btnId = lv_buttonmatrix_get_selected_button(kb);

        if (btnId == LV_BUTTONMATRIX_BUTTON_NONE)
            return;

        const char* txt = lv_buttonmatrix_get_button_text(kb, btnId);

        if (txt == nullptr)
            return;

        if (strcmp(txt, SBG) == 0) {
            switch (lv_keyboard_get_mode(kb)) {
            case LV_KEYBOARD_MODE_USER_1:
                lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_2);
                return;
            case LV_KEYBOARD_MODE_USER_2:
                lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);
                return;
            default:
                return;
            }
        }

        if (strcmp(txt, SBS) == 0) {
            lv_textarea_delete_char(ta);
            return;
        }

        const char* current = lv_textarea_get_text(ta);
        if (strlen(current) >= 10)
            return;

        lv_textarea_add_text(ta, txt);
    }
} // namespace

LV::Keyboard CustomKeyboard::Create(lv_obj_t* parent) {
    auto keyboard = LV::Keyboard::Create(parent);

    lv_keyboard_set_mode(keyboard, LV_KEYBOARD_MODE_USER_1);
    lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_USER_1, kMapAzerty, kCtrlAzerty);
    lv_keyboard_set_map(keyboard, LV_KEYBOARD_MODE_USER_2, kMapQwerty, kCtrlQwerty);

    lv_obj_remove_event_cb(keyboard, lv_keyboard_def_event_cb);
    lv_obj_add_event_cb(keyboard, OnKeyboardEvent, LV_EVENT_VALUE_CHANGED, nullptr);

    return keyboard;
}
