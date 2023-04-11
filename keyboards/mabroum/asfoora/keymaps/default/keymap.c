#include "oneshot.h"

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    SNIPING_MODE,
    SNIPING_MODE_TOGGLE,
    DRAGSCROLL_MODE,
    DRAGSCROLL_MODE_TOGGLE,
    ML_TOG,
};

#include "g/keymap_combo.h"

#define SCROLL_DIVISOR 100

enum layers {
    HDN = 0,
    NAV,
    SYM,
    HDNW,
    NAVW,
    SYMW,
    MOUS,
};

// pointing
#define ASFOORA_SNIPING_DPI_CONFIG_STEP 100
#define ASFOORA_DRAGSCROLL_DPI 100
#define ASFOORA_DRAGSCROLL_BUFFER_SIZE 6
#define ASFOORA_DEFAULT_DPI_CONFIG_STEP 200
#define ASFOORA_MINIMUM_DEFAULT_DPI 600
#define ASFOORA_MINIMUM_SNIPING_DPI 200
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE

// global
#define SCRNSHT     C(A(S(KC_P)))
#define WRKFLW1     A(C(S(G(KC_K))))
#define WRKFLW2     A(C(S(G(KC_Y))))

// layers
#define MO_NAV MO(1)
#define MO_SYM MO(2)
#define MO_NAVW MO(4)
#define MO_SYMW MO(5)

// mac
#define PST         G(KC_V)
#define CPY         G(KC_C)
#define CUT         G(KC_X)
#define SALL        G(KC_A)
#define DWRD        A(KC_BSPC)
#define QUIT        G(KC_Q)

//windows
#define PSTW         C(KC_V)
#define CPYW         C(KC_C)
#define CUTW         C(KC_X)
#define SALLW        C(KC_A)
#define DWRDW        C(KC_BSPC)
#define QUITW        A(KC_F4)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HDN] = LAYOUT_ortho_23332x2(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                   KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                   KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,   KC_1,                   KC_2,     KC_U,   KC_O,     KC_Y,
                                        MO_NAV, KC_SPACE,       OS_SHFT, MO_SYM
    ),

    [NAV] = LAYOUT_ortho_23332x2(
        SCRNSHT,   KC_ENT, KC_BSPC, KC_TAB,  KC_DEL,                 DWRD,    KC_NO,     KC_UP,    QUIT,       WRKFLW1,
        OS_CTRL,   OS_ALT, OS_CMD,  OS_SHFT, SALL,                   KC_DOT,  KC_LEFT,   KC_DOWN,  KC_RIGHT,   WRKFLW2,
                   CUT,    CPY,     PST,     KC_NO,                  KC_NO,   KC_ENT,    KC_BSPC,  KC_TAB,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [SYM] = LAYOUT_ortho_23332x2(
        KC_TILDE,   KC_9,   KC_8,   KC_7,   KC_EQUAL,                   KC_COMMA, KC_SCLN, KC_COLN, KC_BSLS, KC_GRAVE,
        KC_3,       KC_2,   KC_1,   KC_0,   KC_MINUS,                   KC_DOT,   OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
                    KC_6,   KC_5,   KC_4,   KC_NO,                      KC_NO,    KC_QUES, KC_EXLM, KC_SLSH,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [HDNW] = LAYOUT_ortho_23332x2(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                   KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                   KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,   KC_1,                   KC_1,     KC_U,   KC_O,     KC_Y,
                                        MO_NAVW, KC_SPACE, OS_SHFT, MO_SYMW
    ),

    [NAVW] = LAYOUT_ortho_23332x2(
        SCRNSHT,   KC_ENT, KC_BSPC, KC_TAB,  KC_DEL,                 DWRD,    KC_F2,     KC_UP,    QUITW,      WRKFLW1,
        OS_CMD,    OS_ALT, OS_CTRL, OS_SHFT, SALLW,                  SALLW,   KC_LEFT,   KC_DOWN,  KC_RIGHT,   WRKFLW2,
                   CUTW,   CPYW,    PSTW,    KC_NO,                  KC_NO,   KC_ENT,    KC_BSPC,  KC_TAB,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [SYMW] = LAYOUT_ortho_23332x2(
        KC_TILDE,   KC_9,   KC_8,   KC_7,   KC_EQUAL,                   KC_COMMA, KC_SCLN, KC_COLN, KC_BSLS, KC_GRAVE,
        KC_3,       KC_2,   KC_1,   KC_0,   KC_MINUS,                   KC_DOT,   OS_SHFT,     OS_CTRL,     OS_ALT,     OS_CMD,
                    KC_6,   KC_5,   KC_4,   KC_NO,                      KC_NO,    KC_QUES, KC_EXLM, KC_SLSH,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [MOUS] = LAYOUT_ortho_23332x2(
        SNIPING,  ML_TOG,    ML_TOG,  ML_TOG,    SNIPING,                ML_TOG, ML_TOG, ML_TOG, ML_TOG, ML_TOG,
        OS_CMD,   OS_ALT,    OS_CTRL, OS_SHFT,   DRGSCRL,                ML_TOG, ML_TOG, ML_TOG, ML_TOG, ML_TOG,
                  KC_BTN3,   KC_BTN2, KC_BTN1,   KC_NO,                  KC_NO,  ML_TOG, ML_TOG, ML_TOG,
                                                ML_TOG, ML_TOG,     ML_TOG, ML_TOG
    )

};

// One shot implementation
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_SYMW:
    case MO_NAV:
    case MO_NAVW:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO_NAV:
    case MO_SYM:
    case MO_NAVW:
    case MO_SYMW:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

// bool set_scrolling = false;

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case DRAGSCROLL_MODE_TOGGLE:
        case DRAGSCROLL_MODE:
        case SNIPING_MODE_TOGGLE:
        case SNIPING_MODE:
            return true;
        default:
            return false;
    }
    return  is_mouse_record_user(keycode, record);
}

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
    } __attribute__((packed));
} asfoora_config_t;

static asfoora_config_t g_asfoora_config = {0};

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(asfoora_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * ASFOORA_DEFAULT_DPI_CONFIG_STEP + ASFOORA_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(asfoora_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * ASFOORA_SNIPING_DPI_CONFIG_STEP + ASFOORA_MINIMUM_SNIPING_DPI;
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(asfoora_config_t* config) {
    if (config->is_dragscroll_enabled) {
        pointing_device_set_cpi(ASFOORA_DRAGSCROLL_DPI);
    } else if (config->is_sniping_enabled) {
        pointing_device_set_cpi(get_pointer_sniping_dpi(config));
    } else {
        pointing_device_set_cpi(get_pointer_default_dpi(config));
    }
}

bool asfoora_get_pointer_dragscroll_enabled(void) {
    return g_asfoora_config.is_dragscroll_enabled;
}

bool asfoora_get_pointer_sniping_enabled(void) {
    return g_asfoora_config.is_sniping_enabled;
}

uint16_t asfoora_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_asfoora_config);
}

uint16_t asfoora_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_asfoora_config);
}

void asfoora_set_pointer_sniping_enabled(bool enable) {
    g_asfoora_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_asfoora_config);
}

void asfoora_set_pointer_dragscroll_enabled(bool enable) {
    g_asfoora_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&g_asfoora_config);
}

static void pointing_device_task_asfoora(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (g_asfoora_config.is_dragscroll_enabled) {
        scroll_buffer_x += mouse_report->x;
        scroll_buffer_y -= mouse_report->y;
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > ASFOORA_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > ASFOORA_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
        pointing_device_task_asfoora(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    switch (keycode) {
        case SNIPING_MODE:
            asfoora_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                asfoora_set_pointer_sniping_enabled(!asfoora_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            asfoora_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                asfoora_set_pointer_dragscroll_enabled(!asfoora_get_pointer_dragscroll_enabled());
            }
            break;
        case ML_TOG:
            if (record->event.pressed) {
                layer_off(HDNW);
                return true;
            }
            break;
    }

    return true;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        case UNDO:
        case REDO:
            if (layer_state_is(3)) {
                return false;
            }
        case UNDOW:
        case REDOW:
            if (layer_state_is(0)) {
                return false;
            }
    }

    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [HDN]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [NAV]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [SYM]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [HDNW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [NAVW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [SYMW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [MOUS] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_MS_WH_RIGHT, KC_MS_WH_LEFT)  }
};
#endif

void pointing_device_init_user(void) {
    set_auto_mouse_layer(6); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_asfoora_config);
    pointing_device_init_user();
}

static void write_asfoora_config_to_eeprom(asfoora_config_t* config) {
    eeconfig_update_kb(config->raw);
}

void eeconfig_init_kb(void) {
    g_asfoora_config.raw                 = 0;
    g_asfoora_config.pointer_default_dpi = 2; // DPI=1200
    write_asfoora_config_to_eeprom(&g_asfoora_config);
    maybe_update_pointing_device_cpi(&g_asfoora_config);
    eeconfig_init_user();
}
// void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  /* debug_enable=true; */
  // debug_matrix=true;
  // debug_keyboard=true;
  /* debug_mouse=true; */
// }
