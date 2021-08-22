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
#include "pimoroni_trackball.h"


extern uint8_t is_master;

enum layers {
  _QWERTY,
  _UNSHIFT,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
    TB_BTN1 = SAFE_RANGE,
    TB_BTN2,
    TB_SCRL,
};

#define UNSHIFT TG(_UNSHIFT)
#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    TB_BTN1,          XXXXXXX, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
                               KC_LALT, KC_LGUI, LOWER,   KC_SPC,           KC_ENT,  RAISE,   TB_BTN2, TB_SCRL
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

  trackball_set_precision(1.5);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case TB_BTN1:
      trackball_register_button(record->event.pressed, MOUSE_BTN1);
      return false;
    case TB_BTN2:
      trackball_register_button(record->event.pressed, MOUSE_BTN2);
      return false;
    case TB_SCRL:
      trackball_set_scrolling(record->event.pressed);
      return false;
    default:
      return true;
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_0;
}

void render_lily58_logo(void) {
  static const char PROGMEM lily58_logo[] = {
    // 'logo', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x40, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x80, 0xe0, 0x70, 0x3c, 0x0e, 0x06, 0x0e, 0x3c, 0x70, 0xe0, 0x80, 0x00, 0x00, 0xc0, 0xc0, 0x00,
    0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x80,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83,
    0x07, 0x07, 0x0c, 0x18, 0x70, 0xe0, 0x80, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x80, 0xb6, 0xb6, 0x80,
    0xb0, 0xb0, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf1, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf0,
    0x30, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xe1, 0x71, 0x71, 0xf1, 0xf1, 0xe1, 0xc1, 0x81, 0x00, 0x00,
    0x00, 0x00, 0x0c, 0x3f, 0xff, 0xf3, 0xe1, 0xc1, 0xc1, 0x81, 0x81, 0xc3, 0xff, 0x7f, 0x1c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x70, 0x78, 0xdc, 0xcc, 0x86, 0x06, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x03, 0x02, 0x06, 0x84, 0xe1, 0xfb, 0x38, 0x1c, 0x0c, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x03, 0x03, 0x06, 0x86, 0xcc, 0xdc, 0x78, 0x70, 0x20, 0x00, 0xff, 0xff, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7e, 0xf8, 0xe0, 0xf0, 0x7e, 0x1f, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xe1, 0xff, 0x7f, 0x3f, 0x00,
    0x00, 0x00, 0x3e, 0xff, 0xff, 0xc1, 0xc0, 0x80, 0x81, 0x81, 0xc3, 0xc3, 0xff, 0xfe, 0x3c, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06,
    0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04,
    0x06, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x01, 0x00, 0x00, 0x60, 0x60, 0x70, 0x38, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00
  };

  oled_write_raw_P(lily58_logo, sizeof(lily58_logo));
}


void oled_task_user(void) {
  if (!is_keyboard_master()) {
    render_lily58_logo();
  }
}
#endif // OLED_DRIVER_ENABLE
