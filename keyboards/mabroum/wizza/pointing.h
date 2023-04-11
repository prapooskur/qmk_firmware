#pragma once
#include "quantum.h"

uint16_t mab_get_pointer_default_dpi(void);

void mab_cycle_pointer_default_dpi(bool forward);

uint16_t mab_get_pointer_sniping_dpi(void);

bool mab_process_pointing_keys(uint16_t keycode, keyrecord_t *record);

void mab_set_pointer(void);
