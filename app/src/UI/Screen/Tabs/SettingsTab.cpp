/**
 * @file      SettingsTab.cpp
 * @brief     UI Settings tab implementation
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

#include "SettingsTab.h"

#include "UI/Core/Base.h"
#include "UI/Core/Locale.h"
#include "UI/Core/Router.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Assets.h"
#include "UI/Theme/Styles.h"

SettingsTab::SettingsTab(Context& ctx) noexcept : Screen(ctx) {}

void SettingsTab::Create() {
    lv_obj_add_style(Root(), &UI::Styles::Common::BACKGROUND, 0);

    auto header = Box::Create(Root());
    lv_obj_set_size(header, lv_pct(100), lv_pct(15));
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);

    title = LV::Label::Create(header);
    lv_obj_center(title);
    lv_obj_set_style_text_font(title, UI::Fonts::F32, 0);
    lv_obj_set_style_text_color(title, UI::Colors::WHITE, 0);

    auto box = Box::Create(Root());
    lv_obj_set_size(box, lv_pct(100), lv_pct(85));
    lv_obj_align(box, LV_ALIGN_BOTTOM_MID, 0, 0);

    list.Create(box, {
                         .List = &UI::Styles::InfoTab::LIST,
                         .Section = &UI::Styles::InfoTab::SECTION,
                         .BarBox = &UI::Styles::InfoTab::SCROLLBAR_BOX,
                         .BarTrack = &UI::Styles::InfoTab::SCROLLBAR_TRACK,
                         .BarThumb = &UI::Styles::InfoTab::SCROLLBAR_THUMB,
                         .ScrollWidth = 16,
                     });

    auto* flagSection = list.Add();
    CreateFlagSection(flagSection);
    flagSectionLabel = LV::Label::From(lv_obj_get_child(flagSection, 0));

    adminSection = list.Add();
    CreateAdminSection(adminSection);

    leaderboardSection = list.Add();
    CreateLeaderboardSection(leaderboardSection);

    keypad.Create(Root());
    keypad.Hide();
    keypad.OnSucess(
        [](void* userData) {
            auto* self = static_cast<SettingsTab*>(userData);
            self->UnLock();
            self->keypad.Hide();
        },
        this);
}

void SettingsTab::Refresh() {
    lv_label_set_text_static(title, Locale::T(TKey::Settings));
    lv_label_set_text_static(flagSectionLabel, Locale::T(TKey::Language));
    lv_label_set_text_static(adminSectionLabel, Locale::T(TKey::AdminSettings));
    lv_label_set_text_static(adminSectionUnlockLabel, Locale::T(TKey::Unlock));
    lv_label_set_text_static(leaderboardSectionLabel, Locale::T(TKey::Leaderboard));
    lv_label_set_text_static(leaderboardSectionResetLabel, Locale::T(TKey::Clear));
}

void SettingsTab::OnEnter(const std::any&) {
    Lock();
}

void SettingsTab::CreateFlagSection(lv_obj_t* parent) {
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    auto sectionTitle = LV::Label::Create(parent);
    lv_obj_set_style_text_font(sectionTitle, UI::Fonts::F22, 0);
    lv_obj_set_style_text_color(sectionTitle, UI::Colors::WHITE, 0);

    auto* sectionBody = lv_obj_create(parent);
    lv_obj_remove_style_all(sectionBody);
    lv_obj_set_size(sectionBody, lv_pct(100), 60);
    lv_obj_set_flex_flow(sectionBody, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(sectionBody, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    constexpr std::pair<Language, const void*> languages[] = {
        {Language::FrFr, &Assets::FlagFR},
        {Language::EnUs, &Assets::FlagUK},
    };

    for (const auto& [lang, asset] : languages)
        AddFlag(sectionBody, lang, asset);
}

void SettingsTab::AddFlag(lv_obj_t* parent, Language language, const void* asset) {
    auto flag = LV::Image::Create(parent);
    lv_image_set_src(flag, asset);
    lv_obj_add_flag(flag, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_user_data(flag, reinterpret_cast<void*>(static_cast<uintptr_t>(static_cast<u32>(language))));
    lv_obj_add_event_cb(flag, LV_BIND_EVENT_CB_E(SettingsTab, OnFlagButtonPress), LV_EVENT_CLICKED, this);

    lv_obj_set_style_outline_color(flag, UI::Colors::WHITE, LV_STATE_CHECKED);
    lv_obj_set_style_outline_width(flag, 3, LV_STATE_CHECKED);

    if (Locale::Get() == language)
        lv_obj_add_state(flag, LV_STATE_CHECKED);
}

void SettingsTab::OnFlagButtonPress(lv_event_t* e) {
    auto flag = LV::Image::From(lv_event_get_target_obj(e));
    auto newLanguage =
        static_cast<Language>(static_cast<u32>(reinterpret_cast<uintptr_t>(lv_obj_get_user_data(flag))));

    if (newLanguage == Locale::Get())
        return;

    auto* parent = lv_obj_get_parent(flag);
    for (u32 i = 0; i < lv_obj_get_child_count(parent); i++) {
        lv_obj_remove_state(lv_obj_get_child(parent, i), LV_STATE_CHECKED);
    }
    lv_obj_add_state(flag, LV_STATE_CHECKED);

    Locale::Set(newLanguage);
    ctx.router.RefreshAllScreens();
    ctx.state.language = Locale::Get();
    Platform::FS::Store(SaveFiles::State, ctx.state);
}

void SettingsTab::CreateAdminSection(lv_obj_t* parent) {
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    adminSectionLabel = LV::Label::Create(parent);
    lv_obj_set_style_text_font(adminSectionLabel, UI::Fonts::F22, 0);
    lv_obj_set_style_text_color(adminSectionLabel, UI::Colors::WHITE, 0);

    auto unlockButton = LV::Button::Create(parent);
    lv_obj_set_size(unlockButton, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_add_style(unlockButton, &UI::Styles::SettingsTab::BUTTON, 0);
    lv_obj_add_event_cb(unlockButton, LV_BIND_EVENT_CB(SettingsTab, OnUnlockPress), LV_EVENT_CLICKED, this);

    adminSectionUnlockLabel = LV::Label::Create(unlockButton);
    lv_obj_center(adminSectionUnlockLabel);
}

void SettingsTab::CreateLeaderboardSection(lv_obj_t* parent) {
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    leaderboardSectionLabel = LV::Label::Create(parent);
    lv_obj_set_style_text_font(leaderboardSectionLabel, UI::Fonts::F22, 0);
    lv_obj_set_style_text_color(leaderboardSectionLabel, UI::Colors::WHITE, 0);

    auto resetButton = LV::Button::Create(parent);
    lv_obj_set_size(resetButton, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_add_style(resetButton, &UI::Styles::SettingsTab::DANGER_BUTTON, 0);
    lv_obj_add_event_cb(resetButton, LV_BIND_EVENT_CB(SettingsTab, OnResetLeaderboardPress), LV_EVENT_CLICKED,
                        this);

    leaderboardSectionResetLabel = LV::Label::Create(resetButton);
    lv_obj_center(leaderboardSectionResetLabel);
}

void SettingsTab::Lock() {
    lv_obj_remove_flag(adminSection, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(leaderboardSection, LV_OBJ_FLAG_HIDDEN);
}

void SettingsTab::UnLock() {
    lv_obj_add_flag(adminSection, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(leaderboardSection, LV_OBJ_FLAG_HIDDEN);
}

void SettingsTab::OnResetLeaderboardPress() {
    ctx.leaderboards.Clear();
    Platform::FS::Store(SaveFiles::Leaderboards, ctx.leaderboards);
    ctx.router.RefreshScreen(Route::Main);
}

void SettingsTab::OnUnlockPress() {
    keypad.Show();
}
