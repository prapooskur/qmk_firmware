// #include QMK_KEYBOARD_H
#include "nshot_mod.h"

enum keycodes {
    SNIPING_MODE = SAFE_RANGE,
    SNIPING_MODE_TOGGLE,
    DRAGSCROLL_MODE,
    DRAGSCROLL_MODE_TOGGLE,
    ACCELERATION_TOGGLE,
    OS_LCTL,
    OS_LALT,
    OS_LGUI,
    OS_LSFT,
    OSR_SFT,
};

nshot_state_t  nshot_states[] = {
    {OS_LSFT, MOD_BIT(KC_LSFT), 1, true,  os_up_unqueued, 0, false},
    {OS_LCTL, MOD_BIT(KC_LCTL), 1, true,  os_up_unqueued, 0, false},
    {OS_LALT, MOD_BIT(KC_LALT), 1, true,  os_up_unqueued, 0, false},
    {OS_LGUI, MOD_BIT(KC_LGUI), 1, true,  os_up_unqueued, 0, false},
    {OSR_SFT, MOD_BIT(KC_LSFT), 1, false, os_up_unqueued, 0, false}
};
uint8_t        NUM_NSHOT_STATES = sizeof(nshot_states) / sizeof(nshot_state_t);


enum layers {
    HDN = 0,
    NAV,
    SYM,
    HDNW,
    NAVW,
    SYMW,
};

// pointing
#define ASFOORA_SNIPING_DPI_CONFIG_STEP 100
#define ASFOORA_DRAGSCROLL_DPI 100
#define ASFOORA_DRAGSCROLL_BUFFER_SIZE 6
#define ASFOORA_DEFAULT_DPI_CONFIG_STEP 100
#define ASFOORA_MINIMUM_DEFAULT_DPI 400
#define ASFOORA_MINIMUM_SNIPING_DPI 100
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE
#define ACCEL_TOG ACCELERATION_TOGGLE

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
#define SAVE        G(KC_S)

//windows
#define PSTW         C(KC_V)
#define CPYW         C(KC_C)
#define CUTW         C(KC_X)
#define SALLW        C(KC_A)
#define DWRDW        C(KC_BSPC)
#define QUITW        A(KC_F4)
#define SAVEW        C(KC_S)
#define RAYCAST     C(A(KC_SPACE))
#define RAYCLIP     C(A(G(S(KC_J))))

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [HDN] = LAYOUT_batreeq(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                   KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                   KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,                                     KC_U,   KC_O,     KC_Y,
                                        MO_NAV, KC_SPACE,       OSM(MOD_LSFT), MO_SYM,
                                        SNIPING, KC_BTN1, KC_BTN2, KC_BTN3
    ),

    [NAV] = LAYOUT_batreeq(
        SCRNSHT,   KC_ENT, KC_BSPC, KC_TAB,  KC_DEL,                 DWRD,    KC_NO,     KC_UP,    QUIT,       WRKFLW1,
        OS_LCTL,   OS_LALT, OS_LGUI,  OS_LSFT, SALL,                   KC_DOT,  KC_LEFT,   KC_DOWN,  KC_RIGHT,   WRKFLW2,
                   CUT,    CPY,     PST,                                      KC_ENT,    KC_BSPC,  KC_TAB,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [SYM] = LAYOUT_batreeq(
        KC_TILDE,   KC_9,   KC_8,   KC_7,   KC_EQUAL,                   KC_COMMA, KC_SCLN, KC_COLN, KC_BSLS, KC_GRAVE,
        KC_3,       KC_2,   KC_1,   KC_0,   KC_MINUS,                   KC_DOT,   OS_LSFT, OS_LGUI,  OS_LALT,  OS_LCTL,
                    KC_6,   KC_5,   KC_4,                                         KC_QUES, KC_EXLM, KC_SLSH,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [HDNW] = LAYOUT_batreeq(
        KC_W,   KC_F,   KC_M,   KC_P,   KC_B,                   KC_COMMA, KC_X,   KC_QUOTE, KC_J,   KC_K,
        KC_R,   KC_S,   KC_N,   KC_T,   KC_G,                   KC_DOT,   KC_A,   KC_E,     KC_I,   KC_H,
                KC_C,   KC_L,   KC_D,                                     KC_U,   KC_O,     KC_Y,
                                        MO_NAVW, KC_SPACE,  OSM(MOD_LSFT), MO_SYMW,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [NAVW] = LAYOUT_batreeq(
        SCRNSHT,   KC_ENT, KC_BSPC, KC_TAB,  KC_DEL,                 DWRD,    KC_F2,     KC_UP,    QUITW,      WRKFLW1,
        OS_LGUI,    OS_LALT, OS_LCTL, OS_LSFT, SALLW,                  SALLW,   KC_LEFT,   KC_DOWN,  KC_RIGHT,   WRKFLW2,
                   CUTW,   CPYW,    PSTW,                                     KC_ENT,    KC_BSPC,  KC_TAB,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [SYMW] = LAYOUT_batreeq(
        KC_TILDE,   KC_9,   KC_8,   KC_7,   KC_EQUAL,                   KC_COMMA, KC_SCLN, KC_COLN, KC_BSLS, KC_GRAVE,
        KC_3,       KC_2,   KC_1,   KC_0,   KC_MINUS,                   KC_DOT,   OS_LSFT,     OS_LCTL,     OS_LALT,     OS_LGUI,
                    KC_6,   KC_5,   KC_4,                                         KC_QUES, KC_EXLM, KC_SLSH,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool is_nshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO_SYM:
    case MO_NAV:
    case MO_SYMW:
    case MO_NAVW:
    case OS_LCTL:
    case OS_LALT:
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
    case MO_SYMW:
    case MO_NAVW:
        return true;
    default:
        return false;
    }
}

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
        bool    is_acceleration_enabled: 1;
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

bool asfoora_get_pointer_acceleration_enabled(void) {
    return g_asfoora_config.is_acceleration_enabled;
}

void asfoora_set_pointer_acceleration_enabled(bool enable) {
    g_asfoora_config.is_acceleration_enabled = enable;
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
    if (g_asfoora_config.is_acceleration_enabled && !g_asfoora_config.is_dragscroll_enabled && !g_asfoora_config.is_sniping_enabled) {
        mouse_xy_report_t x = mouse_report->x, y = mouse_report->y;
        mouse_report->x = 0;
        mouse_report->y = 0;

        x = (mouse_xy_report_t)(x > 0 ? x * x / 16 + x : -x * x / 16 + x);
        y = (mouse_xy_report_t)(y > 0 ? y * y / 16 + y : -y * y / 16 + y);
        mouse_report->x = x;
        mouse_report->y = y;
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    pointing_device_task_asfoora(&mouse_report);
    mouse_report = pointing_device_task_user(mouse_report);
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_nshot_state(keycode, record);
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
        case ACCELERATION_TOGGLE:
            if (record->event.pressed) {
                asfoora_set_pointer_acceleration_enabled(!asfoora_get_pointer_acceleration_enabled());
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

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [HDN]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [NAV]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [SYM]  =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [HDNW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [NAVW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [SYMW] =  { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)}
};

bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QUIT:
        case QUITW:
        case UNDO:
        case REDO:
        case UNDOW:
        case REDOW:
        case QK_BOOT:
        case EE_CLR:
        case CPYW:
        case CUTW:
        case PSTW:
        case CPY:
        case CUT:
        case PST:
        case WIN:
            return true;
            break;
        case KC_S:
            if (record->event.pressed) {
                    if (get_oneshot_mods() & MOD_MASK_CTRL) {
                            return true;
                        }
                    if (get_oneshot_mods() & MOD_MASK_GUI) {
                            return true;
                        }
                    if (get_mods() & MOD_MASK_CTRL) {
                            return true;
                        }
                    if (get_mods() & MOD_MASK_GUI) {
                            return true;
                        }
                    }
            break;
    }
    return false;
}

// void keyboard_post_init_user(void) {
//   // Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
//   debug_keyboard=true;
//   debug_mouse=true;
// }
