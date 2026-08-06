/**
 * @file      GameOverScreen.cpp
 * @brief     UI Game over screen implementation
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

#include "GameOverScreen.h"

#include "UI/Core/Base.h"
#include "UI/Core/Locale.h"
#include "UI/Core/Router.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"

GameOverScreen::GameOverScreen(Context& ctx) noexcept : Screen(ctx) {}

void GameOverScreen::Create() {
    lv_obj_add_style(Root(), &UI::Styles::Common::BACKGROUND, 0);

    {
        // Top label ("YOUR SCORE IS")
        yourScoreIsLabel = LV::Label::Create(Root());
        lv_obj_align(yourScoreIsLabel, LV_ALIGN_TOP_MID, 0, 15);
        lv_obj_add_style(yourScoreIsLabel, &UI::Styles::Text::DARK32, 0);
        lv_obj_set_style_text_color(yourScoreIsLabel, UI::Colors::WHITE, 0);

        // Score holder asset & text
        auto scoreHolder = LV::Image::Create(Root());
        lv_obj_align(scoreHolder, LV_ALIGN_TOP_MID, 0, 70);
        lv_image_set_src(scoreHolder, &Assets::ScoreHolder);

        scoreLabel = LV::Label::Create(scoreHolder);
        lv_obj_add_style(scoreHolder, &UI::Styles::GameOverScreen::SCORE, 0);
        lv_obj_center(scoreLabel);
    }

    // Keyboard & Text input
    auto vbox = VBox::Create(Root());
    lv_obj_set_size(vbox, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_align(vbox, LV_ALIGN_BOTTOM_MID, 0, -100);

    lv_obj_set_style_pad_all(vbox, 10, 0);
    lv_obj_set_style_pad_gap(vbox, 10, 0);

    {
        auto hbox = HBox::Create(vbox);
        lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_set_style_pad_gap(hbox, 10, 0);

        auto box = Box::Create(hbox);
        lv_obj_set_flex_grow(box, 1);
        lv_obj_set_height(box, lv_pct(100));

        lv_obj_add_style(box, &UI::Styles::GameOverScreen::TEXTAREA_HOLDER, 0);

        textarea = LV::TextArea::Create(box);
        lv_obj_remove_style_all(textarea);
        lv_obj_set_size(textarea, lv_pct(100), lv_pct(100));
        lv_obj_center(textarea);

        lv_textarea_set_one_line(textarea, true);
        lv_textarea_set_max_length(textarea, Leaderboard::kMaxUsernameLength);

        lv_obj_add_state(textarea, LV_STATE_FOCUSED);
        lv_obj_add_style(textarea, &UI::Styles::GameOverScreen::TEXTAREA, 0);
        lv_obj_add_style(textarea, &UI::Styles::GameOverScreen::TEXTAREA_PLACEHOLDER,
                         LV_PART_TEXTAREA_PLACEHOLDER);
        lv_obj_add_style(textarea, &UI::Styles::GameOverScreen::BAR_CURSOR,
                         LV_PART_CURSOR | (u32)LV_STATE_FOCUSED);

        submitButton = LV::Button::Create(hbox);
        lv_obj_remove_style_all(submitButton);
        lv_obj_set_size(submitButton, 48, 48);
        lv_obj_add_state(submitButton, LV_STATE_DISABLED);
        lv_obj_add_event_cb(submitButton, LV_BIND_EVENT_CB(GameOverScreen, OnSubmitPress), LV_EVENT_CLICKED, this);

        lv_obj_add_style(submitButton, &UI::Styles::Button::BLUE, 0);
        lv_obj_add_style(submitButton, &UI::Styles::Button::DISABLED, LV_STATE_DISABLED);

        auto submitIcon = LV::Image::Create(submitButton);
        lv_image_set_src(submitIcon, &Assets::NextIcon);
        lv_obj_center(submitIcon);
    }

    {
        auto box = Box::Create(vbox);
        lv_obj_set_size(box, lv_pct(100), LV_SIZE_CONTENT);

        keyboard = CustomKeyboard::Create(box);
        lv_obj_remove_style_all(keyboard);
        lv_obj_set_size(keyboard, lv_pct(100), 125);
        lv_keyboard_set_textarea(keyboard, textarea);
        lv_obj_add_event_cb(keyboard, LV_BIND_EVENT_CB(GameOverScreen, OnKeyPress), LV_EVENT_VALUE_CHANGED, this);

        lv_obj_add_style(keyboard, &UI::Styles::GameOverScreen::KEYBOARD, 0);
        lv_obj_add_style(keyboard, &UI::Styles::GameOverScreen::KEYBOARD_ITEMS, LV_PART_ITEMS);
    }

    {
        constexpr auto NavigateCb = [](lv_event_t* e) {
            static_cast<Router*>(lv_event_get_user_data(e))->NavigateTo(Route::Main);
        };

        auto homeButton = LV::Button::Create(Root());
        lv_obj_align(homeButton, LV_ALIGN_BOTTOM_MID, 0, -40);
        lv_obj_add_event_cb(homeButton, NavigateCb, LV_EVENT_CLICKED, &ctx.router);
        lv_obj_add_style(homeButton, &UI::Styles::Button::BLUE, 0);

        auto homeIcon = LV::Image::Create(homeButton);
        lv_image_set_src(homeIcon, &Assets::HomeIcon);
        lv_obj_center(homeIcon);
    }
}

void GameOverScreen::Refresh() {
    lv_label_set_text_static(yourScoreIsLabel, Locale::T(TKey::YourScoreIs));
    lv_textarea_set_placeholder_text(textarea, Locale::T(TKey::Nickname));
}

void GameOverScreen::OnEnter(const std::any& payload) {
    if (payload.has_value()) {
        gameScore = std::any_cast<Payload::GameScore>(payload);
        auto [success, total] = gameScore.score;
        lv_label_set_text_fmt(scoreLabel, "%u / %u", success, total);
    } else {
        lv_label_set_text_static(scoreLabel, "? / ?");
    }

    lv_textarea_set_text(textarea, "");
    lv_obj_add_state(submitButton, LV_STATE_DISABLED);
}

void GameOverScreen::OnSubmitPress() {
    const char* username = lv_textarea_get_text(textarea);

    if (strlen(username) == 0)
        return;

    auto idx = ctx.leaderboards.Get(gameScore.mode).PushEntry(username, gameScore.score);
    Platform::FS::Store(SaveFiles::Leaderboards, ctx.leaderboards);
    ctx.router.NavigateTo(Route::Main,
                          Payload::MainMenu{
                              .tab = MainTabs::Leaderboard,
                              .tabPayload = Payload::LeaderboardTab{.mode = gameScore.mode, .idx = idx},
                          });
}

void GameOverScreen::OnKeyPress() const {
    if (strlen(lv_textarea_get_text(textarea)) > 0)
        lv_obj_remove_state(submitButton, LV_STATE_DISABLED);
    else
        lv_obj_add_state(submitButton, LV_STATE_DISABLED);
}
