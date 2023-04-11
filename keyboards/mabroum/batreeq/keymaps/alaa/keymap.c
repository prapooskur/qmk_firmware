#include "repeat.h"
#include "nshot_mod.h"
#include "swapper.h"
#include "keyboards/mabroum/mab_haptic.h"
#include "keyboards/mabroum/mab_pointing.h"
#include "keyboards/mabroum/keys.h"

enum layers {
    HDN = 0,
    NAV,
    SYM,
    HDNW,
    NAVW,
    SYMW,
};

// pointing
#define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
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
#define MO_NAV MO(1)
#define MO_SYM MO(2)

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
#define OSM_SHFT    OSM(MOD_LSFT)
#define RAYCAST     C(A(KC_SPACE))
#define RAYCLIP     C(A(G(S(KC_J))))

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HDN] = LAYOUT_23332(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                   KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                   KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,                                     KC_U,   KC_O,     KC_Y,
                                        MO_NAV, KC_SPACE,       OSM(MOD_LSFT), MO_SYM,
                                        SNIPING, KC_BTN3, KC_BTN1, KC_BTN2
    ),

    [NAV] = LAYOUT_23332(
        SCRNSHT,   KC_ENT, KC_BSPC, KC_TAB,  KC_DEL,            DWRD,    KC_NO,     KC_UP,    QUIT,       WRKFLW1,
        OS_LCTL,   OS_LALT, OS_LGUI,  OS_LSFT, SALL,            KC_DOT,  KC_LEFT,   KC_DOWN,  KC_RIGHT,   WRKFLW2,
                   CUT,    COPY,     PASTE,                                 KC_ENT,    KC_BSPC,  KC_TAB,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [SYM] = LAYOUT_23332(
        KC_TILDE,   KC_9,   KC_8,   KC_7,   KC_EQUAL,           KC_COMMA, KC_SCLN, KC_COLN, KC_BSLS, KC_GRAVE,
        KC_3,       KC_2,   KC_1,   KC_0,   KC_MINUS,           KC_DOT,   OS_LSFT, OS_LGUI,  OS_RALT,  OS_LCTL,
                    KC_6,   KC_5,   KC_4,                                 KC_QUES, KC_EXLM, KC_SLSH,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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
        return true;
    default:
        return false;
    }
}

bool is_nshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_NAV:
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
            }
            return false;
        default:
            return true;
    }
    return true;
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [HDN]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [NAV]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [SYM]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
};
