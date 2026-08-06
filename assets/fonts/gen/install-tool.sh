#!/bin/bash
# @file      install-tool.sh
# @brief     Font generation tools install script
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

OUTPUT_DIR="bin"
LV_FONT_CONV_REF="github:lvgl/lv_font_conv#626bd649f3b8534999d7eb03597ae183cc7022f5"
LV_FONT_CONV_BIN="$OUTPUT_DIR/node_modules/.bin/lv_font_conv"

if [ -f "$LV_FONT_CONV_BIN" ]; then
    echo "lv_font_conv already installed, skipping."
    exit 0
fi

echo "Installing lv_font_conv into $OUTPUT_DIR..."
npm install --prefix "$OUTPUT_DIR" "$LV_FONT_CONV_REF"
echo "Done."
