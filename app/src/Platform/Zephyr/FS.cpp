/**
 * @file      FS.cpp
 * @brief     Zephyr file system implementation
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

#include "FS.h"

#include <ff.h>
#include <zephyr/fs/fs.h>

using namespace Platform;

namespace {
    bool mounted = false;
}

void FS::Init() {
    static FATFS fatfs;
    static struct fs_mount_t mp = {
        .type = FS_FATFS,
        .mnt_point = "/SD:",
        .fs_data = &fatfs,
        .storage_dev = (void*)"SD",
    };
    mounted = fs_mount(&mp) >= 0;
}

FS::Result FS::Detail::Load(const char* filename, void* out, u32 size) noexcept {
    if (!mounted)
        return Result::FileSystemNotMounted;

    fs_file_t file;
    fs_file_t_init(&file);

    if (fs_open(&file, filename, FS_O_READ) < 0)
        return Result::FileNotFound;

    i32 n = fs_read(&file, out, size);
    fs_close(&file);

    if (n < 0)
        return Result::ReadError;

    if (static_cast<u32>(n) != size)
        return Result::ReadError;

    return Result::Ok;
}

FS::Result FS::Detail::Store(const char* filename, const void* data, u32 size) noexcept {
    if (!mounted)
        return Result::FileSystemNotMounted;

    fs_file_t file;
    fs_file_t_init(&file);

    if (fs_open(&file, filename, FS_O_CREATE | FS_O_WRITE) < 0)
        return Result::WriteError;

    i32 n = fs_write(&file, data, size);
    fs_close(&file);

    if (n < 0)
        return Result::WriteError;

    if (static_cast<u32>(n) != size)
        return Result::WriteError;

    return Result::Ok;
}
