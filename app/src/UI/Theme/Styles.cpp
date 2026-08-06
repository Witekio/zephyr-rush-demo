/**
 * @file      Styles.cpp
 * @brief     UI Styles initialization
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

#include "Styles.h"

#include "UI/Core/Utils.h"

void UI::Styles::Init() {
    // Text
    {
        lv_style_init(&Text::DARK16);
        lv_style_set_text_color(&Text::DARK16, Colors::GRAY);
        lv_style_set_text_font(&Text::DARK16, Fonts::F16);

        lv_style_init(&Text::DARK22);
        lv_style_set_text_color(&Text::DARK22, Colors::GRAY);
        lv_style_set_text_font(&Text::DARK22, Fonts::F22);

        lv_style_init(&Text::DARK32);
        lv_style_set_text_color(&Text::DARK32, Colors::GRAY);
        lv_style_set_text_font(&Text::DARK32, Fonts::F32);

        lv_style_init(&Text::LIGHT16);
        lv_style_set_text_color(&Text::LIGHT16, Colors::WHITE);
        lv_style_set_text_font(&Text::LIGHT16, Fonts::F16);

        lv_style_init(&Text::LIGHT22);
        lv_style_set_text_color(&Text::LIGHT22, Colors::WHITE);
        lv_style_set_text_font(&Text::LIGHT22, Fonts::F22);

        lv_style_init(&Text::LIGHT32);
        lv_style_set_text_color(&Text::LIGHT32, Colors::WHITE);
        lv_style_set_text_font(&Text::LIGHT32, Fonts::F32);
    }

    // Button
    {
        lv_style_init(&Button::BASE);
        lv_style_set_radius(&Button::BASE, 7);
        lv_style_set_outline_width(&Button::BASE, 3);
        lv_style_set_outline_pad(&Button::BASE, -3);
        lv_style_set_text_color(&Button::BASE, Colors::WHITE);
        lv_style_set_text_font(&Button::BASE, Fonts::F22);

        lv_style_init(&Button::ORANGE);
        lv_style_copy(&Button::ORANGE, &Button::BASE);
        lv_style_set_bg_color(&Button::ORANGE, Colors::ORANGE);
        lv_style_set_outline_color(&Button::ORANGE, Colors::ORANGE_ACCENT);
        lv_style_set_shadow_color(&Button::ORANGE, Colors::ORANGE_SHADOW);

        lv_style_init(&Button::BLUE);
        lv_style_copy(&Button::BLUE, &Button::BASE);
        lv_style_set_bg_opa(&Button::BLUE, LV_OPA_COVER);
        lv_style_set_bg_color(&Button::BLUE, Colors::SKYBLUE);
        lv_style_set_outline_color(&Button::BLUE, Colors::SKYBLUE_ACCENT);
        lv_style_set_shadow_color(&Button::BLUE, Colors::SKYBLUE_SHADOW);

        lv_style_init(&Button::DISABLED);
        lv_style_set_recolor_opa(&Button::DISABLED, LV_OPA_50);
    }

    // Common
    {
        lv_style_init(&Common::BACKGROUND);
        lv_style_set_bg_color(&Common::BACKGROUND, Colors::DARKBLUE);
        lv_style_set_bg_opa(&Common::BACKGROUND, LV_OPA_COVER);
    }

    // GameOverScreen
    {
        lv_style_init(&GameOverScreen::SCORE);
        lv_style_merge(&GameOverScreen::SCORE, &Text::DARK32);
        lv_style_set_text_color(&GameOverScreen::SCORE, Colors::WHITE);

        lv_style_init(&GameOverScreen::TEXTAREA_HOLDER);
        lv_style_set_radius(&GameOverScreen::TEXTAREA_HOLDER, 7);
        lv_style_set_bg_color(&GameOverScreen::TEXTAREA_HOLDER, Colors::WHITE);
        lv_style_set_bg_opa(&GameOverScreen::TEXTAREA_HOLDER, LV_OPA_COVER);
        lv_style_set_pad_left(&GameOverScreen::TEXTAREA_HOLDER, 10);

        lv_style_init(&GameOverScreen::TEXTAREA);
        lv_style_set_text_font(&GameOverScreen::TEXTAREA, Fonts::F22);

        lv_style_init(&GameOverScreen::TEXTAREA_PLACEHOLDER);
        lv_style_set_text_font(&GameOverScreen::TEXTAREA_PLACEHOLDER, Fonts::F22);
        lv_style_set_text_opa(&GameOverScreen::TEXTAREA_PLACEHOLDER, LV_OPA_50);

        lv_style_init(&GameOverScreen::BAR_CURSOR);
        lv_style_set_bg_opa(&GameOverScreen::BAR_CURSOR, LV_OPA_TRANSP);
        lv_style_set_border_side(&GameOverScreen::BAR_CURSOR, LV_BORDER_SIDE_LEFT);
        lv_style_set_border_width(&GameOverScreen::BAR_CURSOR, 2);
        lv_style_set_pad_left(&GameOverScreen::BAR_CURSOR, -2);
        lv_style_set_anim_duration(&GameOverScreen::BAR_CURSOR, 600);

        lv_style_init(&GameOverScreen::KEYBOARD);
        lv_style_set_radius(&GameOverScreen::KEYBOARD, 5);
        lv_style_set_bg_color(&GameOverScreen::KEYBOARD, Colors::SKYBLUE);
        lv_style_set_bg_opa(&GameOverScreen::KEYBOARD, LV_OPA_COVER);
        lv_style_set_pad_all(&GameOverScreen::KEYBOARD, 2);
        lv_style_set_pad_gap(&GameOverScreen::KEYBOARD, 2);

        lv_style_init(&GameOverScreen::KEYBOARD_ITEMS);
        lv_style_set_radius(&GameOverScreen::KEYBOARD_ITEMS, 5);
        lv_style_set_bg_color(&GameOverScreen::KEYBOARD_ITEMS, Colors::DARKBLUE_ACCENT);
        lv_style_set_bg_opa(&GameOverScreen::KEYBOARD_ITEMS, LV_OPA_COVER);
        lv_style_set_text_color(&GameOverScreen::KEYBOARD_ITEMS, Colors::WHITE);
        lv_style_set_text_font(&GameOverScreen::KEYBOARD_ITEMS, Fonts::F16);
    }

    // Keypad
    {
        lv_style_init(&Keypad::CONT);
        lv_style_set_pad_all(&Keypad::CONT, 15);
        lv_style_set_pad_row(&Keypad::CONT, 10);
        lv_style_set_radius(&Keypad::CONT, 12);
        lv_style_set_bg_color(&Keypad::CONT, Colors::DARKGRAY);
        lv_style_set_bg_opa(&Keypad::CONT, LV_OPA_COVER);
        lv_style_set_border_width(&Keypad::CONT, 0);

        lv_style_init(&Keypad::BTNM);
        lv_style_set_bg_opa(&Keypad::BTNM, LV_OPA_TRANSP);
        lv_style_set_border_width(&Keypad::BTNM, 0);
        lv_style_set_pad_gap(&Keypad::BTNM, 8);

        static lv_font_t fixWidthGabarito = FixWidthFontFrom<30>(*Fonts::F32);
        lv_style_init(&Keypad::INPUT);
        lv_style_set_text_font(&Keypad::INPUT, &fixWidthGabarito);
        lv_style_set_text_color(&Keypad::INPUT, Colors::WHITE);
        lv_style_set_pad_top(&Keypad::INPUT, 8);

        lv_style_init(&Keypad::ITEMS);
        lv_style_set_text_font(&Keypad::ITEMS, Fonts::F22);
        lv_style_set_radius(&Keypad::ITEMS, LV_RADIUS_CIRCLE);
        lv_style_set_border_width(&Keypad::ITEMS, 0);
        lv_style_set_shadow_width(&Keypad::ITEMS, 0);
        lv_style_set_bg_color(&Keypad::ITEMS, Colors::DARKGRAY_ACCENT);
        lv_style_set_text_color(&Keypad::ITEMS, Colors::WHITE);

        lv_style_init(&Keypad::ITEMS_PRESSED);
        lv_style_copy(&Keypad::ITEMS_PRESSED, &Keypad::ITEMS);
        lv_style_set_text_color(&Keypad::ITEMS_PRESSED, Colors::WHITE);
        lv_style_set_bg_color(&Keypad::ITEMS_PRESSED, Colors::LIGHTGRAY);
    }

    // PausePopup
    {
        lv_style_init(&PausePopup::BUTTON);
        lv_style_set_bg_opa(&PausePopup::BUTTON, LV_OPA_TRANSP);
        lv_style_set_shadow_opa(&PausePopup::BUTTON, LV_OPA_TRANSP);
        lv_style_set_text_font(&PausePopup::BUTTON, Fonts::F22);
        lv_style_set_text_color(&PausePopup::BUTTON, Colors::WHITE);
    }

    // ResultPopup
    {
        lv_style_init(&ResultPopup::VBOX);
        lv_style_set_bg_color(&ResultPopup::VBOX, Colors::DARKBLUE);
        lv_style_set_bg_opa(&ResultPopup::VBOX, LV_OPA_COVER);
        lv_style_set_radius(&ResultPopup::VBOX, 10);
        lv_style_set_pad_all(&ResultPopup::VBOX, 15);
        lv_style_set_pad_row(&ResultPopup::VBOX, 10);

        lv_style_init(&ResultPopup::BODY);
        lv_style_set_pad_column(&ResultPopup::BODY, 5);
        lv_style_set_radius(&ResultPopup::BODY, 10);

        lv_style_init(&ResultPopup::LIST);
        lv_style_set_pad_row(&ResultPopup::LIST, 5);

        lv_style_init(&ResultPopup::SECTION);
        lv_style_set_radius(&ResultPopup::SECTION, 10);
        lv_style_set_bg_color(&ResultPopup::SECTION, Colors::WHITE);
        lv_style_set_bg_opa(&ResultPopup::SECTION, LV_OPA_COVER);
        lv_style_set_text_font(&ResultPopup::SECTION, Fonts::F22);
        lv_style_set_text_color(&ResultPopup::SECTION, Colors::GRAY);
        lv_style_set_pad_column(&ResultPopup::SECTION, 10);
        lv_style_set_pad_left(&ResultPopup::SECTION, 6);
        lv_style_set_pad_right(&ResultPopup::SECTION, 6);

        lv_style_init(&ResultPopup::CANVAS_BOX);
        lv_style_set_bg_color(&ResultPopup::CANVAS_BOX, Colors::BLACK);
        lv_style_set_bg_opa(&ResultPopup::CANVAS_BOX, LV_OPA_COVER);
        lv_style_set_pad_all(&ResultPopup::CANVAS_BOX, 10);
        lv_style_set_radius(&ResultPopup::CANVAS_BOX, 10);

        lv_style_init(&ResultPopup::CLOSE_BUTTON);
        lv_style_set_bg_opa(&ResultPopup::CLOSE_BUTTON, LV_OPA_TRANSP);
        lv_style_set_shadow_opa(&ResultPopup::CLOSE_BUTTON, LV_OPA_TRANSP);
        lv_style_set_pad_top(&ResultPopup::CLOSE_BUTTON, 6);
        lv_style_set_text_font(&ResultPopup::CLOSE_BUTTON, Fonts::F32);
        lv_style_set_text_color(&ResultPopup::CLOSE_BUTTON, Colors::WHITE);
    }

    // InfoTab
    {
        lv_style_init(&InfoTab::LIST);
        lv_style_set_pad_all(&InfoTab::LIST, 10);
        lv_style_set_pad_row(&InfoTab::LIST, 10);

        lv_style_init(&InfoTab::SECTION);
        lv_style_merge(&InfoTab::SECTION, &UI::Styles::Text::LIGHT22);
        lv_style_set_bg_color(&InfoTab::SECTION, Colors::DARKBLUE_ACCENT);
        lv_style_set_bg_opa(&InfoTab::SECTION, LV_OPA_COVER);
        lv_style_set_radius(&InfoTab::SECTION, 10);
        lv_style_set_outline_color(&InfoTab::SECTION, Colors::ORANGE);
        lv_style_set_outline_opa(&InfoTab::SECTION, LV_OPA_COVER);
        lv_style_set_outline_width(&InfoTab::SECTION, 2);
        lv_style_set_pad_all(&InfoTab::SECTION, 12);
        lv_style_set_pad_row(&InfoTab::SECTION, 12);

        lv_style_init(&InfoTab::SCROLLBAR_BOX);
        lv_style_set_pad_right(&InfoTab::SCROLLBAR_BOX, 5);
        lv_style_set_pad_top(&InfoTab::SCROLLBAR_BOX, 10);
        lv_style_set_pad_bottom(&InfoTab::SCROLLBAR_BOX, 10);

        lv_style_init(&InfoTab::SCROLLBAR_TRACK);
        lv_style_set_bg_color(&InfoTab::SCROLLBAR_TRACK, Colors::DARKBLUE_ACCENT);
        lv_style_set_bg_opa(&InfoTab::SCROLLBAR_TRACK, LV_OPA_COVER);
        lv_style_set_radius(&InfoTab::SCROLLBAR_TRACK, 12);
        lv_style_set_pad_all(&InfoTab::SCROLLBAR_TRACK, 5);

        lv_style_init(&InfoTab::SCROLLBAR_THUMB);
        lv_style_set_bg_color(&InfoTab::SCROLLBAR_THUMB, Colors::ORANGE);
        lv_style_set_bg_opa(&InfoTab::SCROLLBAR_THUMB, LV_OPA_COVER);
        lv_style_set_radius(&InfoTab::SCROLLBAR_THUMB, 6);

        lv_style_init(&InfoTab::METRICS_TABLE);
        lv_style_set_pad_row(&InfoTab::METRICS_TABLE, 5);
        lv_style_set_pad_all(&InfoTab::METRICS_TABLE, 5);

        lv_style_init(&InfoTab::METRICS_TABLE_ROW);
        lv_style_set_border_side(&InfoTab::METRICS_TABLE_ROW, LV_BORDER_SIDE_BOTTOM);
        lv_style_set_pad_bottom(&InfoTab::METRICS_TABLE_ROW, 10);
        lv_style_set_border_color(&InfoTab::METRICS_TABLE_ROW, UI::Colors::WHITE);
        lv_style_set_border_width(&InfoTab::METRICS_TABLE_ROW, 1);

        lv_style_init(&InfoTab::METRICS_TABLE_ROW_KEY);
        lv_style_set_text_align(&InfoTab::METRICS_TABLE_ROW_KEY, LV_TEXT_ALIGN_LEFT);
        lv_style_set_text_font(&InfoTab::METRICS_TABLE_ROW_KEY, UI::Fonts::F16);

        lv_style_init(&InfoTab::METRICS_TABLE_ROW_VALUE);
        lv_style_set_text_align(&InfoTab::METRICS_TABLE_ROW_VALUE, LV_TEXT_ALIGN_RIGHT);
        lv_style_set_text_font(&InfoTab::METRICS_TABLE_ROW_VALUE, UI::Fonts::F16);
        lv_style_set_text_color(&InfoTab::METRICS_TABLE_ROW_VALUE, UI::Colors::ORANGE);
    }

    // LeaderboardTab
    {
        lv_style_init(&LeaderboardTab::TABVIEW);
        lv_style_set_bg_color(&LeaderboardTab::TABVIEW, Colors::DARKBLUE_ACCENT);
        lv_style_set_outline_color(&LeaderboardTab::TABVIEW, Colors::ORANGE);
        lv_style_set_outline_opa(&LeaderboardTab::TABVIEW, LV_OPA_COVER);
        lv_style_set_outline_width(&LeaderboardTab::TABVIEW, 3);
        lv_style_set_radius(&LeaderboardTab::TABVIEW, 5);

        lv_style_init(&LeaderboardTab::TABVIEW_BAR);
        lv_style_set_bg_color(&LeaderboardTab::TABVIEW_BAR, Colors::DARKBLUE_ACCENT);
        lv_style_set_text_color(&LeaderboardTab::TABVIEW_BAR, Colors::WHITE);
        lv_style_set_text_font(&LeaderboardTab::TABVIEW_BAR, Fonts::F16);
        lv_style_set_radius(&LeaderboardTab::TABVIEW_BAR, 5);

        lv_style_init(&LeaderboardTab::TABVIEW_BAR_SELECTED);
        lv_style_set_text_color(&LeaderboardTab::TABVIEW_BAR_SELECTED, Colors::ORANGE);
        lv_style_set_border_color(&LeaderboardTab::TABVIEW_BAR_SELECTED, Colors::ORANGE);

        lv_style_init(&LeaderboardTab::TAB);
        lv_style_set_pad_all(&LeaderboardTab::TAB, 0);

        lv_style_init(&LeaderboardTab::LIST);
        lv_style_set_pad_all(&LeaderboardTab::LIST, 5);
        lv_style_set_pad_gap(&LeaderboardTab::LIST, 5);

        lv_style_init(&LeaderboardTab::SCROLLBAR);
        lv_style_set_bg_color(&LeaderboardTab::SCROLLBAR, UI::Colors::ORANGE);
        lv_style_set_bg_opa(&LeaderboardTab::SCROLLBAR, LV_OPA_COVER);
        lv_style_set_radius(&LeaderboardTab::SCROLLBAR, 6);
        lv_style_set_width(&LeaderboardTab::SCROLLBAR, 5);
        lv_style_set_pad_all(&LeaderboardTab::SCROLLBAR, 5);

        lv_style_init(&LeaderboardTab::PILL);
        lv_style_set_text_font(&LeaderboardTab::PILL, UI::Fonts::F22);
        lv_style_set_text_color(&LeaderboardTab::PILL, UI::Colors::GRAY);
        lv_style_set_pad_top(&LeaderboardTab::PILL, 3);

        lv_style_init(&LeaderboardTab::PILL_RANK);
        lv_style_set_text_color(&LeaderboardTab::PILL_RANK, UI::Colors::WHITE);
        lv_style_set_text_align(&LeaderboardTab::PILL_RANK, LV_TEXT_ALIGN_CENTER);

        lv_style_init(&LeaderboardTab::PILL_SCORE);
        lv_style_set_text_align(&LeaderboardTab::PILL_SCORE, LV_TEXT_ALIGN_CENTER);

        lv_style_init(&LeaderboardTab::PILL_DISABLED);
        lv_style_set_image_opa(&LeaderboardTab::PILL_DISABLED, LV_OPA_50);
        lv_style_set_text_opa(&LeaderboardTab::PILL_DISABLED, LV_OPA_50);
    }

    // SettingsTab
    {
        lv_style_init(&SettingsTab::BUTTON);
        lv_style_set_text_font(&SettingsTab::BUTTON, Fonts::F16);
        lv_style_set_text_color(&SettingsTab::BUTTON, Colors::WHITE);
        lv_style_set_outline_width(&SettingsTab::BUTTON, 2);
        lv_style_set_outline_color(&SettingsTab::BUTTON, Colors::WHITE);
        lv_style_set_bg_opa(&SettingsTab::BUTTON, LV_OPA_TRANSP);

        lv_style_init(&SettingsTab::DANGER_BUTTON);
        lv_style_set_outline_color(&SettingsTab::DANGER_BUTTON, Colors::RED_ACCENT);
        lv_style_set_bg_color(&SettingsTab::DANGER_BUTTON, Colors::RED);
        lv_style_set_text_color(&SettingsTab::DANGER_BUTTON, Colors::RED_ACCENT);
        lv_style_set_outline_width(&SettingsTab::DANGER_BUTTON, 2);
    }

    // FreeDrawTab
    {
        lv_style_init(&FreeDrawTab::HEADER_BOX);
        lv_style_set_pad_all(&FreeDrawTab::HEADER_BOX, 10);

        lv_style_init(&FreeDrawTab::HEADER_PILL);
        lv_style_set_bg_color(&FreeDrawTab::HEADER_PILL, Colors::SKYBLUE);
        lv_style_set_bg_opa(&FreeDrawTab::HEADER_PILL, LV_OPA_COVER);
        lv_style_set_radius(&FreeDrawTab::HEADER_PILL, LV_RADIUS_CIRCLE);
        lv_style_set_pad_all(&FreeDrawTab::HEADER_PILL, 4);

        lv_style_init(&FreeDrawTab::INFERENCE_LABEL_PILL);
        lv_style_set_bg_color(&FreeDrawTab::INFERENCE_LABEL_PILL, Colors::WHITE);
        lv_style_set_bg_opa(&FreeDrawTab::INFERENCE_LABEL_PILL, LV_OPA_COVER);
        lv_style_set_radius(&FreeDrawTab::INFERENCE_LABEL_PILL, LV_RADIUS_CIRCLE);

        lv_style_init(&FreeDrawTab::INFERENCE_LABEL);
        lv_style_set_text_align(&FreeDrawTab::INFERENCE_LABEL, LV_TEXT_ALIGN_CENTER);
        lv_style_set_text_color(&FreeDrawTab::INFERENCE_LABEL, Colors::GRAY);
        lv_style_set_text_font(&FreeDrawTab::INFERENCE_LABEL, Fonts::F22);

        lv_style_init(&FreeDrawTab::INFERENCE_PCT_LABEL);
        lv_style_set_text_align(&FreeDrawTab::INFERENCE_PCT_LABEL, LV_TEXT_ALIGN_CENTER);
        lv_style_set_text_color(&FreeDrawTab::INFERENCE_PCT_LABEL, Colors::WHITE);
        lv_style_set_text_font(&FreeDrawTab::INFERENCE_PCT_LABEL, Fonts::F22);
    }
}
