// Copyright 2021 Christian Eiden, cykedev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H 

#define SPC_L   LSFT_T(KC_SPC)
#define SPC_R   RSFT_T(KC_SPC)
#define ENT_L   LSFT_T(KC_ENT)
#define ENT_R   RSFT_T(KC_ENT)

#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(KC_Y)
#define CUT     LGUI(KC_X)
#define COPY    LGUI(KC_C)
#define PASTE   LGUI(KC_V)
#define ALL     LGUI(KC_A)

#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)

#define LBSPC   LT(_LOWER,KC_BSPC)
#define RBSPC   LT(_RAISE,KC_BSPC)

#define E_CTL   LCTL_T(KC_ESC)

#define TSKMN   LCTL(LSFT(KC_ESC))

enum layer_names {
  _BASE,
  _COLEMAK,
  _RAISE,
  _LOWER,
  _ADJUST,
  _GAME
};

const uint16_t PROGMEM cmswap[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM gswap[] = {KC_B, KC_N, COMBO_END};

/*
// Tap Dance declarations
enum tapdance_names {
    TD_MINS_EQL
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MINS_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
};

#define MINEQ   TD(TD_MINS_EQL)
*/

combo_t key_combos[COMBO_COUNT] = {
    COMBO(cmswap, TG(_COLEMAK)),
    COMBO(gswap, TG(_GAME)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_5x6_5(
   KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
   E_CTL  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                          KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     KC_LGUI, KC_LALT,          KC_SPC , ENT_L , KC_HOME ,      KC_PGUP, ENT_R ,  KC_SPC ,          KC_LBRC, KC_RBRC,
                                                         LBSPC,  KC_END  ,      KC_PGDN, RBSPC
   ),
  [_COLEMAK] = LAYOUT_5x6_5(
   KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
   KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                          KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
   E_CTL  , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                          KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,                                          KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     KC_LGUI, KC_LALT,          KC_SPC , ENT_L , KC_HOME ,      KC_PGUP, ENT_R ,  KC_SPC ,          KC_LBRC, KC_RBRC,
                                                          LOWER, KC_END  ,      KC_PGDN, RAISE
   ), 
  [_RAISE] = LAYOUT_5x6_5(
  /* RAISE
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | Redo |      |      |      |      |                                  |   %  |   $  |  #   |   `  |      |  F12 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | All  | Cut  | Copy | Paste|      |                                  |   ^  |   /  |  *   |   ~  |  ?   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      | Undo |      |      |      |      |                                  |      |   &  |  |   |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               | RST  |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       / Page  /            \  Page \       \
   *                                     /       /  Up   /              \  Down \       \
   *                                    '---------------'                '---------------'
   */
   KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
   _______, REDO   , XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,                                          KC_PERC, KC_DLR , KC_HASH, KC_GRV , KC_EQL , KC_F12 ,
   _______, KC_EXLM, KC_AT  , KC_LPRN, KC_RPRN, XXXXXXX,                                          KC_CIRC, KC_SLSH, KC_ASTR, KC_TILD, KC_QUES, _______,
   _______, UNDO   , XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,                                          XXXXXXX, KC_AMPR, KC_PIPE, _______, _______, _______,
                     QK_BOOT, _______,          _______, _______, _______,      _______, _______, _______,          KC_PLUS, QK_BOOT,
                                                         ADJUST , _______,      TSKMN  , ADJUST   
   ),
  [_LOWER] = LAYOUT_5x6_5(
  /* LOWER
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |  F12 |      |      |   [  |   ]  |      |                                  |      |      |      |  [   |  ]   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |  Ins | play | <<<< | >>>> |  V+  |      |                                  |  up  | left | down | rght |  ?   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      | mute |  V-  |      |                                  |      |      |      |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      | RST  |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       / Page  /            \  Page \       \
   *                                     /       /  Up   /              \  Down \       \
   *                                    '---------------'                '---------------'
   */
   KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
   KC_F12 , REDO   , XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,                                          XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,
   KC_INS , KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLU, KC_TRNS,                                          KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_QUES, XXXXXXX,
   _______, UNDO   , XXXXXXX, KC_MUTE, KC_VOLD, XXXXXXX,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                     XXXXXXX, _______,          _______, _______, _______,      _______, _______, _______,          KC_PLUS, QK_BOOT,
                                                         _______, TSKMN  ,      _______, ADJUST
   ),
  [_ADJUST] = LAYOUT_5x6_5(
  /* ADJUST
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |      |      |      |      | QWERT|                                  |COLEM |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |  V+  |                                  |  B + |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |  V-  |                                  |  B - |  <<  | play |  >>  |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      | Mute |                                  |      |      |      |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       /       /            \       \       \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   QK_BOOT, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , QK_BOOT,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                          XXXXXXX, XXXXXXX, XXXXXXX, KC_F11 , KC_F12 , XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX,                                          _______, _______, _______, _______, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, XXXXXXX,                                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     QK_BOOT, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, QK_BOOT,
                                                         XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX
   ),
   [_GAME] = LAYOUT_5x6_5(
   KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
   KC_TAB , KC_T   , KC_Q   , KC_W   , KC_E   , KC_R   ,                                          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
   KC_LCTL, KC_G   , KC_A   , KC_S   , KC_D   , KC_F   ,                                          KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
   KC_LSFT, KC_B   , KC_Z   , KC_X   , KC_C   , KC_V   ,                                          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     KC_LGUI, KC_LALT,          KC_SPC , KC_ENT, KC_HOME ,      KC_PGUP, KC_ENT , KC_SPC ,          KC_LBRC, KC_RBRC,
                                                          LOWER, KC_END  ,      KC_PGDN, RAISE
   )
};
