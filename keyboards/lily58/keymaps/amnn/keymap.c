 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H


extern uint8_t is_master;

enum layers {
  _QWERTY,
  _UNSHIFT,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define UNSHIFT TG(_UNSHIFT)
#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX,          XXXXXXX, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
                              KC_LALT, KC_LGUI, LOWER,   KC_SPC,           KC_ENT,  RAISE,   XXXXXXX, XXXXXXX
  ),

  [_UNSHIFT] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
                              _______, _______, _______, _______,          _______, _______, _______, _______
  ),

  [_LOWER] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, KC_LPRN, KC_RPRN, _______, _______,                            KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, KC_BSLS, KC_LABK, KC_RABK, _______, _______, _______,          _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______,
                               _______, _______, _______, _______,          _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT(
    _______, XXXXXXX, KC_0,    KC_0,    KC_0,    XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_PLUS, KC_1,    KC_2,    KC_3,    KC_MINS,                            XXXXXXX, KC_COMM, KC_DOT,  XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_ASTR, KC_4,    KC_5,    KC_6,    KC_SLSH,                            XXXXXXX, KC_A,    KC_B,    KC_C,    XXXXXXX, XXXXXXX,
    _______, KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC, _______,          _______, XXXXXXX, KC_D,    KC_E,    KC_F,    XXXXXXX, _______,
                               _______, _______, _______, _______,          _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
    _______, UNSHIFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                             XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,
                               _______, _______, _______, _______,          _______, _______, _______, _______
  )
};

/* LED Map
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  05  |  04  |  03  |  02  |  01  |  00  |                    |  29  |  30  |  31  |  32  |  33  |  34  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  06  |  07  |  08  |  09  |  10  |  11  |                    |  40  |  39  |  38  |  37  |  36  |  35  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  17  |  16  |  15  |  14  |  13  |  12  |------.      ,------|  41  |  42  |  43  |  44  |  45  |  46  |
 * |------+------+------+------+------+------|  24  |      |  53  |------+------+------+------+------+------|
 * |  18  |  19  |  20  |  21  |  22  |  23  |------|      |------|  52  |  51  |  50  |  49  |  48  |  47  |
 * `-----------------------------------------/      /       \     \-----------------------------------------'
 *                   |  28  |  27  |  26  | /  25  /         \  54 \  |  55  |  56  |  57  |
 *                   `----------------------------'           '------''--------------------'
 */

#define HSV_DIM_WHITE 0,   0,   64
#define HSV_DIM_TEAL  128, 255, 64
#define HSV_DIM_RED   0,   230, 64
#define HSV_DIM_PRED  0,   179, 64
#define HSV_DIM_SPGRN 106, 255, 64
#define HSV_DIM_GREEN 85,  255, 64
#define HSV_DIM_MGNTA 213, 255, 64
#define HSV_DIM_BLUE  170, 255, 64

const rgblight_segment_t PROGMEM rgb_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  5,  HSV_DIM_TEAL},
  {5,  1,  HSV_DIM_RED},
  {6,  23, HSV_DIM_WHITE},
  {29, 5,  HSV_DIM_TEAL},
  {34, 1,  HSV_DIM_RED},
  {35, 23, HSV_DIM_WHITE}
);

const rgblight_segment_t PROGMEM rgb_unshift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  5,  HSV_DIM_SPGRN},
  {29, 5,  HSV_DIM_SPGRN}
);

const rgblight_segment_t PROGMEM rgb_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  5,  HSV_DIM_SPGRN},
  {29, 5,  HSV_DIM_SPGRN},
  {8,  2,  HSV_DIM_MGNTA},
  {13, 1,  HSV_DIM_MGNTA},
  {14, 2,  HSV_DIM_BLUE},
  {16, 1,  HSV_DIM_MGNTA},
  {19, 1,  HSV_DIM_TEAL},
  {20, 2,  HSV_DIM_MGNTA},
  {38, 3,  HSV_DIM_MGNTA},
  {41, 4,  HSV_DIM_BLUE},
  {50, 3,  HSV_DIM_MGNTA}
);

const rgblight_segment_t PROGMEM rgb_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  1,  HSV_OFF},
  {1,  3,  HSV_DIM_GREEN},
  {4,  1,  HSV_OFF},
  {7,  1,  HSV_DIM_TEAL},
  {8,  3,  HSV_DIM_SPGRN},
  {11, 2,  HSV_DIM_TEAL},
  {13, 3,  HSV_DIM_SPGRN},
  {16, 1,  HSV_DIM_TEAL},
  {19, 1,  HSV_DIM_TEAL},
  {20, 3,  HSV_DIM_SPGRN},
  {23, 1,  HSV_DIM_TEAL},
  {29, 5,  HSV_OFF},
  {35, 3,  HSV_OFF},
  {38, 2,  HSV_DIM_TEAL},
  {40, 2,  HSV_OFF},
  {42, 3,  HSV_DIM_SPGRN},
  {45, 2,  HSV_OFF},
  {48, 1,  HSV_OFF},
  {49, 3,  HSV_DIM_SPGRN},
  {52, 1,  HSV_OFF}
);

const rgblight_segment_t PROGMEM rgb_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {0,  4,  HSV_OFF},
  {4,  1,  HSV_DIM_RED},
  {6,  12, HSV_DIM_MGNTA},
  {18, 1,  HSV_DIM_RED},
  {19, 5,  HSV_OFF},
  {29, 13, HSV_OFF},
  {42, 1,  HSV_DIM_BLUE},
  {43, 4,  HSV_OFF},
  {47, 1,  HSV_DIM_RED},
  {48, 5,  HSV_OFF}
);

const rgblight_segment_t PROGMEM rgb_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
  {18, 1,  HSV_DIM_RED},
  {47, 1,  HSV_DIM_RED}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  rgb_qwerty_layer,
  rgb_unshift_layer,
  rgb_lower_layer,
  rgb_raise_layer,
  rgb_adjust_layer,
  rgb_capslock_layer
);

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);

  rgblight_set_layer_state(1, layer_state_cmp(state, _UNSHIFT));
  rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));

  return state;
}

bool led_update_user(led_t led_state) {
  rgblight_set_layer_state(5, led_state.caps_lock);
  return true;
}

void keyboard_post_init_user(void) {
  rgblight_layers = rgb_layers;

  // Default RGB layer -- always on.
  rgblight_set_layer_state(0, true);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_left()) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_0;
  }
}

#    define KEYLOG_LEN 6
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP   && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }

  for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < 60) {
    keylog_str[0] = code_to_name[keycode];
  }

  keylog_str[KEYLOG_LEN - 1] = 0;

  log_timer = timer_read();
}

void update_log(void) {
  if (timer_elapsed(log_timer) > 750) {
    add_keylog(0);
  }
}

void render_keylogger_status(void) {
  oled_write_P(PSTR("KLogr"), false);
  oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
  oled_write_P(PSTR("Layer"), false);
  oled_write_P(PSTR(" "), false);
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("QRTY"), false);
      break;
    case _LOWER:
      oled_write_ln_P(PSTR("LOW"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("HIGH"), false);
      break;
    case _ADJUST:
      oled_write_ln_P(PSTR("ADJ"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undefined"), false);
  }
}

void render_keylock_status(led_t led_state) {
  oled_write_ln_P(PSTR("Lock"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("N"), led_state.num_lock);
  oled_write_P(PSTR("C"), led_state.caps_lock);
  oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
  oled_write_ln_P(PSTR("Mods"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_status_main(void) {
  // Show keyboard layout
  render_default_layer_state();
  // Add a empty line
  oled_write_P(PSTR("-----"), false);
  // Show host keyboard led status
  render_keylock_status(host_keyboard_led_state());
  // Add a empty line
  oled_write_P(PSTR("-----"), false);
  // Show modifier status
  render_mod_status(get_mods());
  // Add a empty line
  oled_write_P(PSTR("-----"), false);
  render_keylogger_status();
}

void oled_task_user(void) {
  update_log();
  if (is_keyboard_left()) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    add_keylog(keycode);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
