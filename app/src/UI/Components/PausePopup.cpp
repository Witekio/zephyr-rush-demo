/**
 * @file      PausePopup.cpp
 * @brief     UI Pause popup component implementation
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

#include "PausePopup.h"

#include "UI/Core/Locale.h"
#include "UI/Theme/Assets.h"
#include "UI/Theme/Styles.h"

void PausePopup::Create(lv_obj_t* parent) {
    auto* root = Popup::Create(parent);
    Build(root);
    Refresh();
}

void PausePopup::Refresh() const {
    lv_label_set_text_static(resumeLabel, Locale::T(TKey::Resume));
    lv_label_set_text_static(restartLabel, Locale::T(TKey::Restart));
    lv_label_set_text_static(menuLabel, Locale::T(TKey::Menu));
}

void PausePopup::SetCallbacks(void* usrData,
                              lv_event_cb_t resumeCb,
                              lv_event_cb_t restartCb,
                              lv_event_cb_t menuCb) const {
    lv_obj_add_event_cb(lv_obj_get_parent(resumeLabel), resumeCb, LV_EVENT_CLICKED, usrData);
    lv_obj_add_event_cb(lv_obj_get_parent(restartLabel), restartCb, LV_EVENT_CLICKED, usrData);
    lv_obj_add_event_cb(lv_obj_get_parent(menuLabel), menuCb, LV_EVENT_CLICKED, usrData);
}

void PausePopup::Build(lv_obj_t* parent) {
    auto bgImage = LV::Image::Create(parent);
    lv_image_set_src(bgImage, &Assets::PausePopup);
    lv_obj_center(bgImage);

    auto resumeButton = LV::Button::Create(bgImage);
    auto restartButton = LV::Button::Create(bgImage);
    auto menuButton = LV::Button::Create(bgImage);

    lv_obj_set_size(resumeButton, lv_pct(75), 50);
    lv_obj_set_size(restartButton, lv_pct(75), 50);
    lv_obj_set_size(menuButton, lv_pct(75), 50);

    lv_obj_add_style(resumeButton, &UI::Styles::PausePopup::BUTTON, 0);
    lv_obj_add_style(restartButton, &UI::Styles::PausePopup::BUTTON, 0);
    lv_obj_add_style(menuButton, &UI::Styles::PausePopup::BUTTON, 0);

    resumeLabel = LV::Label::Create(resumeButton);
    restartLabel = LV::Label::Create(restartButton);
    menuLabel = LV::Label::Create(menuButton);

    lv_obj_center(resumeLabel);
    lv_obj_center(restartLabel);
    lv_obj_center(menuLabel);

    lv_obj_align(menuButton, LV_ALIGN_BOTTOM_MID, 0, -27);
    lv_obj_align_to(restartButton, menuButton, LV_ALIGN_CENTER, 0, -54);
    lv_obj_align_to(resumeButton, restartButton, LV_ALIGN_CENTER, 0, -54);
}
