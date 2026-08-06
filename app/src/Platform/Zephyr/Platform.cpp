/**
 * @file      Platform.cpp
 * @brief     Zephyr platform helpers implementation
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

#include "Platform.h"

#include <lvgl.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

void Platform::Init() {
#if CONFIG_PLATFORM_DISPLAY_BLANKING_OFF
    const auto* displayDev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (device_is_ready(displayDev)) {
        lv_timer_handler();
        display_blanking_off(displayDev);
    }
#endif

#ifdef CONFIG_PLATFORM_DISPLAY_ROTATION_90
    lv_display_set_rotation(lv_display_get_default(), LV_DISPLAY_ROTATION_90);
#endif
}

void Platform::SleepMS(u32 ms) {
    k_sleep(K_MSEC(ms));
}

u32 Platform::Random32() {
    return sys_rand32_get();
}

void Platform::Panic(const char* msg) {
    printk("PANIC: %s\n", msg);

    while (true) {
        k_sleep(K_FOREVER);
    }
}

static constexpr i64 kTicksPerSecond = CONFIG_SYS_CLOCK_TICKS_PER_SEC;

Platform::Tick Platform::Tick::FromSeconds(u32 seconds) {
    return Tick{static_cast<i64>(seconds) * kTicksPerSecond};
}

u32 Platform::Tick::ToSeconds() const {
    return value / kTicksPerSecond;
}

Platform::Tick Platform::Tick::Now() {
    return {k_uptime_ticks()};
}
