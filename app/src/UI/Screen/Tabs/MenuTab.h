/**
 * @file      MenuTab.h
 * @brief     UI Menu tab header
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

#include "UI/Components/RulesPopup.h"
#include "UI/Core/Router.h"
#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class MenuTab final : public Screen {
public:
    explicit MenuTab(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;
    void OnExit() override;

private:
    template <GameMode mode>
    constexpr auto GameNavigateCb() {
        return +[](lv_event_t* e) {
            auto* router = static_cast<Router*>(lv_event_get_user_data(e));
            router->NavigateTo(Route::Game, Payload::GameMode{mode});
        };
    }

private:
    LV::Label toGameRoundLabel;
    LV::Label toGameSpeedLabel;
    LV::Label toGameSurvivalLabel;
    LV::Label rulesLabel;

    RulesPopup popup;
};
