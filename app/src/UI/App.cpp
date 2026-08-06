/**
 * @file      App.cpp
 * @brief     Application implementation
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

#include "App.h"

#include "UI/Core/Locale.h"
#include "UI/Theme/Styles.h"

App::App() noexcept
    : ctx{
          .inferenceTask = inferenceTask,
          .leaderboards = leaderboards,
          .drawEngine = drawEngine,
          .router = router,
          .state = state,
      },
      mainScreen(ctx),
      gameScreen(ctx),
      gameOverScreen(ctx) {}

void App::Run() {
    Init();
    while (true) {
        Update();
    }
}

void App::Init() {
    Platform::FS::Load(SaveFiles::State, state);
    Platform::FS::Load(SaveFiles::Leaderboards, leaderboards);

    UI::Styles::Init();

    Locale::Set(state.language);

    router.NewScreen(&mainScreen, Route::Main);
    router.NewScreen(&gameScreen, Route::Game);
    router.NewScreen(&gameOverScreen, Route::GameOver);

    router.Start(Route::Main, Payload::MainMenu{.tab = MainTabs::Menu, .tabPayload = {}});

    updateTimer = lv_timer_create(
        [](lv_timer_t* t) {
            auto* router = static_cast<Router*>(lv_timer_get_user_data(t));
            auto* active = router->ActiveScreen();
            if (active)
                active->Update();
        },
        kUpdatePeriodMs, &router);
}

void App::Update() {
    router.Update();
    u32 delay = lv_timer_handler();
    Platform::SleepMS(delay);
}
