/**
 * @file      InfoTab.cpp
 * @brief     UI Info tab implementation
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

#include "InfoTab.h"

#include "UI/Core/Locale.h"
#include "UI/Theme/Styles.h"
#include "UI/Widgets/Box.h"

InfoTab::InfoTab(Context& ctx) noexcept : Screen(ctx) {}

void InfoTab::Create() {
    lv_obj_add_style(Root(), &UI::Styles::Common::BACKGROUND, 0);

    CreateHeader();

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

    {
        auto* section = list.Add();
        lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
        aboutSection = CreateInfoSection(section);
    }

    {
        auto* section = list.Add();
        lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
        ribbonSection = CreateRibbonSection(section);
    }

    {
        auto* section = list.Add();
        lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
        memorySection = CreateMetricsSection(section, 2);
    }

    {
        auto* section = list.Add();
        lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
        aiSection = CreateMetricsSection(section, 3);
    }

    {
        auto* section = list.Add();
        lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
        firmwareSection = CreateMetricsSection(section, 1);
    }
}

void InfoTab::CreateHeader() {
    auto header = Box::Create(Root());
    lv_obj_set_size(header, lv_pct(100), lv_pct(15));
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);

    title = LV::Label::Create(header);
    lv_obj_center(title);
    lv_obj_add_style(title, &UI::Styles::Text::LIGHT32, 0);
}

InfoTab::RibbonSection InfoTab::CreateRibbonSection(lv_obj_t* parent) {
    auto title = LV::Label::Create(parent);
    lv_obj_set_size(title, lv_pct(100), LV_SIZE_CONTENT);

    auto image = LV::Image::Create(parent);
    lv_image_set_src(image, &Assets::Ribbon);
    lv_obj_align(image, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_image_set_inner_align(image, LV_IMAGE_ALIGN_TILE);
    lv_obj_set_width(image, lv_pct(100));
    lv_obj_set_height(image, Assets::Ribbon.header.h);

    lv_obj_set_style_bg_color(image, UI::Colors::WHITE, 0);
    lv_obj_set_style_bg_opa(image, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(image, 10, 0);

    return {.title = title, .image = image};
}

InfoTab::InfoSection InfoTab::CreateInfoSection(lv_obj_t* parent) {
    auto title = LV::Label::Create(parent);

    auto body = LV::Label::Create(parent);
    lv_label_set_long_mode(body, LV_LABEL_LONG_WRAP);
    lv_label_set_recolor(body, true);
    lv_obj_set_width(body, lv_pct(100));
    lv_obj_set_style_text_font(body, UI::Fonts::F16, 0);

    return {.title = title, .body = body};
}

InfoTab::MetricsSection InfoTab::CreateMetricsSection(lv_obj_t* parent, u32 rows) {
    auto title = LV::Label::Create(parent);
    lv_obj_set_width(title, lv_pct(100));

    auto table = VBox::Create(parent);
    lv_obj_set_size(table, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_add_style(table, &UI::Styles::InfoTab::METRICS_TABLE, 0);

    for (u32 y = 0; y < rows; y++) {
        auto row = HBox::Create(table);
        lv_obj_set_size(row, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_add_style(row, &UI::Styles::InfoTab::METRICS_TABLE_ROW, 0);

        auto key = LV::Label::Create(row);
        lv_obj_set_flex_grow(key, 1);
        lv_obj_add_style(key, &UI::Styles::InfoTab::METRICS_TABLE_ROW_KEY, 0);

        auto value = LV::Label::Create(row);
        lv_obj_add_style(value, &UI::Styles::InfoTab::METRICS_TABLE_ROW_VALUE, 0);
    }

    return {.title = title, .table = table, .rows = rows};
}

LV::Label InfoTab::GetLabel(const MetricsSection& section, u32 row, u32 column) {
    assert(row < section.rows);
    assert(column == 0 || column == 1);
    return LV::Label::From(lv_obj_get_child(lv_obj_get_child(section.table, row), column));
}

void InfoTab::Refresh() {
    lv_label_set_text_static(title, Locale::T(TKey::Infos));
    lv_label_set_text_static(ribbonSection.title, Locale::T(TKey::Technologies));

    lv_label_set_text_static(aboutSection.title, Locale::T(InfosSection::AboutTitle));
    lv_label_set_text_static(aboutSection.body, Locale::T(InfosSection::AboutBody));

    lv_label_set_text_static(memorySection.title, Locale::T(InfosSection::MemoryTitle));
    lv_label_set_text_static(GetLabel(memorySection, 0, 0), Locale::T(InfosSection::MemoryFlashKey));
    lv_label_set_text_static(GetLabel(memorySection, 0, 1), Locale::T(InfosSection::MemoryFlashValue));
    lv_label_set_text_static(GetLabel(memorySection, 1, 0), Locale::T(InfosSection::MemoryRamKey));
    lv_label_set_text_static(GetLabel(memorySection, 1, 1), Locale::T(InfosSection::MemoryRamValue));

    lv_label_set_text_static(aiSection.title, Locale::T(InfosSection::AIModelTitle));
    lv_label_set_text_static(GetLabel(aiSection, 0, 0), Locale::T(InfosSection::AIModelSizeFlashKey));
    lv_label_set_text_static(GetLabel(aiSection, 0, 1), Locale::T(InfosSection::AIModelSizeFlashValue));
    lv_label_set_text_static(GetLabel(aiSection, 1, 0), Locale::T(InfosSection::AIModelSizeRamKey));
    lv_label_set_text_static(GetLabel(aiSection, 1, 1), Locale::T(InfosSection::AIModelSizeRamValue));
    lv_label_set_text_static(GetLabel(aiSection, 2, 0), Locale::T(InfosSection::AIModelInferenceTimeKey));
    lv_label_set_text_static(GetLabel(aiSection, 2, 1), Locale::T(InfosSection::AIModelInferenceTimeValue));

    lv_label_set_text_static(firmwareSection.title, Locale::T(InfosSection::FirmwareTitle));
    lv_label_set_text_static(GetLabel(firmwareSection, 0, 0), Locale::T(InfosSection::FirmwareVersionKey));
    lv_label_set_text_static(GetLabel(firmwareSection, 0, 1), Locale::T(InfosSection::FirmwareVersionValue));

    list.Refresh();
    lv_obj_scroll_to_view(list.Get(0), LV_ANIM_OFF);
}

void InfoTab::Update() {
    ribbonOffset += 1;
    const i32 ribbonWidth = Assets::Ribbon.header.w;
    lv_image_set_offset_x(ribbonSection.image, -(ribbonOffset % ribbonWidth));
}
