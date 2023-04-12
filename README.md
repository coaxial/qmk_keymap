# Custom firmware for my QMK keyboard

This is my custom keymaps using the [userspace](https://docs.qmk.fm/#/feature_userspace) feature from QMK.

## Modifying layout

1. Load `coaxial.json` into [QMK
   Configurator](https://config.qmk.fm/) (or select load from URL with `https://raw.githubusercontent.com/coaxial/qmk_keymap/master/coaxial.json`)
2. Edit keys
3. Download updated json file and overwrite `coaxial.json` in the repo
4. Commit using a [semantic-commit message](https://github.com/angular/angular/blob/main/CONTRIBUTING.md#-commit-message-format) via PR
4. Merge PR

## Flashing new firmware on keyboard

1. Setup the [QMK CLI](https://docs.qmk.fm/#/newbs_getting_started?id=set-up-your-environment)
2. Download latest firmware file from the [releases page](https://github.com/coaxial/qmk_keymap/releases)
3. Flash with `qmk flash <path/to/firmware>` (must be run within `qmk_firmware` repo)

> ⚠️ For split keyboards, both sides must be flashed individually.
