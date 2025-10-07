#include QMK_KEYBOARD_H
#include <stdio.h>

#ifdef OLED_ENABLE
enum layer_number {
  _CXL = 0,
  _MEDIA,
  _SYMBOLS,
  _MOUSE,
  _NUMPAD,
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_0;
  } else {
    return OLED_ROTATION_180;
  }
}

// Customize layer names
static void render_layer_status(void) {
  char buf[10];
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
  case _CXL:
    oled_write_P(PSTR("Coaxial"), false);
    break;
  case _MEDIA:
    oled_write_P(PSTR("Media"), false);
    break;
  case _SYMBOLS:
    oled_write_P(PSTR("Symbols"), false);
    break;
  case _MOUSE:
    oled_write_P(PSTR("Mouse"), false);
    break;
  case _NUMPAD:
    oled_write_P(PSTR("Numpad"), false);
    break;
  default:
    oled_write_P(PSTR("Undef-"), false);
    snprintf(buf, sizeof(buf), "%u", layer_state);
    oled_write(buf, false);
  }

  oled_write_P(PSTR("\n"), false);
}

void render_status(void) {
  render_layer_status();

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUMLOCK") : PSTR("       "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCLK") : PSTR("    "), false);
  oled_advance_page(true);
  oled_write_P(PSTR("\n"), false);
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
      // clang-format off
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
      // clang-format on
  };
  oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif // DEBUG_TO_SCREEN

  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    render_layer_status();
  }

  return false;
}
#endif // OLED_ENABLE
