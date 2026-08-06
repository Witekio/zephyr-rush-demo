/**
 * @file      Leaderboard.h
 * @brief     Game's leaderboard header
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

#include <array>

#include "Core/Base.h"
#include "Core/Game/GameEngine.h"

class Leaderboard {
    static constexpr u32 kMaxCapacity = 32;

public:
    static constexpr u32 kMaxUsernameLength = 10;
    using Username = std::array<char, kMaxUsernameLength + 1>;

    struct Entry {
        Username name;
        GameScore score;
    };

    using EntryIndex = std::optional<u32>;

public:
    Leaderboard() = default;

    EntryIndex PushEntry(const char* name, GameScore score);
    void Clear();

    u32 Count() const;
    const Entry& GetEntry(u32 idx) const;

    static constexpr u32 Capacity() { return kMaxCapacity; }

private:
    u32 FindPlace(GameScore score) const;
    void ShiftDown(u32 index);
    static void CopyUsername(Username& dst, const char* src);

    static i32 Compare(GameScore a, GameScore b);

private:
    std::array<Entry, kMaxCapacity> entries;
    u32 entryCount = 0;
};

struct Leaderboards {
    Leaderboard round;
    Leaderboard speed;
    Leaderboard survival;

    Leaderboard& Get(GameMode mode);
    void Clear();
};
