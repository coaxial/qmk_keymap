#include QMK_KEYBOARD_H

enum layer_number {
  _CXL = 0,
  _MEDIA,
  _SYMBOLS,
  _MOUSE,
  _NUMPAD,
};

# ifdef OLED_ENABLE
// Customize layer names
static void render_layer_status(void) {
    char buf[10];
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
    case _CXL:
        oled_write_P(PSTR("Coaxial"), false);
        break;
    case _MEDIA:
        oled_write_P(PSTR("Symbols"), false);
        break;
    case _SYMBOLS:
        oled_write_P(PSTR("Media"), false);
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

bool oled_task_user(void) {
#   if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#   endif // DEBUG_TO_SCREEN

  if (is_keyboard_master()) {
    render_status();
  } else {
    render_helix_logo();
    render_rgbled_status(false);
    render_layer_status();
  }

  return false;
}
#endif // OLED_ENABLE
