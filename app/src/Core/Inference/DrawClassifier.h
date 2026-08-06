/**
 * @file      DrawClassifier.h
 * @brief     DrawClassifierModel Interpreter implementation
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
#include "Core/Draw/StrokeStorage.h"
#include "DrawClassifierModel.h"
#include "Interpreter.h"

constexpr u32 kTensorArenaSize = 64 << 10; // 64 KiB

/*
 * @brief Custom interpreter for the DrawClassifierModel
 *
 * This class implements the inference logic for the DrawClassifier model.
 * It handles pre-processing of input data and provides simplified access to model results.
 */
class DrawClassifier : public Interpreter<DrawClassifierModel, kTensorArenaSize> {
public:
    using Interpreter::Model;
    using Label = Model::Label;

    struct Prediction {
        Label label;
        u8 percentage;
    };

    using Predictions = std::array<Prediction, Model::kOutputSize>;
    using Canvas = Draw::Canvas<28, 28>;

public:
    DrawClassifier() : rasterizer(kRasterAntialias, kRasterLineWidth, kRasterColor) {}

    template <u32 N>
    void Infer(const Draw::StrokeStorage<N>& strokes) {
        {
            canvas.Clear(0);

            auto bbox = strokes.ComputeBBox();
            Vec2f size = bbox.SizeF();
            f32 scale = 24.0f / Vec2f::Max(size);
            Vec2f offset = (Vec2f(28.f) - size * scale) / 2.0f - Vec2f(bbox.start) * scale;

            rasterizer.SetScale(scale);
            rasterizer.SetOffset(offset);

            strokes.RasterTo(canvas, rasterizer);
        }

        {

            const u8* canvasRaw = canvas.Data();
            for (u32 i = 0; i < 28 * 28; i++)
                input[i] = static_cast<i16>(canvasRaw[i]) - 128;
        }

        {
            bool success = Invoke();
            (void)success;
        }

        {
            for (u32 i = 0; i < kOutputSize; i++) {
                auto& [label, pct] = predictions[i];
                label = Model::LabelFromIndex(i);
                pct = static_cast<u8>((static_cast<i16>(output[i]) + 128) * 100 / 255);
            }

            std::ranges::sort(predictions, [](Prediction a, Prediction b) { return a.percentage > b.percentage; });
        }
    }

    const Predictions& GetPredictions() const { return predictions; }

    const Canvas& GetCanvas() const { return canvas; }

private:
    static constexpr u32 kOutputSize = Model::kOutputSize;
    static constexpr f32 kRasterAntialias = 1.3f;
    static constexpr u32 kRasterLineWidth = 0;
    static constexpr u8 kRasterColor = 255;

private:
    Canvas canvas;
    Predictions predictions;
    Draw::Rasterizer rasterizer;
};
