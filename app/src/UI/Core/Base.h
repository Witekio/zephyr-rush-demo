/**
 * @file      Base.h
 * @brief     UI basic define layer
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

#include <any>

#include "Core/Draw/Engine.h"
#include "Core/Game/GameEngine.h"
#include "Core/Game/Leaderboard.h"
#include "Platform/Zephyr/FS.h"
#include "UI/Theme/Translations.h"

constexpr i32 kScreenWidth = 272;
constexpr i32 kScreenHeight = 480;

using DrawEngine = Draw::Engine<kScreenWidth, kScreenHeight, 4096, 10>;

enum class Route : u8 {
    Main = 0,
    Game,
    GameOver,

    Count,
};

enum class MainTabs : u8 {
    Info = 0,
    Leaderboard,
    Menu,
    FreeDraw,
    Settings,

    Count,
};

namespace Payload {
    struct GameMode {
        ::GameMode mode = ::GameMode::Round;
    };

    struct GameScore {
        ::GameScore score;
        ::GameMode mode;
    };

    struct MainMenu {
        MainTabs tab;
        std::any tabPayload;
    };

    struct LeaderboardTab {
        ::GameMode mode;
        Leaderboard::EntryIndex idx;
    };
} // namespace Payload

namespace SaveFiles {
    inline constexpr auto State = Platform::FS::MakePath("state.bin");
    inline constexpr auto Leaderboards = Platform::FS::MakePath("ldb.bin");
} // namespace SaveFiles

struct AppState {
    Language language = Language::EnUs;
};
