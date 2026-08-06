/**
 * @file      MenuTab.cpp
 * @brief     UI Menu tab implementation
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

#include "MenuTab.h"

#include "UI/Core/Locale.h"
#include "UI/Theme/Assets.h"
#include "UI/Theme/Styles.h"

MenuTab::MenuTab(Context& ctx) noexcept : Screen(ctx) {}

void MenuTab::Create() {
    lv_obj_add_style(Root(), &UI::Styles::Common::BACKGROUND, 0);

    auto witekioLogo = LV::Image::Create(Root());
    lv_image_set_src(witekioLogo, &Assets::WitekioLogo);
    lv_obj_align(witekioLogo, LV_ALIGN_TOP_MID, 0, 20);

    auto rushLogo = LV::Image::Create(Root());
    lv_image_set_src(rushLogo, &Assets::RushLogo);
    lv_obj_align_to(rushLogo, witekioLogo, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    auto toGameRoundButton = LV::Button::Create(Root());
    lv_obj_set_size(toGameRoundButton, 200, 40);
    lv_obj_align(toGameRoundButton, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_event_cb(toGameRoundButton, GameNavigateCb<GameMode::Round>(), LV_EVENT_CLICKED, &ctx.router);
    lv_obj_add_style(toGameRoundButton, &UI::Styles::Button::BLUE, 0);

    toGameRoundLabel = LV::Label::Create(toGameRoundButton);
    lv_obj_center(toGameRoundLabel);

    auto toGameSpeedButton = LV::Button::Create(Root());
    lv_obj_set_size(toGameSpeedButton, 200, 40);
    lv_obj_align_to(toGameSpeedButton, toGameRoundButton, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(toGameSpeedButton, GameNavigateCb<GameMode::Speed>(), LV_EVENT_CLICKED, &ctx.router);
    lv_obj_add_style(toGameSpeedButton, &UI::Styles::Button::ORANGE, 0);

    toGameSpeedLabel = LV::Label::Create(toGameSpeedButton);
    lv_obj_center(toGameSpeedLabel);

    auto toGameSurvivalButton = LV::Button::Create(Root());
    lv_obj_set_size(toGameSurvivalButton, 200, 40);
    lv_obj_align_to(toGameSurvivalButton, toGameSpeedButton, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(toGameSurvivalButton, GameNavigateCb<GameMode::Survival>(), LV_EVENT_CLICKED, &ctx.router);
    lv_obj_add_style(toGameSurvivalButton, &UI::Styles::Button::BLUE, 0);

    toGameSurvivalLabel = LV::Label::Create(toGameSurvivalButton);
    lv_obj_center(toGameSurvivalLabel);

    auto rulesButton = LV::Button::Create(Root());
    lv_obj_set_size(rulesButton, 200, 40);
    lv_obj_align_to(rulesButton, toGameSurvivalButton, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(
        rulesButton,
        [](lv_event_t* e) {
            auto* self = static_cast<MenuTab*>(lv_event_get_user_data(e));
            self->popup.Show();
            self->popup.ScrollToTop();
        },
        LV_EVENT_CLICKED, this);
    lv_obj_add_style(rulesButton, &UI::Styles::Button::ORANGE, 0);

    rulesLabel = LV::Label::Create(rulesButton);
    lv_obj_center(rulesLabel);

    popup.Create(Root());
    popup.Hide();
    popup.Refresh();
}

void MenuTab::Refresh() {
    lv_label_set_text_fmt(toGameRoundLabel, "%s - %s", Locale::T(TKey::Play), Locale::T(GameMode::Round));
    lv_label_set_text_fmt(toGameSpeedLabel, "%s - %s", Locale::T(TKey::Play), Locale::T(GameMode::Speed));
    lv_label_set_text_fmt(toGameSurvivalLabel, "%s - %s", Locale::T(TKey::Play), Locale::T(GameMode::Survival));
    lv_label_set_text_static(rulesLabel, Locale::T(TKey::Rules));
    popup.Refresh();
}

void MenuTab::OnExit() {
    popup.Hide();
}
