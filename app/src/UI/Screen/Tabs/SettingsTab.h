/**
 * @file      SettingsTab.h
 * @brief     UI Settings tab header
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

#include "UI/Components/KeypadPopup.h"
#include "UI/Components/List.h"
#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class SettingsTab final : public Screen {
public:
    explicit SettingsTab(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;

    void OnEnter(const std::any& payload) override;

private:
    void CreateFlagSection(lv_obj_t* parent);
    void AddFlag(lv_obj_t* parent, Language lang, const void* asset);
    void OnFlagButtonPress(lv_event_t* e);

    void CreateAdminSection(lv_obj_t* parent);

    void CreateLeaderboardSection(lv_obj_t* parent);

    void Lock();
    void UnLock();

    void OnResetLeaderboardPress();
    void OnUnlockPress();

private:
    LV::Label title;

    LV::Label flagSectionLabel;

    lv_obj_t* adminSection;
    LV::Label adminSectionLabel;
    LV::Label adminSectionUnlockLabel;

    lv_obj_t* leaderboardSection;
    LV::Label leaderboardSectionLabel;
    LV::Label leaderboardSectionResetLabel;

    List list;
    KeypadPopup keypad;
};
