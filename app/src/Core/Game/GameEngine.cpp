/**
 * @file      GameEngine.cpp
 * @brief     Game's logic implementation
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

#include "GameEngine.h"

#include <random>

GameEngine::GameEngine(IntoInferenceTask& canvas, InferenceTask& task)
    : roundTimer(clock),
      inferenceTimer(clock),
      canvas(canvas),
      task(task) {}

void GameEngine::Start(GameMode mode_) {
    // Logic/State
    mode = mode_;
    roundCount = 0;
    success = 0;
    skips = 0;
    gameOver = false;
    target = RandomLabel(true);

    // Timings
    clock.Reset();

    roundTimer.Duration(TIME_PER_ROUND_S[Idx()]);
    roundTimer.Restart();

    inferenceTimer.Duration(kInferenceTimePeriodS);
    inferenceTimer.SetExpired();

    // Inference
    inferenceID = 0;

    // Event queue
    eventCount = 0;
    eventHead = 0;

    // On start events
    PushEvent({.type = GameEvent::Type::NewTarget});
}

void GameEngine::Restart() {
    Start(mode);
}

void GameEngine::Pause() {
    if (clock.IsPaused())
        return;

    clock.Pause();
}

void GameEngine::Resume() {
    if (!clock.IsPaused())
        return;

    clock.Resume();
}

void GameEngine::Skip() {
    if (gameOver || clock.IsPaused() || !CanSkip())
        return;

    skips++;
    Advance(false, false);
}

void GameEngine::InvalidateNextPrediction() {
    if (gameOver || clock.IsPaused() || !CanSkip())
        return;

    inferenceID = std::nullopt;
}

void GameEngine::Update() {
    if (gameOver || clock.IsPaused())
        return;

    bool roundWin = EvaluatePendingInference();
    if (!roundWin)
        TryStartInference();

    if (roundWin) {
        Advance(true, false);
        return;
    }

    if (roundTimer.Expired()) {
        Advance(false, true);
        return;
    }
}

bool GameEngine::PollEvents(GameEvent& event) {
    if (clock.IsPaused())
        return false;

    if (eventCount == 0) {
        eventHead = 0;
        return false;
    }

    event = events[eventHead++];
    --eventCount;

    return true;
}

void GameEngine::PushEvent(GameEvent event) {
    if (eventCount < events.size())
        events[eventCount++] = event;
}

bool GameEngine::EvaluatePendingInference() {
    if (!inferenceID || !task.Ready() || task.ID() != *inferenceID)
        return false;

    auto prediction = task.GetPredictions();
    inferenceID = std::nullopt;
    bool roundWin = RateInference(prediction);
    // When round is won, send the target label regardless of its position
    u16 labelSend = roundWin ? static_cast<u16>(target) : static_cast<u16>(prediction[0].label);
    PushEvent({.type = GameEvent::Type::InferenceResult, .v = labelSend});
    return roundWin;
}

void GameEngine::TryStartInference() {
    if (!inferenceTimer.Expired())
        return;

    if (WorkerThread::Get().Busy())
        return;

    if (!canvas.CaptureInto(task))
        return;

    inferenceID = task.ID();
    WorkerThread::Get().Submit(task);
    inferenceTimer.Restart();
}

void GameEngine::Advance(bool win, bool timeIsOut) {
    success += static_cast<u32>(win);
    roundCount++;

    if (IsRoundBasedMode()) {
        if (roundCount >= ROUND_PER_MODE[Idx()]) {
            PushEvent({.type = GameEvent::Type::GameOver});
            return;
        }

        roundTimer.Restart();
    } else {
        if (timeIsOut) {
            PushEvent({.type = GameEvent::Type::GameOver});
            return;
        }
    }

    if (win) {
        u32 bonus = REWARD_PER_SUCCESS_S[Idx()];
        if (bonus != 0) {
            roundTimer.Extend(bonus);
        }
        PushEvent({.type = GameEvent::Type::Success});
    }

    target = RandomLabel();
    PushEvent({.type = GameEvent::Type::NewTarget});
}

bool GameEngine::RateInference(const DrawClassifier::Predictions& predictions) {
    for (u32 i = 0; i < kTopNAccept; ++i) {
        if (predictions[i].label == target) {
            return true;
        }
    }
    return false;
}

GameEngine::Label GameEngine::RandomLabel(bool reset) {
    static u32 index = -1;
    static std::array<u32, DrawClassifierModel::kLabelCount> indices;
    static std::mt19937 gen{Platform::Random32()};

    if (reset || index > indices.size()) {
        for (u32 i = 0; i < indices.size(); i++)
            indices[i] = i;

        std::ranges::shuffle(indices, gen);

        index = 0;
    }

    return DrawClassifier::Model::LabelFromIndex(indices[index++]);
}
