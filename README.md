# Witekio Rush

## About

Witekio-Rush is a demo application developed by Witekio to showcase the capabilities of modern MCU-based platforms.

Built with Zephyr RTOS, LVGL, and TensorFlow Lite for Microcontrollers, it demonstrates how rich graphics, responsive user interfaces, and embedded AI can be combined within the constraints of embedded devices.

The project targets the NXP MIMXRT1064-EVK board with the NXP RK043FN66HS-CTG parallel display.

## Setup

> **Note:** `west init -l .` treats this repository as the manifest repo, which means West will create `zephyr/`, `modules/`, `bootloader/`, and other supporting folders as **siblings** of this repo (i.e. in its parent directory), not inside it. Make sure this repo lives in its own dedicated parent folder (e.g. `rush-workspace/rush/`) before running setup, so these folders don't end up mixed in with unrelated files.

Install West and configure Zephyr:

```bash
python3 -m venv venv
source venv/bin/activate
pip install west

west init -l .
west update
west zephyr-export
west packages pip --install
west sdk install
```

If you plan to build the native simulator, the simulator requires a windowing backend (SDL2).

On Ubuntu, you can install it with:

```bash
sudo apt install libsdl2-dev
```

## Build

Create and build the projects (only needed once):

```bash
west build app --build-dir build/mimxrt1064 -b mimxrt1064_evk --shield rk043fn66hs_ctg
```

```bash
west build app --build-dir build/native -b native_sim/native/64
```

## Rebuild / Run

**MIMXRT1064 board:**

```bash
west build --build-dir build/mimxrt1064
west flash --build-dir build/mimxrt1064
```

**Native simulator:**

```bash
west build --build-dir build/native -t run
```

## License

This project is licensed under the GNU General Public License v3.0. See the `LICENSE` file for details.

### Attribution

This project uses the Quick, Draw! Dataset made available by Google, Inc. 
under the Creative Commons Attribution 4.0 International license.
https://creativecommons.org/licenses/by/4.0/

This project uses the Gabarito font, which is licensed under the SIL Open Font License 1.1.
The font license is available in `assets/fonts/OFL.txt`.
