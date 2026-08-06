# Font Embeddings Generator

Scripts to embed TTF fonts into LVGL-compatible `.c` files.

## Prerequisites

You need **Node.js and npm** installed on your machine.

- Download from [nodejs.org](https://nodejs.org) (npm is bundled with Node.js)
- Verify your installation: `node -v && npm -v`

## Scripts

### `install-tools.sh` - One-time setup

Downloads and installs `lv_font_conv` locally into the `bin/` folder.

```bash
./install-tools.sh
```

Only needs to be run once. If the tool is already installed it will skip silently.

### `generate-fonts.sh` - Generate the fonts

Converts the TTF fonts into LVGL `.c` files with different parameters.

```bash
./generate-fonts.sh
```

Output files are written to `out/`.
