/**
 * @file      FS.h
 * @brief     Generic platform file system header
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

#include <array>
#include <cassert>
#include <type_traits>

#include "Core/Base.h"

namespace Platform {
    namespace FS {
        enum class Result : u8 {
            Ok,
            FileNotFound,
            ReadError,
            WriteError,
            FileSystemNotMounted,
        };

        namespace Detail {
            Result Store(const char* filename, const void* data, u32 size) noexcept;
            Result Load(const char* filename, void* out, u32 size) noexcept;
        } // namespace Detail

        void Init();

        template <u32 N>
        struct Path {
            static constexpr char kPrefix[] = "/SD:/";
            std::array<char, sizeof(kPrefix) - 1 + N> value{};

            constexpr explicit Path(const char (&name)[N]) {
                static_assert(N - 1 < 12, "Path must respect the 8.3 rule");

                u32 i = 0;
                for (; i < sizeof(kPrefix) - 1; ++i)
                    value[i] = kPrefix[i];

                for (u32 j = 0; j < N; ++j, ++i)
                    value[i] = name[j];
            }

            constexpr const char* c_str() const noexcept { return value.data(); }
        };

        template <u32 N>
        constexpr auto MakePath(const char (&name)[N]) {
            return Path<N>{name};
        }

        template <typename T, u32 N>
            requires std::is_trivially_copyable_v<T>
        Result Store(const Path<N>& path, const T& value) noexcept {
            return Detail::Store(path.c_str(), &value, sizeof(T));
        }

        template <typename T, u32 N>
            requires std::is_trivially_copyable_v<T>
        Result Load(const Path<N>& path, T& out) noexcept {
            return Detail::Load(path.c_str(), &out, sizeof(T));
        }

    }; // namespace FS
} // namespace Platform
