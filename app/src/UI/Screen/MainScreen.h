/**
 * @file      MainScreen.h
 * @brief     UI Main screen header
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

#include "UI/Core/Base.h"
#include "UI/Core/Screen.h"
#include "UI/Screen/Tabs/FreeDrawTab.h"
#include "UI/Screen/Tabs/InfoTab.h"
#include "UI/Screen/Tabs/LeaderboardTab.h"
#include "UI/Screen/Tabs/MenuTab.h"
#include "UI/Screen/Tabs/SettingsTab.h"

class MainScreen final : public Screen {
public:
    explicit MainScreen(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;

    void Update() override;

    void OnEnter(const std::any& payload) override;
    void OnExit() override;

private:
    void SetActiveTile(i32 idx, const std::any& payload = {});

    void OnTileChange();
    void OnTabPress(lv_event_t* e);

private:
    static constexpr i32 kTileCount = static_cast<i32>(MainTabs::Count);
    static constexpr i32 kFooterHeight = 54;

    struct Tab {
        Screen* tab;
        lv_obj_t* tile;
        LV::Button button;
        LV::Image icon;
        const lv_image_dsc_t* asset;
    };

private:
    InfoTab infoTab;
    LeaderboardTab leaderboardTab;
    MenuTab menuTab;
    FreeDrawTab freeDrawTab;
    SettingsTab settingsTab;

    std::array<Tab, kTileCount> tabs;
    i32 currentIndex = 0;
    i32 previousIndex = 0;

    LV::TileView tileview;
    lv_obj_t* lastTile = nullptr;
};
