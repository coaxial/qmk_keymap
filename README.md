# Custom firmware for my QMK keyboard

This is my custom keymaps using the [userspace](https://docs.qmk.fm/#/feature_userspace) feature from QMK.

## Modifying layout

1. Load `coaxial.json` into [QMK
   Configurator](https://config.qmk.fm/#/ryanbaekr/rb18/LAYOUT_numpad_5x4), select
   Helix rev2 as the board, and edit keys.
2. Download json file and overwrite `coaxial.json` in the repo
3. Commit using a semantic-commit via PR
4. Merge PR

## Flashing new firmware on keyboard

1. Setup the [QMK CLI](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment)
2. download latest firmware file from the [releases page](https://github.com/coaxial/qmk_keymap/releases)
3. Flash with `qmk flash <path/to/firmware>` (must be run within `qmk_firmware` repo)

> For split keyboards, both sides must be flashed individually.
