/**
 * @file      Time.h
 * @brief     Time related utilities
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

#include <algorithm>
#include <cstdio>

#include "Core/Base.h"
#include "Platform/Zephyr/Platform.h"

class Clock {
    using Tick = Platform::Tick;

public:
    void Pause() {
        if (paused)
            return;
        paused = true;
        pauseStart = Tick::Now();
    }

    void Resume() {
        if (!paused)
            return;
        pausedAccum = pausedAccum + (Tick::Now() - pauseStart);
        paused = false;
    }

    bool IsPaused() const { return paused; }

    Tick Now() const { return paused ? (pauseStart - pausedAccum) : (Tick::Now() - pausedAccum); }

    void Reset() { *this = Clock(); }

private:
    bool paused = false;
    Tick pauseStart{};
    Tick pausedAccum{};
};

class Timer {
    using Tick = Platform::Tick;

public:
    explicit Timer(Clock& clock) : clock(clock) {}

    void Duration(u32 seconds) { duration = Tick::FromSeconds(seconds); }

    bool Expired() const { return !(clock.Now() < anchor + duration); }

    void Restart() { anchor = clock.Now(); }

    void Extend(u32 seconds) { duration = duration + Tick::FromSeconds(seconds); }

    u32 RemainingSeconds() const {
        auto remainingTicks = duration - (clock.Now() - anchor);
        return std::max(0u, remainingTicks.ToSeconds());
    }

    void SetExpired() { anchor = clock.Now() - duration; }

private:
    Clock& clock;
    Tick anchor{};
    Tick duration{};
};
