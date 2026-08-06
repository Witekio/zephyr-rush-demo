/**
 * @file      Router.h
 * @brief     UI Screen router
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
#include "UI/Core/Screen.h"

#include <any>
#include <array>
#include <cassert>

class Router {
public:
    static constexpr u32 kScreenCount = static_cast<u32>(Route::Count);
    using ScreenArray = std::array<Screen*, kScreenCount>;

    void NewScreen(Screen* screen, Route route) {
        u8 idx = IndexFromRoute(route);
        assert(screens[idx] == nullptr);
        screens[idx] = screen;

        auto* lvScr = lv_obj_create(nullptr);
        lv_obj_remove_flag(lvScr, LV_OBJ_FLAG_SCROLLABLE);

        screen->SetRoot(lvScr);
        screen->Create();
        screen->Refresh();
    }

    void Update() {
        if (pendingScreen) {
            UpdateScreen(pendingScreen);
            pendingScreen = nullptr;
        }
    }

    void NavigateTo(Route route, std::any payload = {}) {
        auto idx = IndexFromRoute(route);
        auto* newScreen = screens[idx];
        if (currentScreen == newScreen)
            return;

        pendingScreen = newScreen;
        pendingPayload = std::move(payload);
    }

    void RefreshScreen(Route route) {
        auto idx = IndexFromRoute(route);
        screens[idx]->Refresh();
    }

    void RefreshAllScreens() {
        for (auto* screen : screens)
            screen->Refresh();
    }

    void Start(Route route, const std::any& payload = {}) {
        auto idx = IndexFromRoute(route);
        currentScreen = screens[idx];
        lv_screen_load(currentScreen->Root());
        currentScreen->OnEnter(payload);
    }

    Screen* ActiveScreen() { return currentScreen; }

private:
    static u8 IndexFromRoute(Route route) { return static_cast<u8>(route); }

    void UpdateScreen(Screen* newScreen) {
        currentScreen->OnExit();
        currentScreen = newScreen;
        lv_screen_load(currentScreen->Root());
        currentScreen->OnEnter(pendingPayload);
        pendingPayload.reset();
    }

private:
    Screen* pendingScreen = nullptr;
    std::any pendingPayload;

    Screen* currentScreen = nullptr;
    ScreenArray screens{};
};
