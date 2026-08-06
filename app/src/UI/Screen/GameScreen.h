/**
 * @file      GameScreen.h
 * @brief     UI Game screen header
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

#include "Core/Game/GameEngine.h"
#include "UI/Components/Animation.h"
#include "UI/Components/Canvas.h"
#include "UI/Components/PausePopup.h"
#include "UI/Core/Screen.h"
#include "UI/Widgets/Widgets.h"

class GameScreen final : public Screen {
public:
    explicit GameScreen(Context& ctx) noexcept;

    void Create() override;
    void Refresh() override;

    void Update() override;

    void OnEnter(const std::any& payload) override;
    void OnExit() override;

private:
    void OnClearPress();
    void OnUndoPress();
    void OnSkipPress();
    void OnPausePress();
    void OnResumePress();
    void OnRestartPress();
    void OnMenuPress();

private:
    struct TargetLabelTransition {
        lv_anim_t* centerToLeft = nullptr;
        lv_anim_t* rightToCenter = nullptr;

        void Start(class GameScreen* screen);

        void Pause() const {
            if (centerToLeft)
                lv_anim_pause(centerToLeft);
            if (rightToCenter)
                lv_anim_pause(rightToCenter);
        }

        void Resume() const {
            if (centerToLeft)
                lv_anim_resume(centerToLeft);
            if (rightToCenter)
                lv_anim_resume(rightToCenter);
        }

        void Cancel() {
            if (centerToLeft) {
                lv_anim_delete(centerToLeft, nullptr);
                centerToLeft = nullptr;
            }
            if (rightToCenter) {
                lv_anim_delete(rightToCenter, nullptr);
                rightToCenter = nullptr;
            }
        }
    };

    struct SuccessSequence {
        lv_obj_t* fillObj = nullptr;
        lv_anim_t* fillAnim = nullptr;
        lv_timer_t* timer = nullptr;

        void Start(class GameScreen* screen);

        void Pause() const {
            if (fillAnim)
                lv_anim_pause(fillAnim);
            if (timer)
                lv_timer_pause(timer);
        }

        void Resume() const {
            if (fillAnim)
                lv_anim_resume(fillAnim);
            if (timer)
                lv_timer_resume(timer);
        }

        void Cancel() {
            if (fillAnim) {
                lv_anim_delete(fillAnim, nullptr);
                fillAnim = nullptr;
            }
            if (timer) {
                lv_timer_delete(timer);
                timer = nullptr;
            }
            if (fillObj)
                lv_obj_set_width(fillObj, 0);
        }
    };

    void ClearPredictionAndCanvas();
    void SetControlsEnabled(bool enabled);

private:
    Canvas canvas;
    PausePopup pausePopup;

    LV::Label timerLabel;
    LV::Label scoreLabel;
    LV::Label currentTargetLabel;
    LV::Label nextTargetLabel;

    LV::Obj inferenceBox;
    LV::Label inferenceLabel;

    LV::Button clearButton;
    LV::Button undoButton;
    LV::Button skipButton;
    LV::Label skipLabel;

    // Animations
    Animation::ShakeParams wrongLabelAnimParams;
    TargetLabelTransition targetLabelTransition;
    SuccessSequence successSeq;

    // Game logic
    GameEngine game;
    u32 currentInferenceID = -1;
};
