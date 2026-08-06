/**
 * @file      Assets.h
 * @brief     UI Images and fonts declarations
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

#include <lvgl.h>

namespace Assets {
    extern "C" {
    LV_IMAGE_DECLARE(ClearIcon);
    LV_IMAGE_DECLARE(CloseIcon);
    LV_IMAGE_DECLARE(EntryPill);
    LV_IMAGE_DECLARE(FlagFR);
    LV_IMAGE_DECLARE(FlagUK);
    LV_IMAGE_DECLARE(FreeDrawTabIcon);
    LV_IMAGE_DECLARE(HomeIcon);
    LV_IMAGE_DECLARE(InfoTabIcon);
    LV_IMAGE_DECLARE(LeaderboardHeader);
    LV_IMAGE_DECLARE(LeaderboardTabIcon);
    LV_IMAGE_DECLARE(MenuTabIcon);
    LV_IMAGE_DECLARE(NextIcon);
    LV_IMAGE_DECLARE(PausePopup);
    LV_IMAGE_DECLARE(PlusIcon);
    LV_IMAGE_DECLARE(Ribbon);
    LV_IMAGE_DECLARE(RoundModeIcon);
    LV_IMAGE_DECLARE(RushLogo);
    LV_IMAGE_DECLARE(ScoreHolder);
    LV_IMAGE_DECLARE(SettingsTabIcon);
    LV_IMAGE_DECLARE(SpeedModeIcon);
    LV_IMAGE_DECLARE(SurvivalModeIcon);
    LV_IMAGE_DECLARE(UndoIcon);
    LV_IMAGE_DECLARE(WitekioLogo);

    LV_FONT_DECLARE(Gabarito16);
    LV_FONT_DECLARE(Gabarito22);
    LV_FONT_DECLARE(Gabarito32);
    }
} // namespace Assets
