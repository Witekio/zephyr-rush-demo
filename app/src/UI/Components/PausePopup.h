/**
 * @file      PausePopup.h
 * @brief     UI Pause popup component header
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

#include "UI/Core/Popup.h"
#include "UI/Widgets/Widgets.h"

class PausePopup final : public Popup {
public:
    void Create(lv_obj_t* parent);
    void Refresh() const;

    void SetCallbacks(void* usrData, lv_event_cb_t resume, lv_event_cb_t restart, lv_event_cb_t menu) const;

private:
    void Build(lv_obj_t* parent);

private:
    LV::Label resumeLabel;
    LV::Label restartLabel;
    LV::Label menuLabel;
};
