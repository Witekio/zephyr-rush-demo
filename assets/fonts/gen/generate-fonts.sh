#!/bin/bash
# @file      generate-fonts.sh
# @brief     Font generation script
#
# Copyright (C) Witekio
#
# This file is part of the Zephyr Rush demonstration.
#
# This demonstration is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This demonstration is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with This demonstration. If not, see <http://www.gnu.org/licenses/>.

set -euo pipefail

BPP=4
SIZES=(16 22 32)
FONTS=(
    "../Gabarito-ExtraBold.ttf|32-255,8226"
    "../Symbols.ttf|59392,59393"
)

OUTPUT_PREFIX="Gabarito"
OUTPUT_DIR="out"

LV_FONT_CONV_BIN="bin/node_modules/.bin/lv_font_conv"

if [ ! -f "$LV_FONT_CONV_BIN" ]; then
    echo "Error: lv_font_conv not found. Run ./install-tools.sh first."
    exit 1
fi

for SIZE in "${SIZES[@]}"; do
    CMD=(
        "$LV_FONT_CONV_BIN"
        --bpp "$BPP"
        --size "$SIZE"
        --no-compress
        --stride 1
        --align 1
    )
    for ENTRY in "${FONTS[@]}"; do
        FONT="${ENTRY%%|*}"
        RANGE="${ENTRY#*|}"
        CMD+=( --font "$FONT" --range "$RANGE" )
    done
    CMD+=(
        --format lvgl
        -o "${OUTPUT_DIR}/${OUTPUT_PREFIX}${SIZE}.c"
    )
    "${CMD[@]}"
done
