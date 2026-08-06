/**
 * @file      Leaderboard.cpp
 * @brief     Game's leaderboard implementation
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

#include "Leaderboard.h"

#include <cstdio>

Leaderboard::EntryIndex Leaderboard::PushEntry(const char* name, GameScore score) {
    u32 idx = FindPlace(score);
    if (idx >= Capacity())
        return std::nullopt;

    ShiftDown(idx);

    auto& entry = entries[idx];
    CopyUsername(entry.name, name);
    entry.score = score;

    entryCount = std::min(entryCount + 1, Capacity());
    return idx;
}

void Leaderboard::Clear() {
    entryCount = 0;
}

u32 Leaderboard::Count() const {
    return entryCount;
}

const Leaderboard::Entry& Leaderboard::GetEntry(u32 idx) const {
    assert(idx < entryCount);
    return entries[idx];
}

u32 Leaderboard::FindPlace(GameScore score) const {
    for (u32 i = 0; i < entryCount; ++i) {
        if (Compare(score, entries[i].score) >= 0)
            return i;
    }

    if (entryCount < Capacity())
        return entryCount;

    // Invalid index
    return Capacity();
}

void Leaderboard::ShiftDown(u32 index) {
    for (u32 i = std::min(entryCount, Capacity() - 1); i > index; --i)
        entries[i] = entries[i - 1];
}

void Leaderboard::CopyUsername(Username& dst, const char* src) {
    strncpy(dst.data(), src, kMaxUsernameLength);
    dst[kMaxUsernameLength] = '\0';
}

i32 Leaderboard::Compare(GameScore a, GameScore b) {
    // clang-format off
    // Success (descending)
    if (a.success > b.success) return 1;
    if (a.success < b.success) return -1;

    // Total (ascending)
    if (a.total > b.total) return -1;
    if (a.total < b.total) return 1;

    return 0;
    // clang-format on
}

Leaderboard& Leaderboards::Get(GameMode mode) {
    // clang-format off
    switch (mode) {
    case GameMode::Round:    return round;
    case GameMode::Speed:    return speed;
    case GameMode::Survival: return survival;
    }
    std::unreachable();
    // clang-format on
}

void Leaderboards::Clear() {
    round.Clear();
    speed.Clear();
    survival.Clear();
}
