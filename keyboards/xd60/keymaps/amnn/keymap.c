#include "xd60.h"
#include "action_layer.h"
#include "rgblight.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  KEYMAP(
    KC_ESC,        KC_1,    KC_2,    KC_3,    KC_4,   KC_5,  KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_NO, \
    KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,  KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, \
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,   KC_G,  KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_NO,            KC_ENT, \
    KC_LSFT,       KC_GRV,  KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_VOLD, F(1),    KC_VOLU, \
    F(0),          KC_LALT, KC_LGUI,                          KC_SPC,                          KC_RGUI, F(0),    KC_MRWD, KC_MPLY, KC_MFFD),

  // 1: Function Layer
  KEYMAP(
    LCTL(LSFT(KC_PWR)),
             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS, \
    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_MUTE, KC_TRNS, KC_TRNS, \
    F(0),    KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, F(0),     KC_TRNS, KC_TRNS, KC_TRNS),

  // 2: Function Layer
  KEYMAP(
    KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,          KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, F(1),    KC_TRNS, \
    F(0),    KC_TRNS, KC_TRNS,                              KC_TRNS,                             KC_TRNS, F(0),     BL_DEC,  RGB_TOG, BL_INC),
};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
  [1] = ACTION_LAYER_MOMENTARY(2),  // to Fn overlay
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t sHue = 0;
  switch (keycode) {
    case F(0):
    case F(1):
      sHue += record->event.pressed ? 100 : 25;
      sHue %= 360;
      rgblight_sethsv(sHue, 172, 172);
      break;
  }

  return true;
}

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
