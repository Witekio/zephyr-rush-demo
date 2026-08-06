/**
 * @file      GameScreen.cpp
 * @brief     UI Game screen implementation
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

#include "GameScreen.h"

#include "UI/Components/Animation.h"
#include "UI/Core/Base.h"
#include "UI/Core/Locale.h"
#include "UI/Core/Router.h"
#include "UI/Core/Utils.h"
#include "UI/Theme/Styles.h"

GameScreen::GameScreen(Context& ctx) noexcept
    : Screen(ctx),
      canvas(ctx.drawEngine),
      game(canvas, ctx.inferenceTask) {}

void GameScreen::Create() {
    // Canvas
    {
        canvas.Create(Root());
        lv_obj_set_size(canvas.Obj(), lv_pct(100), lv_pct(100));
    }

    // Header
    {
        auto vbox = VBox::Create(Root());
        lv_obj_align(vbox, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_set_size(vbox, lv_pct(100), lv_pct(18));
        lv_obj_move_foreground(vbox);

        lv_obj_set_style_text_font(vbox, UI::Fonts::F22, 0);
        lv_obj_set_style_text_color(vbox, UI::Colors::GRAY, 0);
        lv_obj_set_style_pad_all(vbox, 10, 0);
        lv_obj_set_style_pad_row(vbox, 10, 0);

        // First row
        auto hbox = HBox::Create(vbox);
        lv_obj_set_width(hbox, lv_pct(100));
        lv_obj_set_flex_grow(hbox, 1);

        // Timer
        auto timerBox = Box::Create(hbox);
        lv_obj_set_height(timerBox, lv_pct(100));
        lv_obj_set_flex_grow(timerBox, 1);

        timerLabel = LV::Label::Create(timerBox);
        lv_obj_center(timerLabel);

        // Score
        auto scoreBox = Box::Create(hbox);
        lv_obj_set_height(scoreBox, lv_pct(100));
        lv_obj_set_flex_grow(scoreBox, 1);

        scoreLabel = LV::Label::Create(scoreBox);
        lv_obj_center(scoreLabel);

        // Pause
        auto pauseBox = Box::Create(hbox);
        lv_obj_set_height(pauseBox, lv_pct(100));
        lv_obj_set_flex_grow(pauseBox, 1);

        auto pauseButton = LV::Button::Create(pauseBox);
        lv_obj_remove_style_all(pauseButton);
        lv_obj_set_size(pauseButton, lv_pct(100), lv_pct(100));
        lv_obj_center(pauseButton);
        lv_obj_add_event_cb(pauseButton, LV_BIND_EVENT_CB(GameScreen, OnPausePress), LV_EVENT_CLICKED, this);

        auto pauseLabel = LV::Label::Create(pauseButton);
        lv_obj_center(pauseLabel);
        lv_label_set_text_static(pauseLabel, "PAUSE");
        lv_obj_set_style_text_decor(pauseLabel, LV_TEXT_DECOR_UNDERLINE, 0);

        // Second row
        inferenceBox = Box::Create(vbox);
        lv_obj_set_width(inferenceBox, lv_pct(100));
        lv_obj_set_flex_grow(inferenceBox, 1);

        lv_obj_set_style_outline_color(inferenceBox, UI::Colors::GRAY, 0);
        lv_obj_set_style_outline_width(inferenceBox, 3, 0);
        lv_obj_set_style_outline_opa(inferenceBox, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(inferenceBox, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_clip_corner(inferenceBox, true, 0);

        successSeq.fillObj = Box::Create(inferenceBox);
        lv_obj_clear_flag(successSeq.fillObj, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_height(successSeq.fillObj, lv_pct(100));
        lv_obj_set_width(successSeq.fillObj, 0);
        lv_obj_align(successSeq.fillObj, LV_ALIGN_CENTER, 0, 0);

        lv_obj_set_style_radius(successSeq.fillObj, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_bg_color(successSeq.fillObj, UI::Colors::GREEN_SUCCESS, 0);
        lv_obj_set_style_bg_opa(successSeq.fillObj, LV_OPA_COVER, 0);

        inferenceLabel = LV::Label::Create(inferenceBox);
        lv_label_set_long_mode(inferenceLabel, LV_LABEL_LONG_MODE_SCROLL_CIRCULAR);
        lv_obj_center(inferenceLabel);

        wrongLabelAnimParams = {
            .obj = inferenceLabel,
            .duration = 400,
            .cycles = 1.5f,
            .amplitude = 10.f,
        };
    }

    // Word-to-draw label
    {
        currentTargetLabel = LV::Label::Create(Root());
        lv_obj_center(currentTargetLabel);
        lv_obj_set_width(currentTargetLabel, lv_pct(95));

        lv_obj_set_style_text_align(currentTargetLabel, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_add_style(currentTargetLabel, &UI::Styles::Text::DARK32, 0);
        lv_obj_set_style_text_opa(currentTargetLabel, LV_OPA_50, 0);

        nextTargetLabel = LV::Label::Create(Root());
        lv_obj_center(nextTargetLabel);
        lv_obj_set_width(nextTargetLabel, lv_pct(95));

        lv_obj_set_style_text_align(nextTargetLabel, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_add_style(nextTargetLabel, &UI::Styles::Text::DARK32, 0);
        lv_obj_set_style_text_opa(nextTargetLabel, LV_OPA_50, 0);
    }

    // Footer
    {
        auto hbox = HBox::Create(Root());
        lv_obj_set_flex_align(hbox, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_size(hbox, lv_pct(100), LV_SIZE_CONTENT);
        lv_obj_align(hbox, LV_ALIGN_BOTTOM_MID, 0, 0);

        lv_obj_set_style_pad_all(hbox, 20, 0);

        clearButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(clearButton, LV_BIND_EVENT_CB(GameScreen, OnClearPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(clearButton, 48, 48);
        lv_obj_add_style(clearButton, &UI::Styles::Button::BLUE, 0);

        auto clearIcon = LV::Image::Create(clearButton);
        lv_image_set_src(clearIcon, &Assets::ClearIcon);
        lv_obj_center(clearIcon);

        undoButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(undoButton, LV_BIND_EVENT_CB(GameScreen, OnUndoPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(undoButton, 48, 48);
        lv_obj_add_style(undoButton, &UI::Styles::Button::BLUE, 0);

        auto undoIcon = LV::Image::Create(undoButton);
        lv_image_set_src(undoIcon, &Assets::UndoIcon);
        lv_obj_center(undoIcon);

        skipButton = LV::Button::Create(hbox);
        lv_obj_add_event_cb(skipButton, LV_BIND_EVENT_CB(GameScreen, OnSkipPress), LV_EVENT_CLICKED, this);
        lv_obj_set_size(skipButton, LV_SIZE_CONTENT, 48);
        lv_obj_add_style(skipButton, &UI::Styles::Button::ORANGE, 0);

        skipLabel = LV::Label::Create(skipButton);
        lv_obj_center(skipLabel);
    }

    // Popup
    {
        pausePopup.Create(Root());
        pausePopup.SetCallbacks(this, LV_BIND_EVENT_CB(GameScreen, OnResumePress),
                                LV_BIND_EVENT_CB(GameScreen, OnRestartPress),
                                LV_BIND_EVENT_CB(GameScreen, OnMenuPress));
        pausePopup.Hide();
    }
}

void GameScreen::Refresh() {
    lv_label_set_text(timerLabel, "");
    lv_label_set_text(scoreLabel, "");
    lv_label_set_text(inferenceLabel, "");
    lv_label_set_text(currentTargetLabel, "");
    lv_label_set_text(nextTargetLabel, "");
    lv_label_set_text_static(skipLabel, Locale::T(TKey::Skip));
    pausePopup.Refresh();
}

void GameScreen::Update() {
    if (!pausePopup.Hidden())
        return;

    auto lastTarget = game.GetTarget();
    game.Update();

    GameEvent event;
    while (game.PollEvents(event)) {
        auto [type, value] = event;
        switch (type) {
        case GameEvent::Type::InferenceResult: {
            auto resultLabel = DrawClassifierModel::LabelFromIndex(value);
            bool isWinLabel = resultLabel == lastTarget;
            lv_label_set_text_static(inferenceLabel, Locale::T(resultLabel));

            if (!isWinLabel)
                Animation::Shake(&wrongLabelAnimParams);

            break;
        }
        case GameEvent::Type::NewTarget: {
            ClearPredictionAndCanvas();
            lv_label_set_text_fmt(scoreLabel, "%02u/%02u", game.Success(), game.RoundCount());
            targetLabelTransition.Start(this);
            break;
        }
        case GameEvent::Type::GameOver: {
            ctx.router.NavigateTo(Route::GameOver,
                                  Payload::GameScore{
                                      .score = {.success = game.Success(), .total = game.RoundCount()},
                                      .mode = game.CurrentMode(),
                                  });
            break;
        }
        case GameEvent::Type::Success: {
            game.Pause();
            canvas.Freeze();
            SetControlsEnabled(false);
            successSeq.Start(this);
            break;
        }
        }
    }

    // Update timer label
    u32 remainingSeconds = game.TimerRemainingSeconds();
    lv_label_set_text_fmt(timerLabel, "%02u:%02u", remainingSeconds / 60, remainingSeconds % 60);
}

void GameScreen::OnEnter(const std::any& payload) {
    ClearPredictionAndCanvas();
    ctx.inferenceTask.SetID(UINT32_MAX);
    auto gameMode = GameMode::Round;
    if (payload.has_value()) {
        gameMode = std::any_cast<Payload::GameMode>(payload).mode;
    }
    game.Start(gameMode);

    if (game.CanSkip())
        lv_obj_remove_state(skipButton, LV_STATE_DISABLED);
    else
        lv_obj_add_state(skipButton, LV_STATE_DISABLED);
}

void GameScreen::OnExit() {
    pausePopup.Hide();
    successSeq.Cancel();
    targetLabelTransition.Cancel();
}

void GameScreen::OnClearPress() {
    if (game.IsPaused())
        return;

    ClearPredictionAndCanvas();
}

void GameScreen::OnUndoPress() {
    if (game.IsPaused())
        return;

    canvas.Undo();
    if (canvas.Empty())
        ClearPredictionAndCanvas();
}

void GameScreen::OnSkipPress() {
    if (game.IsPaused())
        return;

    game.Skip();
    ClearPredictionAndCanvas();
}

void GameScreen::OnPausePress() {
    game.Pause();
    pausePopup.Show();
    targetLabelTransition.Pause();
    successSeq.Pause();
}

void GameScreen::OnResumePress() {
    pausePopup.Hide();
    game.Resume();
    targetLabelTransition.Resume();
    successSeq.Resume();
}

void GameScreen::OnRestartPress() {
    ClearPredictionAndCanvas();
    game.Restart();
    pausePopup.Hide();
    targetLabelTransition.Cancel();
    successSeq.Cancel();
}

void GameScreen::OnMenuPress() {
    ctx.router.NavigateTo(Route::Main);
}

void GameScreen::ClearPredictionAndCanvas() {
    lv_label_set_text(inferenceLabel, "");
    canvas.Clear();
    currentInferenceID++;
    game.InvalidateNextPrediction();
}

void GameScreen::SetControlsEnabled(bool enabled) {
    if (enabled) {
        lv_obj_remove_state(clearButton, LV_STATE_DISABLED);
        lv_obj_remove_state(undoButton, LV_STATE_DISABLED);
        lv_obj_remove_state(skipButton, LV_STATE_DISABLED);
    } else {
        lv_obj_add_state(clearButton, LV_STATE_DISABLED);
        lv_obj_add_state(undoButton, LV_STATE_DISABLED);
        lv_obj_add_state(skipButton, LV_STATE_DISABLED);
    }
    lv_obj_invalidate(clearButton);
    lv_obj_invalidate(undoButton);
    lv_obj_invalidate(skipButton);
}

void GameScreen::TargetLabelTransition::Start(GameScreen* screen) {
    constexpr i32 kAnimTransTimeMs = 700;

    const char* newText = Locale::T(screen->game.GetTarget());

    lv_label_set_text_static(screen->nextTargetLabel, newText);
    lv_obj_set_pos(screen->nextTargetLabel, kScreenWidth, 0);
    lv_obj_remove_flag(screen->nextTargetLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(screen->skipButton, LV_STATE_DISABLED);

    // old label (center -> left)
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, screen->currentTargetLabel);
    lv_anim_set_values(&a1, 0, -lv_obj_get_width(screen->currentTargetLabel));
    lv_anim_set_duration(&a1, kAnimTransTimeMs);
    lv_anim_set_exec_cb(&a1, [](void* obj, int32_t x) { lv_obj_set_x(static_cast<lv_obj_t*>(obj), x); });
    lv_anim_set_path_cb(&a1, lv_anim_path_bounce);
    centerToLeft = lv_anim_start(&a1);

    // new label (right -> center)
    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, screen->nextTargetLabel);
    lv_anim_set_values(&a2, kScreenWidth, 0);
    lv_anim_set_duration(&a2, kAnimTransTimeMs);
    lv_anim_set_exec_cb(&a2, [](void* obj, int32_t x) { lv_obj_set_x(static_cast<lv_obj_t*>(obj), x); });
    lv_anim_set_path_cb(&a2, lv_anim_path_bounce);
    lv_anim_set_completed_cb(&a2, [](lv_anim_t* a) {
        auto* self = static_cast<GameScreen*>(a->user_data);
        std::swap(self->currentTargetLabel, self->nextTargetLabel);
        lv_obj_add_flag(self->nextTargetLabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_state(self->skipButton, LV_STATE_DISABLED);
        self->targetLabelTransition = {.centerToLeft = nullptr, .rightToCenter = nullptr};
    });
    lv_anim_set_user_data(&a2, screen);
    rightToCenter = lv_anim_start(&a2);
}

void GameScreen::SuccessSequence::Start(GameScreen* screen) {
    lv_obj_set_width(fillObj, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, fillObj);
    lv_anim_set_values(&a, 0, lv_obj_get_width(screen->inferenceBox));
    lv_anim_set_duration(&a, 350);
    lv_anim_set_user_data(&a, this);
    lv_anim_set_exec_cb(&a, [](void* obj, int32_t v) { lv_obj_set_width(static_cast<lv_obj_t*>(obj), v); });
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_deleted_cb(
        &a, [](lv_anim_t* anim) { static_cast<SuccessSequence*>(anim->user_data)->fillAnim = nullptr; });
    fillAnim = lv_anim_start(&a);

    timer = lv_timer_create(
        [](lv_timer_t* t) {
            auto* self = static_cast<GameScreen*>(lv_timer_get_user_data(t));
            self->canvas.Clear();
            self->canvas.UnFreeze();
            self->game.Resume();
            self->SetControlsEnabled(true);
            self->successSeq.Cancel();
        },
        500, screen);
}
