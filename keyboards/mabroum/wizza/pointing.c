#include "wizza.h"
#include "pointing.h"
#include "keyboards/mabroum/keys.h"
#include "./quantum/pointing_device/pointing_device_modes.h"

#ifdef QUANTUM_PAINTER_ENABLE
  #include "lvgl.h"
  #include "display.h"
#endif

#define MAB_SNIPING_DPI_CONFIG_STEP 100
#define MAB_DRAGSCROLL_DPI 100
#define MAB_DRAGSCROLL_BUFFER_SIZE 6
#define MAB_DEFAULT_DPI_CONFIG_STEP 100
#define MAB_DEFAULT_DPI 400
#define MAB_MINIMUM_SNIPING_DPI 100

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
        bool    is_acceleration_enabled: 1;
    } __attribute__((packed));
} mab_config_t;

static mab_config_t g_mab_config = {0};

static uint16_t get_pointer_default_dpi(mab_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * MAB_DEFAULT_DPI_CONFIG_STEP + MAB_DEFAULT_DPI;
}

static uint16_t get_pointer_sniping_dpi(mab_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * MAB_SNIPING_DPI_CONFIG_STEP + MAB_MINIMUM_SNIPING_DPI;
}

static void write_mab_config_to_eeprom(mab_config_t* config) {
    eeconfig_update_kb(config->raw);
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(mab_config_t* config) {
    if (is_keyboard_left()) {
        if (get_pointing_mode_id() == PM_DRAG) {
            pointing_device_set_cpi_on_side(true, MAB_DRAGSCROLL_DPI);
            pointing_device_set_cpi_on_side(false, MAB_DRAGSCROLL_DPI);
        } else if (get_pointing_mode_id() == PM_PRECISION) {
            pointing_device_set_cpi_on_side(true,get_pointer_sniping_dpi(config));
            pointing_device_set_cpi_on_side(false,get_pointer_sniping_dpi(config));
        } else {
            pointing_device_set_cpi_on_side(true, get_pointer_default_dpi(config));
            pointing_device_set_cpi_on_side(false, get_pointer_default_dpi(config));
        }
    } else {
        if (get_pointing_mode_id() == PM_DRAG) {
            pointing_device_set_cpi_on_side(true, MAB_DRAGSCROLL_DPI);
            pointing_device_set_cpi(MAB_DRAGSCROLL_DPI);
        } else if (get_pointing_mode_id() == PM_PRECISION) {
            pointing_device_set_cpi_on_side(true,get_pointer_sniping_dpi(config));
            pointing_device_set_cpi(get_pointer_sniping_dpi(config));
        } else {
            pointing_device_set_cpi_on_side(true, get_pointer_default_dpi(config));
            pointing_device_set_cpi(get_pointer_default_dpi(config));
        }
    }
}

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to MAB_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(mab_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

void mab_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_mab_config, forward);
    write_mab_config_to_eeprom(&g_mab_config);
}

uint16_t mab_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_mab_config);
}

uint16_t mab_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_mab_config);
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_mab_config);
    pointing_device_init_user();
}

void eeconfig_init_kb(void) {
    g_mab_config.raw                 = 0;
    g_mab_config.pointer_default_dpi = 0;
    write_mab_config_to_eeprom(&g_mab_config);
    maybe_update_pointing_device_cpi(&g_mab_config);
    eeconfig_init_user();
}

static bool has_shift_mod(void) {
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
}

bool mab_process_pointing_keys(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                mab_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                mab_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case PMR_DRAG:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(1);
                toggle_pointing_mode_id(2);
            } 
            break;
        case PML_DRAG:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(0);
                toggle_pointing_mode_id(2);
            }
            break;
        case PML_SNIPE:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(0);
                toggle_pointing_mode_id(1);
            }
            break;
        case PMR_SNIPE:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(1);
                toggle_pointing_mode_id(1);
            }
            break;
        case PML_CARET:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(0);
                toggle_pointing_mode_id(3);
            }
            break;
        case PMR_CARET:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(1);
                toggle_pointing_mode_id(3);
            }
            break;
        case PML_VOLUME:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(0);
                toggle_pointing_mode_id(5);
            }
            break;
        case PMR_VOLUME:
            if (record->event.pressed) {
                if (get_toggled_pointing_mode_id() != 0) {
                  set_pointing_mode_id(0);
                }
                set_pointing_mode_device(1);
                toggle_pointing_mode_id(5);
            }
            break;
        default:
            break;
    }

    return true;
}

void mab_set_pointer() {
  if (keymap_config.swap_lctl_lgui) {
    g_mab_config.pointer_default_dpi  = 2;
    maybe_update_pointing_device_cpi(&g_mab_config);
  } else {
    g_mab_config.pointer_default_dpi  = 1;
    maybe_update_pointing_device_cpi(&g_mab_config);
  }
}
