/**
 * @file      RulesPopup.cpp
 * @brief     UI Rules popup component implementation
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

#include "RulesPopup.h"

#include "UI/Core/Locale.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"
#include "UI/Widgets/Widgets.h"

LV::Label RulesPopup::AddRuleRow(lv_obj_t* list, i32 index) {
    auto hbox = HBox::Create(list);
    lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_set_style_pad_bottom(hbox, 12, 0);
    lv_obj_set_style_pad_column(hbox, 10, 0);

    auto bullet = Box::Create(hbox);
    lv_obj_set_size(bullet, 24, 24);

    lv_obj_set_style_bg_color(bullet, UI::Colors::ORANGE, 0);
    lv_obj_set_style_bg_opa(bullet, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(bullet, LV_RADIUS_CIRCLE, 0);

    auto num = LV::Label::Create(bullet);
    lv_label_set_text_fmt(num, "%d", index);
    lv_obj_center(num);

    lv_obj_add_style(num, &UI::Styles::Text::LIGHT16, 0);
    lv_obj_set_style_pad_bottom(num, 2, 0);

    auto label = LV::Label::Create(hbox);
    lv_obj_set_flex_grow(label, 1);

    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_label_set_recolor(label, true);

    lv_obj_add_style(label, &UI::Styles::Text::LIGHT16, 0);
    lv_obj_set_style_text_line_space(label, 3, 0);

    return label;
}

RulesPopup::ModeRow RulesPopup::AddModeRow(lv_obj_t* list, const void* asset) {
    auto vbox = VBox::Create(list);
    lv_obj_set_size(vbox, lv_pct(100), LV_SIZE_CONTENT);

    lv_obj_set_style_pad_row(vbox, 4, 0);
    lv_obj_set_style_border_color(vbox, UI::Colors::ORANGE, 0);
    lv_obj_set_style_border_side(vbox, LV_BORDER_SIDE_TOP, 0);
    lv_obj_set_style_border_width(vbox, 1, 0);
    lv_obj_set_style_border_opa(vbox, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_top(vbox, 10, 0);
    lv_obj_set_style_pad_bottom(vbox, 10, 0);

    auto hbox = HBox::Create(vbox);
    lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_column(hbox, 8, 0);

    auto icon = LV::Image::Create(hbox);
    lv_image_set_src(icon, asset);
    lv_obj_set_size(icon, 25, 25);

    auto title = LV::Label::Create(hbox);
    lv_obj_set_size(title, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(title, UI::Colors::ORANGE, 0);

    auto body = LV::Label::Create(vbox);
    lv_obj_set_size(body, lv_pct(100), LV_SIZE_CONTENT);
    lv_label_set_long_mode(body, LV_LABEL_LONG_WRAP);

    lv_obj_add_style(body, &UI::Styles::Text::LIGHT16, 0);

    return {.title = title, .body = body};
}

void RulesPopup::Create(lv_obj_t* parent) {
    auto* root = Popup::Create(parent);

    // Cont
    auto cont = VBox::Create(root);
    lv_obj_set_size(cont, lv_pct(90), lv_pct(95));
    lv_obj_center(cont);

    lv_obj_set_style_bg_color(cont, UI::Colors::DARKBLUE, 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(cont, UI::Colors::ORANGE, 0);
    lv_obj_set_style_border_width(cont, 2, 0);
    lv_obj_set_style_radius(cont, 20, 0);
    lv_obj_add_style(cont, &UI::Styles::Text::LIGHT22, 0);

    // Header
    auto header = Box::Create(cont);
    lv_obj_set_size(header, lv_pct(100), 44);

    lv_obj_set_style_pad_top(header, 14, 0);
    lv_obj_set_style_pad_bottom(header, 14, 0);
    lv_obj_set_style_pad_left(header, 18, 0);
    lv_obj_set_style_pad_right(header, 14, 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(header, 1, 0);
    lv_obj_set_style_border_color(header, UI::Colors::ORANGE, 0);

    howToPlayLabel = LV::Label::Create(header);
    lv_obj_align(howToPlayLabel, LV_ALIGN_LEFT_MID, 0, 0);

    // List
    list = VBox::Create(cont);
    lv_obj_set_width(list, lv_pct(100));
    lv_obj_set_flex_grow(list, 1);

    lv_obj_set_style_pad_all(list, 18, 0);
    lv_obj_add_style(list, &UI::Styles::LeaderboardTab::SCROLLBAR, LV_PART_SCROLLBAR);

    // Rules
    rules1 = AddRuleRow(list, 1);
    rules2 = AddRuleRow(list, 2);

    // Game Modes

    //  Spacer
    auto divider = Box::Create(list);
    lv_obj_set_size(divider, lv_pct(100), 1);

    lv_obj_set_style_bg_color(divider, UI::Colors::WHITE, 0);
    lv_obj_set_style_bg_opa(divider, LV_OPA_COVER, 0);
    lv_obj_set_style_margin_top(divider, 6, 0);
    lv_obj_set_style_margin_bottom(divider, 12, 0);

    // Section title
    gameModesLabel = LV::Label::Create(list);
    lv_obj_set_size(gameModesLabel, lv_pct(100), LV_SIZE_CONTENT);

    lv_obj_set_style_text_color(gameModesLabel, UI::Colors::ORANGE, 0);
    lv_obj_set_style_pad_bottom(gameModesLabel, 12, 0);
    lv_obj_set_style_text_align(gameModesLabel, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_margin_bottom(gameModesLabel, 5, 0);

    // Modes
    round = AddModeRow(list, &Assets::RoundModeIcon);
    speed = AddModeRow(list, &Assets::SpeedModeIcon);
    survival = AddModeRow(list, &Assets::SurvivalModeIcon);

    // Footer
    auto footer = Box::Create(cont);
    lv_obj_set_size(footer, lv_pct(100), LV_SIZE_CONTENT);

    lv_obj_set_style_pad_all(footer, 18, 0);

    auto gotItButton = LV::Button::Create(footer);
    lv_obj_set_size(gotItButton, lv_pct(100), 44);
    lv_obj_add_event_cb(gotItButton, LV_BIND_EVENT_CB(RulesPopup, Hide), LV_EVENT_CLICKED, this);

    lv_obj_set_style_bg_color(gotItButton, UI::Colors::ORANGE, 0);
    lv_obj_set_style_bg_opa(gotItButton, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(gotItButton, UI::Colors::WHITE, 0);
    lv_obj_set_style_border_width(gotItButton, 1, 0);
    lv_obj_set_style_radius(gotItButton, 12, 0);
    lv_obj_set_style_shadow_opa(gotItButton, LV_OPA_TRANSP, 0);

    gotItLabel = LV::Label::Create(gotItButton);
    lv_obj_center(gotItLabel);
    lv_obj_add_style(gotItLabel, &UI::Styles::Text::LIGHT16, 0);
}

void RulesPopup::Refresh() {
    lv_label_set_text_static(howToPlayLabel, Locale::T(Rules::HowToPlay));
    lv_label_set_text_static(rules1, Locale::T(Rules::Rule1));
    lv_label_set_text_static(rules2, Locale::T(Rules::Rule2));
    lv_label_set_text(gameModesLabel, Locale::T(Rules::GameModes));
    lv_label_set_text_static(round.title, Locale::T(GameMode::Round));
    lv_label_set_text_static(round.body, Locale::T(Rules::RoundBody));
    lv_label_set_text_static(speed.title, Locale::T(GameMode::Speed));
    lv_label_set_text_static(speed.body, Locale::T(Rules::SpeedBody));
    lv_label_set_text_static(survival.title, Locale::T(GameMode::Survival));
    lv_label_set_text_static(survival.body, Locale::T(Rules::SurvivalBody));
    lv_label_set_text_static(gotItLabel, Locale::T(Rules::GotIt));

    ScrollToTop();
}

void RulesPopup::ScrollToTop() {
    lv_obj_scroll_to_y(list, 0, LV_ANIM_OFF);
}
