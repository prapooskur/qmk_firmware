#include "repeat.h"
#include "nshot_mod.h"
#include "swapper.h"
#include "keyboards/mabroum/mab_haptic.h"
#include "keyboards/mabroum/mab_pointing.h"
#include "keyboards/mabroum/keys.h"
#include "lvgl.h"
#include "display.h"


enum layers {
    HDN = 0,
    CMK,
    NAV,
    SYM,
    ADJ,
};

// pointing
#define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
#define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE
#define ACCEL_TOG ACCELERATION_TOGGLE

// global
#define SCRNSHT     C(A(S(KC_P)))
#define WRKFLW1     A(C(S(G(KC_K))))
#define WRKFLW2     A(C(S(G(KC_Y))))
#define RCRD        A(KC_F10)

// layers
#define MO_NAV MO(NAV)
#define MO_SYM MO(SYM)
#define MO_ADJ MO(ADJ)

// mac
#define PSTM         G(KC_V)
#define CPYM         G(KC_C)
#define CUTM         G(KC_X)
#define SALLM        G(KC_A)
#define DWRDM        A(KC_BSPC)
#define QUITM        G(KC_Q)
#define SAVEM        G(KC_S)

//windows
#define PSTW         C(KC_V)
#define CPYW         C(KC_C)
#define CUTW         C(KC_X)
#define SALLW        C(KC_A)
#define DWRDW        C(KC_BSPC)
#define QUITW        A(KC_F4)
#define SAVEW        C(KC_S)

#define UNDOMAC     G(KC_Z)
#define REDOMAC     S(G(KC_Z))
#define UNDOWIN     C(KC_Z)
#define REDOWIN     C(KC_Y)
#define CLIPBOARD   G(C(A(S(KC_Z))))
#define LAUNCHER    G(KC_SPACE)
#define RAYCAST     C(A(KC_SPACE))
#define RAYCLIP     C(A(G(S(KC_J))))
#define OSM_SHFT    OSM(MOD_LSFT)

//my shit

#define CESC LCTL_T(KC_ESC)

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HDN] = LAYOUT_2_3x5_3(
        KC_TAB, KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,  KC_O,    KC_P,    KC_BSPC,
        CESC  , KC_A,  KC_S,   KC_D,   KC_F,   KC_G,                  KC_H,   KC_J,   KC_K,  KC_L, KC_SCLN,   KC_QUOT,
              KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,                        KC_N,   KC_M,   KC_COMMA, KC_DOT, KC_SLSH,
                               KC_LALT, MO_NAV, KC_ENT,         KC_SPACE,  MO_SYM, OSM(MOD_LSFT),
                                                KC_BTN1, KC_BTN3, KC_BTN2,
                                     // click  ,  right  , down   , left   , up
                                     ACCEL_TOG , KC_RIGHT, KC_DOWN, KC_LEFT, KC_UP

    ),

    [CMK] = LAYOUT_2_3x5_3(
        KC_TAB, KC_Q,  KC_W,   KC_F,   KC_P,   KC_B,                   KC_J,   KC_L,   KC_U,  KC_Y, KC_SCLN,   KC_BSPC,
        CESC  , KC_A,  KC_R,   KC_S,   KC_T,   KC_G,                   KC_M,   KC_N,   KC_E,  KC_I,    KC_O,   KC_QUOT,
                KC_Z,  KC_X,   KC_C,   KC_D,   KC_V,                   KC_K,   KC_H,   KC_COMMA, KC_DOT,  KC_SLSH,
                               KC_LALT, MO_NAV, KC_ENT,         KC_SPACE,  MO_SYM, OSM(MOD_LSFT),
                                                KC_BTN1, KC_BTN3, KC_BTN2,
                                     // click  ,  right  , down   , left   , up
                                     ACCEL_TOG , KC_RIGHT, KC_DOWN, KC_LEFT, KC_UP

    ),

    [NAV] = LAYOUT_2_3x5_3(
        KC_TAB , KC_1,     KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,      KC_8,     KC_9,     KC_0, KC_TRNS,
        KC_TRNS, KC_MPLY,  KC_MPRV, KC_MNXT, OS_LSFT, KC_MINUS,          KC_LEFT, KC_DOWN,   KC_UP,    KC_RIGHT, WRKFLW2,  WRKFLW2,
                 OS_LGUI,  OS_LALT, OS_LSFT,  OS_LCTL, SALL,             KC_0,    KC_DEL,    KC_TRNS,  KC_TRNS,   KC_BSLS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, MO_ADJ, KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,
                                         // click  ,  right , down      , left   , up
                                            KC_TRNS, RGB_SPI, SNP_TOG, RGB_SPD, DRG_TOG
    ),
    [SYM] = LAYOUT_2_3x5_3(
        KC_TILDE, KC_1,   KC_7,   KC_8,   KC_9,   KC_DEL,             DWRD,     KC_NO,    KC_DOT,    QUIT,  WRKFLW1,  KC_TRNS,
        KC_TRNS,  KC_4,   KC_4,   KC_5,   KC_6,   KC_MINUS,           KC_PLUS,  OS_LGUI,  OS_LALT, OS_LSFT,  OS_LCTL, KC_GRV,
                  KC_1,   KC_1,   KC_2,   KC_3,   KC_0,               KC_EQL,   KC_DEL , KC_TRNS,  KC_TRNS,  KC_TRNS,
                                  KC_0,       MO_ADJ, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
                                            RGB_HUD, RGB_SAI, RGB_SAD,
                                         // click  ,  right , down      , left   , up
                                            RGB_TOG, RGB_VAI, RGB_RMOD, RGB_VAD, RGB_MOD
    ),
    [ADJ] = LAYOUT_2_3x5_3(
        KC_F1, KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,                   KC_F7,   KC_F8,   KC_F9,  KC_F10,    KC_F11,    KC_F12,
        QK_BOOT, KC_A,  KC_S,   KC_D,   QK_RBT,  KC_G,                  KC_H,   KC_J,   KC_K,  KC_L, KC_SCLN,   KC_SLEP,
              KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,                        KC_N,   KC_M,   KC_COMMA, KC_DOT, KC_SLSH,
                               KC_TRNS, KC_NO, KC_TRNS,         KC_TRNS,  KC_NO, KC_TRNS,
                                                KC_BTN1, KC_BTN3, KC_BTN2,
                                     // click  ,  right  , down   , left   , up
                                     BL_TOGG , BL_BRTG, BL_DOWN, BL_STEP, BL_UP

    ),

};

bool is_nshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_NAV:
    case OS_LCTL:
    case OS_LALT:
    case OS_RALT:
    case OS_LGUI:
    case OS_LSFT:
    case SW_CG:
        return true;
    default:
        return false;
    }
}

bool is_nshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_NAV:
    case SW_CG:
        return true;
    default:
        return false;
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case MO_SYM:
        case MO_NAV:
        case OS_LSFT:
        case OS_LCTL:
        case OS_LALT:
        case OS_RALT:
        case OS_LGUI:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


bool sw_win_active = false;


// Turns display off when computer turns off
void suspend_power_down_user(void) {
    kb_state.lcd_power = false;
    backlight_disable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_nshot_state(keycode, record);
    mab_process_record_haptic(keycode, record);
    mab_process_pointing_keys(keycode, record);
    process_repeat_key(keycode, record);
    // It's important to update the mod variables *after* calling process_repeat_key, or else
    // only a single modifier from the previous key is repeated (e.g. Ctrl+Shift+T then Repeat produces Shift+T)
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    if (keymap_config.swap_lctl_lgui) {
            update_swapper(
                &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
                keycode, record
            );
    } else {
            update_swapper(
                &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
                keycode, record
            );
    }
    switch (keycode) {
        case DWRD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(DWRDM);
                } else {
                        tap_code16(DWRDW);
                }
            }
            return false;
        case QUIT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(QUITM);
                } else {
                        tap_code16(QUITW);
                }
            }
            return false;
        case SAVE:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(SAVEM);
                } else {
                        tap_code16(SAVEW);
                }
            }
            return false;
        case SALL:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(SALLM);
                } else {
                        tap_code16(SALLW);
                }
            }
            return false;
        case COPY:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(CPYM);
                } else {
                        tap_code16(CPYW);
                }
            }
            return false;
        case CUT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(CUTM);
                } else {
                        tap_code16(CUTW);
                }
            }
            return false;
        case PASTE:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(PSTM);
                } else {
                        tap_code16(PSTW);
                }
            }
            return false;
        case UNDO:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(UNDOMAC);
                } else {
                        tap_code16(UNDOWIN);
                }
            }
            return false;
        case REDO:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                        tap_code16(REDOMAC);
                } else {
                        tap_code16(REDOWIN);
                }
            }
            return false;
        case SW_CG:
            if (record->event.pressed) {
              keymap_config.raw = eeconfig_read_keymap();
              keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
              keymap_config.swap_rctl_rgui = keymap_config.swap_lctl_lgui;
              eeconfig_update_keymap(keymap_config.raw);
              mab_set_pointer();
              lv_event_send(ui_Layer_Indicator, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);
            }
            return false;
        default:
            return true;
    }
    return true;
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [HDN]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [NAV]  =  { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT)},
    [SYM]  =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [ADJ]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
};
