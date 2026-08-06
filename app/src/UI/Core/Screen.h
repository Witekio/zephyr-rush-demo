/**
 * @file      Screen.h
 * @brief     Generic Screen abstraction
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

#include "Core/Game/Leaderboard.h"
#include "Core/Inference/InferenceTask.h"
#include "UI/Core/Base.h"

#include <lvgl.h>

#include <any>

class Router;

class Screen {
public:
    struct Context {
        InferenceTask& inferenceTask;
        Leaderboards& leaderboards;
        DrawEngine& drawEngine;
        Router& router;
        AppState& state;
    };

public:
    explicit Screen(Context& ctx) : ctx(ctx) {}

    virtual ~Screen() = default;

    virtual void Create() = 0;

    virtual void Refresh() {}

    virtual void Update() {}

    virtual void OnEnter(const std::any& /* payload */) {}

    virtual void OnExit() {}

    void SetRoot(lv_obj_t* root) { this->root = root; }

    lv_obj_t* Root() { return root; }

protected:
    Context& ctx;

private:
    lv_obj_t* root;
};
