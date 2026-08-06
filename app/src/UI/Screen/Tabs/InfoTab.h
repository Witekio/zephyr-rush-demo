/**
 * @file      InfoTab.h
 * @brief     UI Info tab header
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

#include "UI/Components/List.h"
#include "UI/Core/Screen.h"
#include "UI/Widgets/Lvgl.h"

class InfoTab : public Screen {
public:
    explicit InfoTab(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;
    void Update() override;

private:
    struct RibbonSection {
        LV::Label title;
        LV::Image image;
    };

    struct InfoSection {
        LV::Label title;
        LV::Label body;
    };

    struct MetricsSection {
        LV::Label title;
        LV::Obj table;
        u32 rows;
    };

    void CreateHeader();

    static RibbonSection CreateRibbonSection(lv_obj_t* parent);
    static InfoSection CreateInfoSection(lv_obj_t* parent);
    static MetricsSection CreateMetricsSection(lv_obj_t* parent, u32 rows);
    static LV::Label GetLabel(const MetricsSection& section, u32 row, u32 column);

private:
    LV::Label title;

    List list;

    u32 ribbonOffset = 0;

    InfoSection aboutSection;
    RibbonSection ribbonSection;
    MetricsSection memorySection;
    MetricsSection aiSection;
    MetricsSection firmwareSection;
};
