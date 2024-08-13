// Copyright 2023 Danny Nguyen (@nooges)
// Copyright 2024 Ashok Menon (@amnn)
// SPDX-License-Identifier: GPL-2.0-or-later

// @amnn's personal layout, derived from the Iris CE default layout, features:
//
// - "Pre-shifted" number row. Number row on the base layer is bound to the
//   shifted versions of the equivalent numeric key, and the normal number keys
//   are available on the first layer.
//
// - Symmetrical brackets: Paired characters (parens, braces, brackets, angles)
//   are available around the left home row on the first layer, arranged
//   symmetrically around the middle of the keyboard (the closing character is
//   the same distance to the right of center as the opening is to the left).
//
// - ISO-layout grave key (next to left shift).
//
// - VIM arrows (h/j/k/l).
//
// - Number pad on second layer. With facilities for typing operators on either
//   side of the numeric keys, and a way to input hexadecimal digits.
//
// - "Adjustment" layer -- holding both layer keys enables an adjustment layer
//   that toggles various sticky properties:
//   - "Pre-shifted" numbers can be toggled on/off.
//   - Shift keys become caps lock keys.
//
// RGB backlighting is used to indicate when a keycode has changed.

#include "info_config.h"
#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY = 0,
    _UNSFT  = 1,
    _LOWER  = 2,
    _RAISE  = 3,
    _ADJUST = 4,
};

enum backlight_kind {
    LDXXXXX = 0,    // Turn backlight off
    LD_ABC  = 1,    // Alphabetic keys
    LD_NUM,         // Numeric keys
    LD_OP,          // Operator keys
    LD_SHIFT,       // Shift keys (special because of caps lock handling)
    LD_MOD,         // Modifier keys
    LD_WARN,        // Things to flag as warnings (e.g. potentially destructive)
    LD_NAV,         // Navigation keys, e.g. arrows
    LD_FN,          // Function keys
    LD_RGB,         // RGB toggle
    LD_BACK = 0xFE, // Backlight
    LD_____ = 0xFF, // Transparent
};

#define UNSFT TG(_UNSFT)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

// clang-format off
#define QWERTY_LAYER(F) F(                                                                                                        \
    LD_WARN, LD_OP  , LD_OP  , LD_OP  , LD_OP  , LD_OP  ,                   LD_OP  , LD_OP  , LD_OP  , LD_OP  , LD_OP  , LD_WARN, \
    KC_ESC , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL , KC_BSPC, \
                                                                                                                                  \
    LD_NAV , LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_ABC ,                   LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_OP  , \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_SLSH, \
                                                                                                                                  \
    LD_MOD , LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_ABC ,                   LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_OP  , LD_OP  , \
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
                                                                                                                                  \
    LD_MOD , LD_OP  , LD_ABC , LD_ABC , LD_ABC , LD_ABC , LD_NAV , LD_NAV , LD_ABC , LD_ABC , LD_ABC , LD_OP  , LD_OP  , LD_MOD , \
    KC_LSFT, KC_GRV , KC_Z   , KC_X   , KC_C   , KC_V   , KC_SPC , KC_ENT , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_RSFT, \
                                                                                                                                  \
                                       LD_MOD  , LD_FN  , LD_NAV , LD_NAV , LD_FN  , LD_MOD ,                                     \
                                       KC_LGUI , LOWER  , KC_SPC , KC_ENT , RAISE  , KC_RALT                                      \
)

#define UNSFT_LAYER(F) F(                                                                                                         \
    LD_____, LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_NUM ,                   LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_____, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, \
                                                                                                                                  \
    LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                   LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
                                                                                                                                  \
    LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                   LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
                                                                                                                                  \
    LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, LD_____, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                                                                                                  \
                                        LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                                     \
                                        _______, _______, _______, _______, _______, _______                                      \
)

#define LOWER_LAYER(F) F(                                                                                                         \
    LD_____, LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_NUM ,                   LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_NUM , LD_____, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______, \
                                                                                                                                  \
    LD_____, LD_____, LD_OP  , LD_OP  , LD_____, LD_____,                   LD_FN  , LD_FN  , LD_FN  , LD_____, LD_____, LD_____, \
    _______, _______, KC_LPRN, KC_RPRN, _______, _______,                   KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, \
                                                                                                                                  \
    LD_____, LD_OP  , LD_OP  , LD_OP  , LD_OP  , LD_____,                   LD_NAV , LD_NAV , LD_NAV , LD_NAV , LD_____, LD_____, \
    _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______,                   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
                                                                                                                                  \
    LD_____, LD_OP  , LD_OP  , LD_OP  , LD_____, LD_____, LD_____, LD_____, LD_FN  , LD_FN  , LD_FN  , LD_____, LD_____, LD_____, \
    _______, KC_BSLS, KC_LABK, KC_RABK, _______, _______, _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______, _______, _______, \
                                                                                                                                  \
                                        LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                                     \
                                        _______, _______, _______, _______, _______, _______                                      \
)

#define RAISE_LAYER(F) F(                                                                                                         \
    LD_____, LDXXXXX, LD_NUM , LD_NUM , LD_NUM , LDXXXXX,                   LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LD_____, \
    _______, XXXXXXX, KC_0   , KC_0   , KC_0   , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
                                                                                                                                  \
    LD_____, LD_OP  , LD_NUM , LD_NUM , LD_NUM , LD_OP  ,                   LDXXXXX, LD_OP  , LD_OP  , LDXXXXX, LDXXXXX, LDXXXXX, \
    _______, KC_PLUS, KC_1   , KC_2   , KC_3   , KC_MINS,                   XXXXXXX, KC_COMM, KC_DOT , XXXXXXX, XXXXXXX, XXXXXXX, \
                                                                                                                                  \
    LD_____, LD_OP  , LD_NUM , LD_NUM , LD_NUM , LD_OP  ,                   LDXXXXX, LD_NUM , LD_NUM , LD_NUM , LDXXXXX, LDXXXXX, \
    _______, KC_ASTR, KC_4   , KC_5   , KC_6   , KC_SLSH,                   XXXXXXX, KC_A   , KC_B   , KC_C   , XXXXXXX, XXXXXXX, \
                                                                                                                                  \
    LD_____, LD_OP  , LD_NUM , LD_NUM , LD_NUM , LD_OP  , LD_____, LD_____, LDXXXXX, LD_NUM , LD_NUM , LD_NUM , LDXXXXX, LDXXXXX, \
    _______, KC_CIRC, KC_7   , KC_8   , KC_9   , KC_PERC, _______, _______, XXXXXXX, KC_D   , KC_E   , KC_F   , XXXXXXX, _______, \
                                                                                                                                  \
                                        LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                                     \
                                        _______, _______, _______, _______, _______, _______                                      \
)

#define ADJUST_LAYER(F) F(                                                                                                        \
    LD_____, LD_NUM , LD_FN  , LD_FN  , LD_FN  , LDXXXXX,                   LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, \
    _______, UNSFT  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                                                                                                                  \
    LD_____, LDXXXXX, LD_FN  , LD_FN  , LD_FN  , LDXXXXX,                   LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, \
    _______, XXXXXXX, KC_F1  , KC_F2  , KC_F3  , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                                                                                                                  \
    LD_____, LDXXXXX, LD_FN  , LD_FN  , LD_FN  , LDXXXXX,                   LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, \
    _______, XXXXXXX, KC_F4  , KC_F5  , KC_F6  , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                                                                                                                  \
    LD_____, LDXXXXX, LD_FN  , LD_FN  , LD_FN  , LDXXXXX, LD_RGB , LD_RGB , LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LDXXXXX, LD_WARN, \
    _______, XXXXXXX, KC_F7  , KC_F8  , KC_F9  , XXXXXXX, RGB_TOG, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, \
                                                                                                                                  \
                                        LD_____, LD_____, LD_____, LD_____, LD_____, LD_____,                                     \
                                        _______, _______, _______, _______, _______, _______                                      \
)

#define KEYS(                                                             \
    L00, L01, L02, L03, L04, L05,           L06, L07, L08, L09, L0A, L0B, \
    K00, K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, K0B, \
    L10, L11, L12, L13, L14, L15,           L16, L17, L18, L19, L1A, L1B, \
    K10, K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, K1B, \
    L20, L21, L22, L23, L24, L25,           L26, L27, L28, L29, L2A, L2B, \
    K20, K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A, K2B, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B, L3C, L3D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
                        L40, L41, L42, L43, L44, L45,                     \
                        K40, K41, K42, K43, K44, K45                      \
) LAYOUT(                                                                 \
    K00, K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A, K2B, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
                        K40, K41, K42, K43, K44, K45                      \
)

// Maps LED Index to its backlight code. This mapping is hard coded to follow
// the Iris CE layout and RGB matrix configuration. The `LAYOUT` maps matrix
// row and column to positions, and `g_led_config` maps matrix row and column
// to LED indices. This macro combines both to map LED indices to their
// positions.
#define BACKLIGHT(                                                        \
    L00, L01, L02, L03, L04, L05,           L06, L07, L08, L09, L0A, L0B, \
    K00, K01, K02, K03, K04, K05,           K06, K07, K08, K09, K0A, K0B, \
    L10, L11, L12, L13, L14, L15,           L16, L17, L18, L19, L1A, L1B, \
    K10, K11, K12, K13, K14, K15,           K16, K17, K18, K19, K1A, K1B, \
    L20, L21, L22, L23, L24, L25,           L26, L27, L28, L29, L2A, L2B, \
    K20, K21, K22, K23, K24, K25,           K26, K27, K28, K29, K2A, K2B, \
    L30, L31, L32, L33, L34, L35, L36, L37, L38, L39, L3A, L3B, L3C, L3D, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, \
                        L40, L41, L42, L43, L44, L45,                     \
                        K40, K41, K42, K43, K44, K45                      \
) {                                                                       \
    L00    , LD_BACK, L01    , L02    , LD_BACK, L03    , L04    , LD_BACK, L05    , L15    , L14    , L13    , L12    , L11    , L10    , L20    , L21    , \
    L22    , L23    , L24    , L25    , L35    , L34    , L33    , L32    , L31    , L30    , LD_BACK, LD_BACK, L40    , L41    , LD_BACK, L42    , L36    , \
    L0B    , LD_BACK, L0A    , L09    , LD_BACK, L08    , L07    , LD_BACK, L06    , L16    , L17    , L18    , L19    , L1A    , L1B    , L2B    , L2A    , \
    L29    , L28    , L27    , L26    , L38    , L39    , L3A    , L3B    , L3C    , L3D    , LD_BACK, LD_BACK, L45    , L44    , LD_BACK, L43    , L37    , \
}

#define HSV_THEME_OFF      0,   0,   0
#define HSV_THEME_DBLUE  196, 255,  64
#define HSV_THEME_BLUE   148, 255,  64
#define HSV_THEME_GREEN   80, 255,  64
#define HSV_THEME_ORANGE  10, 255,  64
#define HSV_THEME_RED      0, 255,  64
#define HSV_THEME_WHITE    0,   0,  64

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = QWERTY_LAYER(KEYS),
  [_UNSFT]  = UNSFT_LAYER(KEYS),
  [_LOWER]  = LOWER_LAYER(KEYS),
  [_RAISE]  = RAISE_LAYER(KEYS),
  [_ADJUST] = ADJUST_LAYER(KEYS),
};

const uint8_t PROGMEM backlights[][RGB_MATRIX_LED_COUNT] = {
  [_QWERTY] = QWERTY_LAYER(BACKLIGHT),
  [_UNSFT]  = UNSFT_LAYER(BACKLIGHT),
  [_LOWER]  = LOWER_LAYER(BACKLIGHT),
  [_RAISE]  = RAISE_LAYER(BACKLIGHT),
  [_ADJUST] = ADJUST_LAYER(BACKLIGHT),
};

// clang-format on
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
}

void keyboard_post_init_user(void) {
    rgb_matrix_sethsv_noeeprom(HSV_THEME_WHITE);
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

void set_hsv(uint8_t led, uint8_t h, uint8_t s, uint8_t v) {
    RGB rgb = hsv_to_rgb((HSV){h, s, v});
    rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; ++i) {
        enum backlight_kind kind;

        uint8_t layer = get_highest_layer(layer_state);
        while ((kind = backlights[layer][i]) == LD_____ && layer > 0)
            --layer;

        switch (kind) {
            case LD_____:
            case LDXXXXX:
                set_hsv(i, HSV_THEME_OFF);
                break;
            case LD_ABC:
            case LD_BACK:
                set_hsv(i, HSV_THEME_WHITE);
                break;
            case LD_NUM:
                set_hsv(i, HSV_THEME_BLUE);
                break;
            case LD_OP:
                set_hsv(i, HSV_THEME_DBLUE);
                break;
            case LD_SHIFT:
                if (host_keyboard_led_state().caps_lock) {
                    set_hsv(i, HSV_THEME_RED);
                    break;
                }
                /* fallthrough */
            case LD_FN:
            case LD_MOD:
                set_hsv(i, HSV_THEME_ORANGE);
                break;
            case LD_WARN:
                set_hsv(i, HSV_THEME_RED);
                break;
            case LD_NAV:
                set_hsv(i, HSV_THEME_GREEN);
                break;
            case LD_RGB:
                set_hsv(i, (timer_read() / 16) % 255, 255, 64);
                break;
        }
    }

    return true;
}
