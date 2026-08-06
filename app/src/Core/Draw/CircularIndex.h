/**
 * @file      CircularIndex.h
 * @brief     Generic circular index implementation
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

#include "Core/Base.h"

template <u32 MaxSize>
class CircularIndex {
public:
    CircularIndex() = default;

    u32 Push() {
        u32 idx = head;
        head = (head + 1) % MaxSize;
        if (size < MaxSize)
            size++;
        else
            tail = (tail + 1) % MaxSize;
        return idx;
    }

    u32 Pop() {
        assert(CanPop());
        head = (head == 0) ? MaxSize - 1 : head - 1;
        size--;
        return head;
    }

    void Reset() {
        head = 0;
        tail = 0;
        size = 0;
    }

    u32 Nth(u32 idx) const {
        assert(idx < size);
        return (tail + idx) % MaxSize;
    }

    u32 Top() const {
        assert(size > 0);
        return (head == 0) ? MaxSize - 1 : head - 1;
    }

    u32 Size() const { return size; }

    bool Empty() const { return size == 0; }

    bool CanPop() const { return size > 0; }

private:
    u32 head = 0;
    u32 tail = 0;
    u32 size = 0;
};
