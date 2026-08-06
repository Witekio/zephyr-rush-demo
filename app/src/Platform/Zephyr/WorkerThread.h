/**
 * @file      WorkerThread.h
 * @brief     Zephyr worker thread abstraction
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

#include <zephyr/kernel.h>

#define WORKER_THREAD_PRIORITY K_LOWEST_APPLICATION_THREAD_PRIO
#define WORKER_STACK_SIZE 16384

/*
 * @brief Reusable asynchronous task.
 *
 * The task ID can be used by callers to version or identify task instances,
 * since task objects are intended to be reused.
 *
 * The worker thread clears the ready flag before execution and sets it once
 * execution completes. A task is considered running while Ready() returns
 * false.
 */
class Task {
    friend class WorkerThread;

public:
    using TaskID = u32;

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task() = default;

    virtual ~Task() = default;
    virtual void Run() = 0;

    bool Ready() const { return static_cast<bool>(atomic_get(&ready)); }

    void SetID(TaskID id) { this->id = id; }

    TaskID ID() const { return id; }

private:
    TaskID id = 0;
    atomic_t ready = ATOMIC_INIT(1);
};

class MutexLock {
public:
    explicit MutexLock(k_mutex& mutex) : m(mutex) { k_mutex_lock(&m, K_FOREVER); }

    ~MutexLock() { k_mutex_unlock(&m); }

    MutexLock(const MutexLock&) = delete;
    MutexLock& operator=(const MutexLock&) = delete;

private:
    k_mutex& m;
};

/*
 * @brief Single-threaded asynchronous task executor (singleton).
 *
 * Executes Task instances on a dedicated worker thread. Only one task can be
 * queued or running at a time; Submit() fails if the worker is busy.
 *
 * The caller is responsible for handling task submission failures.
 *
 * Platform-specific implementations are provided for Zephyr and desktop
 * targets. The desktop implementation supports graceful shutdown, while the
 * Zephyr worker runs for the lifetime of the application.
 */
class WorkerThread {
public:
    enum class State : u8 { Idle, Busy };

    static WorkerThread& Get() {
        static WorkerThread instance;
        return instance;
    }

    WorkerThread(const WorkerThread&) = delete;
    WorkerThread& operator=(const WorkerThread&) = delete;

    bool Submit(Task& task) {
        {
            MutexLock lck(m);

            if (state != State::Idle)
                return false;

            currentTask = &task;
            atomic_set(&currentTask->ready, 0);
            state = State::Busy;
        }

        k_sem_give(&sem);
        return true;
    }

    bool Busy() {
        MutexLock lck(m);
        return state == State::Busy;
    }

private:
    WorkerThread() {
        k_sem_init(&sem, 0, 1);
        k_mutex_init(&m);

        auto ThreadEntry = [](void* arg0, void* /* arg1 */, void* /* arg2 */) {
            auto* self = static_cast<WorkerThread*>(arg0);
            while (true) {
                k_sem_take(&self->sem, K_FOREVER);
                self->DoTask();
            }
        };

        k_thread_create(&thread, stack, K_THREAD_STACK_SIZEOF(stack), ThreadEntry, this, nullptr, nullptr,
                        WORKER_THREAD_PRIORITY, 0, K_NO_WAIT);
    }

    void DoTask() {
        currentTask->Run();

        {
            MutexLock lck(m);
            atomic_set(&currentTask->ready, 1);
            currentTask = nullptr;
            state = State::Idle;
        }
    }

private:
    Task* currentTask = nullptr;

    State state = State::Idle;
    k_sem sem;
    k_mutex m;

    K_KERNEL_STACK_MEMBER(stack, WORKER_STACK_SIZE);
    k_thread thread;
};
