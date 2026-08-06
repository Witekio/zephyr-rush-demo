/**
 * @file      GameEngine.h
 * @brief     Game's logic header
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
#include "Core/Inference/InferenceTask.h"
#include "Core/Time.h"

enum class GameMode : u8 {
    Round = 0,
    Speed,
    Survival,
};

struct GameEvent {
    enum class Type : u8 {
        InferenceResult,
        NewTarget,
        GameOver,
        Success,
    } type;
    u16 v;
};

struct GameScore {
    u32 success;
    u32 total;
};

class GameEngine {
    using Label = DrawClassifier::Label;

public:
    explicit GameEngine(IntoInferenceTask& canvas, InferenceTask& task);

    void Start(GameMode mode);
    void Restart();
    void Pause();
    void Resume();
    void Skip();
    void InvalidateNextPrediction();

    void Update();
    bool PollEvents(GameEvent& event);

    // clang-format off
    bool IsGameOver() const { return gameOver; }
    bool IsPaused() const { return clock.IsPaused(); }
    u32 Success() const { return success; }
    u32 Skips() const { return skips; }
    u32 RoundCount() const { return roundCount; }
    GameMode CurrentMode() const { return mode; }
    bool CanSkip() const { return IS_SKIP_AUTHORIZED[Idx()]; }
    Label GetTarget() const { return target; }
    u32 TimerRemainingSeconds() const { return roundTimer.RemainingSeconds(); }
    // clang-format on

private:
    u8 Idx() const { return static_cast<u8>(mode); }

    bool IsRoundBasedMode() const { return ROUND_PER_MODE[Idx()] != kInfinit; }

    void PushEvent(GameEvent event);

    bool EvaluatePendingInference();
    void TryStartInference();
    void Advance(bool win, bool timeIsOut);
    bool RateInference(const DrawClassifier::Predictions& predictions);

    static Label RandomLabel(bool reset = false);

private:
    // clang-format off
    //      RULES
    //      Mode                      = { Round    , Speed   , Survival };
    u32     TIME_PER_ROUND_S[3]       = { 30       , 120     , 20       };
    u32     REWARD_PER_SUCCESS_S[3]   = { 0        , 0       , 5        };
    u32     ROUND_PER_MODE[3]         = { 5        , kInfinit, kInfinit };
    bool    RESET_TIMER_ON_SUCCESS[3] = { true     , false   , true     };
    bool    IS_SKIP_AUTHORIZED[3]     = { false    , true    , true     };

    static constexpr u32 kInfinit              = UINT32_MAX;
    static constexpr u32 kTopNAccept           = 3;
    static constexpr u32 kInferenceTimePeriodS = 1;

private:
    // Logic/State
    GameMode mode       = GameMode::Round;
    u32      roundCount = 0;
    u32      success    = 0;
    u32      skips      = 0;
    bool     gameOver   = false;
    Label    target     = DrawClassifier::Label::Square;

    // Timings
    Clock clock;
    Timer roundTimer;
    Timer inferenceTimer;

    // Inference
    IntoInferenceTask& canvas;
    InferenceTask& task;
    std::optional<u32> inferenceID = 0;

    // Event queue
    std::array<GameEvent, 10> events;
    u32 eventCount;
    u32 eventHead;

    // clang-format on
};
