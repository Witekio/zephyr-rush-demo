/**
 * @file      Styles.h
 * @brief     UI Styles definitions
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

#include "Assets.h"

namespace UI {
    namespace Colors {
        constexpr lv_color_t DEBUG_RED = LV_COLOR_MAKE(255, 0, 0);
        constexpr lv_color_t DEBUG_GREEN = LV_COLOR_MAKE(0, 255, 0);
        constexpr lv_color_t DEBUG_YELLOW = LV_COLOR_MAKE(255, 255, 0);
        constexpr lv_color_t DEBUG_PURPLE = LV_COLOR_MAKE(128, 0, 128);

        constexpr lv_color_t WHITE = LV_COLOR_MAKE(255, 255, 255);
        constexpr lv_color_t BLACK = LV_COLOR_MAKE(0, 0, 0);

        constexpr lv_color_t SKYBLUE = LV_COLOR_MAKE(0, 172, 233);
        constexpr lv_color_t SKYBLUE_ACCENT = LV_COLOR_MAKE(103, 211, 249);
        constexpr lv_color_t SKYBLUE_SHADOW = LV_COLOR_MAKE(23, 87, 140);

        constexpr lv_color_t ORANGE = LV_COLOR_MAKE(255, 168, 0);
        constexpr lv_color_t ORANGE_ACCENT = LV_COLOR_MAKE(255, 214, 173);
        constexpr lv_color_t ORANGE_SHADOW = LV_COLOR_MAKE(115, 84, 53);

        constexpr lv_color_t DARKBLUE = LV_COLOR_MAKE(13, 100, 162);
        constexpr lv_color_t DARKBLUE_ACCENT = LV_COLOR_MAKE(1, 54, 97);
        constexpr lv_color_t DARKBLUE_ACCENT2 = LV_COLOR_MAKE(1, 31, 97);

        constexpr lv_color_t RED = LV_COLOR_MAKE(42, 20, 20);
        constexpr lv_color_t RED_ACCENT = LV_COLOR_MAKE(204, 140, 141);

        constexpr lv_color_t LIGHTGRAY = LV_COLOR_MAKE(137, 180, 250);
        constexpr lv_color_t DARKGRAY = LV_COLOR_MAKE(30, 30, 46);
        constexpr lv_color_t DARKGRAY_ACCENT = LV_COLOR_MAKE(49, 50, 68);

        constexpr lv_color_t GREEN_SUCCESS = LV_COLOR_MAKE(115, 230, 115);

        constexpr lv_color_t GRAY = LV_COLOR_MAKE(30, 30, 30);
    } // namespace Colors

    namespace Fonts {
        constexpr const lv_font_t* F16 = &Assets::Gabarito16;
        constexpr const lv_font_t* F22 = &Assets::Gabarito22;
        constexpr const lv_font_t* F32 = &Assets::Gabarito32;

        namespace Symbols {
            constexpr const char* BACKSPACE = "\uE800";
            constexpr const char* GLOBE = "\uE801";
        } // namespace Symbols
    } // namespace Fonts

    namespace Styles {
        namespace Button {
            inline lv_style_t BASE;
            inline lv_style_t ORANGE;
            inline lv_style_t BLUE;
            inline lv_style_t DISABLED;
        } // namespace Button

        namespace Common {
            inline lv_style_t BACKGROUND;
        } // namespace Common

        namespace Text {
            inline lv_style_t DARK16;
            inline lv_style_t DARK22;
            inline lv_style_t DARK32;

            inline lv_style_t LIGHT16;
            inline lv_style_t LIGHT22;
            inline lv_style_t LIGHT32;
        } // namespace Text

        namespace GameOverScreen {
            inline lv_style_t SCORE;
            inline lv_style_t TEXTAREA_HOLDER;
            inline lv_style_t TEXTAREA;
            inline lv_style_t TEXTAREA_PLACEHOLDER;
            inline lv_style_t BAR_CURSOR;
            inline lv_style_t KEYBOARD;
            inline lv_style_t KEYBOARD_ITEMS;
        } // namespace GameOverScreen

        namespace Keypad {
            inline lv_style_t CONT;
            inline lv_style_t BTNM;
            inline lv_style_t INPUT;
            inline lv_style_t ITEMS;
            inline lv_style_t ITEMS_PRESSED;
        }; // namespace Keypad

        namespace PausePopup {
            inline lv_style_t BUTTON;
        } // namespace PausePopup

        namespace ResultPopup {
            inline lv_style_t VBOX;
            inline lv_style_t BODY;
            inline lv_style_t LIST;
            inline lv_style_t SECTION;
            inline lv_style_t CANVAS_BOX;
            inline lv_style_t CLOSE_BUTTON;
        } // namespace ResultPopup

        namespace InfoTab {
            inline lv_style_t LIST;
            inline lv_style_t SECTION;
            inline lv_style_t SCROLLBAR_BOX;
            inline lv_style_t SCROLLBAR_TRACK;
            inline lv_style_t SCROLLBAR_THUMB;

            inline lv_style_t METRICS_TABLE;
            inline lv_style_t METRICS_TABLE_ROW;
            inline lv_style_t METRICS_TABLE_ROW_KEY;
            inline lv_style_t METRICS_TABLE_ROW_VALUE;

        } // namespace InfoTab

        namespace LeaderboardTab {
            inline lv_style_t TABVIEW;
            inline lv_style_t TABVIEW_BAR;
            inline lv_style_t TABVIEW_BAR_SELECTED;
            inline lv_style_t TAB;
            inline lv_style_t PILL;
            inline lv_style_t PILL_RANK;
            inline lv_style_t PILL_SCORE;
            inline lv_style_t PILL_DISABLED;
            inline lv_style_t LIST;
            inline lv_style_t SCROLLBAR;
        } // namespace LeaderboardTab

        namespace SettingsTab {
            inline lv_style_t BUTTON;
            inline lv_style_t DANGER_BUTTON;
        } // namespace SettingsTab

        namespace FreeDrawTab {
            inline lv_style_t HEADER_BOX;
            inline lv_style_t HEADER_PILL;
            inline lv_style_t INFERENCE_LABEL_PILL;
            inline lv_style_t INFERENCE_LABEL;
            inline lv_style_t INFERENCE_PCT_LABEL;
        } // namespace FreeDrawTab

        void Init();
    } // namespace Styles
} // namespace UI
