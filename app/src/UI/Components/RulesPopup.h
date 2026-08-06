/**
 * @file      RulesPopup.h
 * @brief     UI Rules popup component header
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

#include "Core/Base.h"
#include "UI/Core/Popup.h"
#include "UI/Widgets/Widgets.h"

class RulesPopup final : public Popup {
public:
    void Create(lv_obj_t* parent);
    void Refresh();
    void ScrollToTop();

private:
    struct ModeRow {
        LV::Label title;
        LV::Label body;
    };

    static LV::Label AddRuleRow(lv_obj_t* list, i32 index);
    static ModeRow AddModeRow(lv_obj_t* list, const void* asset);

private:
    LV::Obj list;

    LV::Label howToPlayLabel;
    LV::Label gotItLabel;

    LV::Label rules1;
    LV::Label rules2;

    LV::Label gameModesLabel;

    ModeRow round;
    ModeRow speed;
    ModeRow survival;
};
