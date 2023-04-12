# ifdef OLED_ENABLE
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

void render_status(void) {
  // Render to mode icon
    static const char os_logo[][2][3] PROGMEM = {
      {
        {0x95,0x96,0}, {0xb5,0xb6,0},
      },
      {
        {0x97,0x98,0}, {0xb7,0xb8,0},
      }
    };
    if (is_mac_mode()) {
        oled_write_P(os_logo[0][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[0][1], false);
    } else {
        oled_write_P(os_logo[1][0], false);
        oled_write_P(PSTR("\n"), false);
        oled_write_P(os_logo[1][1], false);
    }

    oled_write_P(PSTR(" "), false);
    render_layer_status();

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLOCK") : PSTR("       "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCLK") : PSTR("    "), false);
    oled_advance_page(true);
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
    render_layer_status();
  }

  return false;
}
#endif // OLED_ENABLE
