/**
 * @file      App.h
 * @brief     Application header
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
#include "Core/Game/Leaderboard.h"
#include "Core/Inference/InferenceTask.h"
#include "UI/Core/Router.h"
#include "UI/Screen/GameOverScreen.h"
#include "UI/Screen/GameScreen.h"
#include "UI/Screen/MainScreen.h"

class App {
public:
    App() noexcept;
    void Run();

private:
    void Init();
    void Update();
    void Stop();

private:
    InferenceTask inferenceTask;
    Leaderboards leaderboards;
    DrawEngine drawEngine;
    Router router;
    AppState state;

    Screen::Context ctx;

    MainScreen mainScreen;
    GameScreen gameScreen;
    GameOverScreen gameOverScreen;

    static constexpr u32 kUpdatePeriodMs = 33;
    lv_timer_t* updateTimer = nullptr;
};
