/**
 * @file      LeaderboardTab.cpp
 * @brief     UI Leaderboard tab implementation
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

#include "LeaderboardTab.h"

#include "UI/Core/Locale.h"
#include "UI/Theme/Styles.h"

LeaderboardTab::LeaderboardTab(Context& ctx) noexcept : Screen(ctx) {}

void LeaderboardTab::Create() {
    lv_obj_add_style(Root(), &UI::Styles::Common::BACKGROUND, 0);

    auto header = LV::Image::Create(Root());
    lv_image_set_src(header, &Assets::LeaderboardHeader);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 5);

    tabview = LV::TabView::Create(Root());
    lv_obj_set_size(tabview, lv_pct(90), lv_pct(77));
    lv_obj_align(tabview, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_style(tabview, &UI::Styles::LeaderboardTab::TABVIEW, 0);

    auto* bar = lv_tabview_get_tab_bar(tabview);
    lv_obj_add_style(bar, &UI::Styles::LeaderboardTab::TABVIEW_BAR, 0);

    for (u32 i = 0; i < std::size(tabs); i++) {
        auto& [list, mode] = tabs[i];
        auto* tab = lv_tabview_add_tab(tabview, "");
        lv_obj_add_style(tab, &UI::Styles::LeaderboardTab::TAB, 0);

        auto* tabBtn = lv_tabview_get_tab_button(tabview, i);
        lv_obj_add_style(tabBtn, &UI::Styles::LeaderboardTab::TABVIEW_BAR_SELECTED, LV_STATE_CHECKED);

        list = VBox::Create(tab);
        lv_obj_set_size(list, lv_pct(100), lv_pct(100));
        lv_obj_set_flex_align(list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_add_style(list, &UI::Styles::LeaderboardTab::LIST, 0);

        lv_obj_add_style(list, &UI::Styles::LeaderboardTab::SCROLLBAR, LV_PART_SCROLLBAR);

        CreateEntryHolders(list);
    }

    lv_tabview_set_active(tabview, 1, false);
}

void LeaderboardTab::CreateEntryHolders(LV::Obj list) {
    for (u32 i = 0; i < Leaderboard::Capacity(); i++) {
        auto pill = LV::Image::Create(list);
        lv_image_set_src(pill, &Assets::EntryPill);
        lv_obj_add_style(pill, &UI::Styles::LeaderboardTab::PILL, 0);
        lv_obj_add_style(pill, &UI::Styles::LeaderboardTab::PILL_DISABLED, LV_STATE_DISABLED);

        auto rankLabel = LV::Label::Create(pill);
        lv_obj_set_size(rankLabel, 35, lv_pct(100));
        lv_obj_align(rankLabel, LV_ALIGN_LEFT_MID, 0, 0);
        lv_label_set_text_fmt(rankLabel, "%u", i + 1);
        lv_obj_add_style(rankLabel, &UI::Styles::LeaderboardTab::PILL_RANK, 0);

        auto nameLabel = LV::Label::Create(pill);
        lv_obj_align(nameLabel, LV_ALIGN_LEFT_MID, 40, 0);
        lv_obj_set_size(nameLabel, 120, lv_pct(100));
        lv_label_set_long_mode(nameLabel, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_label_set_text_static(nameLabel, "");

        auto scoreLabel = LV::Label::Create(pill);
        lv_obj_set_size(scoreLabel, 60, lv_pct(100));
        lv_obj_align(scoreLabel, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_label_set_text_static(scoreLabel, "");
        lv_obj_add_style(scoreLabel, &UI::Styles::LeaderboardTab::PILL_SCORE, 0);
    }
}

void LeaderboardTab::UpdateEntryHolders(LV::Obj list, GameMode mode) {
    auto& leaderboard = ctx.leaderboards.Get(mode);

    for (u32 i = 0; i < Leaderboard::Capacity(); i++) {
        auto* pill = lv_obj_get_child(list, i);
        // child 0 is the rank label, set once at creation time.
        auto* nameLabel = lv_obj_get_child(pill, 1);
        auto* scoreLabel = lv_obj_get_child(pill, 2);

        if (i < leaderboard.Count()) {
            const auto& [name, score] = leaderboard.GetEntry(i);

            lv_obj_remove_state(pill, LV_STATE_DISABLED);

            lv_label_set_text_static(nameLabel, name.data());
            lv_label_set_text_fmt(scoreLabel, "%u/%u", score.success, score.total);
        } else {
            lv_obj_add_state(pill, LV_STATE_DISABLED);

            lv_label_set_text_static(nameLabel, "");
            lv_label_set_text_static(scoreLabel, "");
        }
    }
}

void LeaderboardTab::SelectTab(u32 tabIdx) {
    lv_tabview_set_active(tabview, tabIdx, LV_ANIM_ON);

    UpdateEntryHolders(tabs[tabIdx].list, tabs[tabIdx].mode);
}

void LeaderboardTab::GoToView(u32 tabIdx, u32 idx) {
    if (tabIdx != lv_tabview_get_tab_active(tabview))
        SelectTab(tabIdx);

    lv_obj_scroll_to_view(lv_obj_get_child(tabs[tabIdx].list, idx), LV_ANIM_ON);
}

void LeaderboardTab::Refresh() {
    for (u32 i = 0; i < std::size(tabs); i++) {
        auto& [list, mode] = tabs[i];
        lv_tabview_set_tab_text(tabview, i, Locale::T(mode));
        UpdateEntryHolders(list, mode);
        lv_obj_scroll_to_view(lv_obj_get_child(list, 0), LV_ANIM_OFF);
    }
}

void LeaderboardTab::OnEnter(const std::any& payload) {
    if (payload.has_value()) {
        auto [mode, idx] = std::any_cast<Payload::LeaderboardTab>(payload);
        SelectTab(static_cast<u32>(mode));
        if (idx.has_value())
            GoToView(static_cast<u32>(mode), *idx);
    }
}
