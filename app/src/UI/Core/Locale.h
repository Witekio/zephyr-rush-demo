/**
 * @file      Locale.h
 * @brief     Generic Locale abstraction
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

#include "UI/Theme/Translations.h"

class Locale {
public:
    static bool Set(Language language) {
        if (current == language)
            return false;

        current = language;
        return true;
    }

    static Language Get() { return current; }

    template <Translatable Enum>
    static const char* T(Enum key) {
        return TranslationTableFor<Enum>::table[static_cast<u32>(key)][static_cast<u32>(current)];
    }

    template <Translatable Tag>
    static const char* T(u32 index) {
        return TranslationTableFor<Tag>::table[index][static_cast<u32>(current)];
    }

private:
    static inline Language current = Language::EnUs;
};
