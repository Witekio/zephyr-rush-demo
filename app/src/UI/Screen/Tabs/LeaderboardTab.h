/**
 * @file      LeaderboardTab.h
 * @brief     UI Leaderboard tab header
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

#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class LeaderboardTab final : public Screen {
public:
    explicit LeaderboardTab(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;

    void OnEnter(const std::any& payload) override;

private:
    void CreateEntryHolders(LV::Obj list);
    void UpdateEntryHolders(LV::Obj list, GameMode mode);

    void SelectTab(u32 tabIdx);
    void GoToView(u32 tabIdx, u32 idx);

    struct Tab {
        LV::Obj list;
        GameMode mode;
    };

private:
    LV::TabView tabview;
    Tab tabs[3] = {
        {.list = {}, .mode = GameMode::Round},
        {.list = {}, .mode = GameMode::Speed},
        {.list = {}, .mode = GameMode::Survival},
    };
};
