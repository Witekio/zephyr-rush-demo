/**
 * @file      Platform.h
 * @brief     Generic platform helpers
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

namespace Platform {
    void Init();
    void SleepMS(u32 ms);
    u32 Random32();
    void Panic(const char* msg);

    struct Tick {
        i64 value = 0;

        static Tick FromSeconds(u32 seconds);
        u32 ToSeconds() const;
        static Tick Now();

        friend Tick operator+(Tick a, Tick b) { return {a.value + b.value}; }

        friend Tick operator-(Tick a, Tick b) { return {a.value - b.value}; }

        friend bool operator<(Tick a, Tick b) { return a.value < b.value; }

        friend bool operator==(Tick a, Tick b) { return a.value == b.value; }
    };
} // namespace Platform
