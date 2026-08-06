/**
 * @file      InferenceTask.h
 * @brief     Draw classifier InferenceTask implementation
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

#include "Core/Draw/StrokeStorage.h"
#include "Core/Inference/DrawClassifier.h"
#include "Platform/Zephyr/WorkerThread.h"

class InferenceTask final : public Task {
public:
    InferenceTask() noexcept = default;

    void Prepare(const Draw::StrokeStorage<4096>& src) { strokes = src; }

    void Run() override { classifier.Infer(strokes); }

    const auto& GetPredictions() const { return classifier.GetPredictions(); }

    const auto& GetCanvas() const { return classifier.GetCanvas(); }

private:
    Draw::StrokeStorage<4096> strokes;
    DrawClassifier classifier;
};

class IntoInferenceTask {
public:
    virtual ~IntoInferenceTask() = default;
    virtual bool CaptureInto(InferenceTask& task) const = 0;
};
