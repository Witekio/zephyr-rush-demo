/**
 * @file      MainScreen.cpp
 * @brief     UI Main screen implementation
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

#include "MainScreen.h"

#include "UI/Core/Base.h"
#include "UI/Core/Screen.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Assets.h"
#include "UI/Theme/Styles.h"

#include <any>
#include <array>
#include <cassert>

MainScreen::MainScreen(Context& ctx) noexcept
    : Screen(ctx),
      infoTab(ctx),
      leaderboardTab(ctx),
      menuTab(ctx),
      freeDrawTab(ctx),
      settingsTab(ctx),
      tabs({
          {&infoTab, nullptr, {}, {}, &Assets::InfoTabIcon},
          {&leaderboardTab, nullptr, {}, {}, &Assets::LeaderboardTabIcon},
          {&menuTab, nullptr, {}, {}, &Assets::MenuTabIcon},
          {&freeDrawTab, nullptr, {}, {}, &Assets::FreeDrawTabIcon},
          {&settingsTab, nullptr, {}, {}, &Assets::SettingsTabIcon},
      }) {}

void MainScreen::Create() {
    {
        tileview = LV::TileView::Create(Root());
        lv_obj_set_size(tileview, kScreenWidth, kScreenHeight - kFooterHeight);
        lv_obj_set_scrollbar_mode(tileview, LV_SCROLLBAR_MODE_OFF);
        lv_obj_align(tileview, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_add_event_cb(tileview, LV_BIND_EVENT_CB(MainScreen, OnTileChange), LV_EVENT_VALUE_CHANGED, this);
    }

    auto* tabsContainer = lv_obj_create(Root());
    lv_obj_remove_style_all(tabsContainer);
    lv_obj_set_size(tabsContainer, lv_pct(100), kFooterHeight);
    lv_obj_align(tabsContainer, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_flex_flow(tabsContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(tabsContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_remove_flag(tabsContainer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(tabsContainer, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(tabsContainer, UI::Colors::DARKBLUE_ACCENT, 0);

    {
        for (i32 i = 0; i < kTileCount; i++) {
            auto& [screen, tile, button, icon, asset] = tabs[i];

            // Tile
            tile = lv_tileview_add_tile(tileview, i, 0, LV_DIR_HOR);
            lv_obj_remove_flag(tile, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_user_data(tile, reinterpret_cast<void*>(static_cast<intptr_t>(i)));
            lv_obj_set_size(tile, lv_pct(100), kScreenHeight - kFooterHeight);

            // Screen
            screen->SetRoot(tile);
            screen->Create();
            screen->Refresh();

            // Button
            button = LV::Button::Create(tabsContainer);
            lv_obj_remove_style_all(button);
            lv_obj_set_size(button, kScreenWidth / kTileCount, lv_pct(100));
            lv_obj_set_flex_grow(button, 1);
            lv_obj_remove_flag(button, LV_OBJ_FLAG_SCROLLABLE);

            lv_obj_set_style_bg_color(button, UI::Colors::ORANGE, LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(button, LV_OPA_COVER, LV_STATE_CHECKED);
            lv_obj_set_style_border_color(button, UI::Colors::WHITE, LV_STATE_CHECKED);
            lv_obj_set_style_border_side(button, LV_BORDER_SIDE_TOP, LV_STATE_CHECKED);
            lv_obj_set_style_border_opa(button, LV_OPA_50, LV_STATE_CHECKED);
            lv_obj_set_style_border_width(button, 4, LV_STATE_CHECKED);

            // Image
            icon = LV::Image::Create(button);
            lv_image_set_src(icon, asset);
            lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0);

            lv_obj_set_user_data(button, reinterpret_cast<void*>(static_cast<intptr_t>(i)));
            lv_obj_add_event_cb(button, LV_BIND_EVENT_CB_E(MainScreen, OnTabPress), LV_EVENT_CLICKED, this);
        }
    }
}

void MainScreen::Refresh() {
    // refresh all tabs
    for (auto& tab : tabs)
        tab.tab->Refresh();
}

void MainScreen::Update() {
    tabs[currentIndex].tab->Update();
}

void MainScreen::OnEnter(const std::any& payload) {
    if (payload.has_value()) {
        auto data = std::any_cast<Payload::MainMenu>(payload);
        auto idx = static_cast<u8>(data.tab);
        SetActiveTile(idx, data.tabPayload);
        lv_tileview_set_tile_by_index(tileview, idx, 0, false);
    }

    auto* tile = tabs[currentIndex].tile;
    lastTile = tile;
    lv_tileview_set_tile(tileview, tile, LV_ANIM_OFF);
    lv_obj_add_state(tabs[currentIndex].button, LV_STATE_CHECKED);
}

void MainScreen::OnExit() {
    tabs[currentIndex].tab->OnExit();
}

void MainScreen::SetActiveTile(i32 idx, const std::any& payload) {
    if (idx < 0 || idx >= kTileCount || idx == currentIndex)
        return;

    bool shouldCallExit = previousIndex != currentIndex;

    previousIndex = currentIndex;
    currentIndex = idx;

    if (shouldCallExit)
        tabs[previousIndex].tab->OnExit();

    tabs[currentIndex].tab->OnEnter(payload);

    lv_obj_remove_state(tabs[previousIndex].button, LV_STATE_CHECKED);
    lv_obj_add_state(tabs[currentIndex].button, LV_STATE_CHECKED);
}

void MainScreen::OnTileChange() {
    auto* activeTile = lv_tileview_get_tile_active(tileview);
    if (activeTile == lastTile)
        return;

    lastTile = activeTile;
    auto idx = static_cast<i32>(reinterpret_cast<intptr_t>(lv_obj_get_user_data(activeTile)));

    SetActiveTile(idx);
}

void MainScreen::OnTabPress(lv_event_t* e) {
    auto* btn = lv_event_get_target_obj(e);
    auto idx = static_cast<i32>(reinterpret_cast<intptr_t>(lv_obj_get_user_data(btn)));

    SetActiveTile(idx);
    lv_tileview_set_tile_by_index(tileview, idx, 0, false);
}
