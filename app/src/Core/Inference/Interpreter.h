/**
 * @file      Interpreter.h
 * @brief     Generic TensorFlow Lite interpreter
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

#include <cassert>
#include <span>

#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>

#include "Core/Base.h"
#include "Platform/Zephyr/Platform.h"

template <typename ModelT, u32 kTensorArenaSize>
class Interpreter {
public:
    using Model = ModelT;
    using InputType = Model::InputT;
    using OutputType = Model::OutputT;

    // Non-copyable
    Interpreter(const Interpreter&) = delete;
    Interpreter& operator=(const Interpreter&) = delete;
    Interpreter(Interpreter&&) = delete;
    Interpreter& operator=(Interpreter&&) = delete;

public:
    Interpreter()
        : model(tflite::GetModel(Model::Bytes)),
          interpreter(model, resolver, tensorArena, kTensorArenaSize) {
        if (model->version() != TFLITE_SCHEMA_VERSION)
            Platform::Panic("Interpreter: schema version mismatch");

        RegisterOps();

        if (interpreter.AllocateTensors() != kTfLiteOk)
            Platform::Panic("Interpreter: failed to allocate tensors");

        TfLiteTensor* inputTensor = interpreter.input(0);
        TfLiteTensor* outputTensor = interpreter.output(0);
        input = {reinterpret_cast<InputType*>(inputTensor->data.raw), Model::kInputSize};
        output = {reinterpret_cast<OutputType*>(outputTensor->data.raw), Model::kOutputSize};
    }

protected:
    bool Invoke() { return interpreter.Invoke() == kTfLiteOk; }

private:
    void RegisterOps() {
        resolver.AddConv2D();
        resolver.AddMaxPool2D();
        resolver.AddFullyConnected();
        resolver.AddRelu();
        resolver.AddSoftmax();
        resolver.AddShape();
        resolver.AddStridedSlice();
        resolver.AddPack();
        resolver.AddReshape();
        resolver.AddMul();
        resolver.AddAdd();
        resolver.AddMean();
    }

protected:
    std::span<InputType> input;
    std::span<OutputType> output;

private:
    const tflite::Model* model;

    tflite::MicroMutableOpResolver<12> resolver;
    tflite::MicroInterpreter interpreter;

    alignas(16) u8 tensorArena[kTensorArenaSize];
};
