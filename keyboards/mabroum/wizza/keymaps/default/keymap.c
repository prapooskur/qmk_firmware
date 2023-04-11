// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_23332(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                     KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                     KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,                                       KC_U,   KC_O,     KC_Y,
                                  KC_0, KC_SPACE,                   OSM(MOD_LSFT), KC_1,
                                  KC_BTN3, KC_BTN1, KC_BTN2,          KC_BTN3, KC_BTN1, KC_BTN2,
                                     KC_1 , KC_2, KC_3, KC_4, KC_5,
                                     KC_1 , KC_2, KC_3, KC_4, KC_5

    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
