// Copyright 2022 Alaa Mansour (@AlaaSaadAbdo)
// SPDX-License-Identifier: GPL-2.0-or-later

// Copyright 2022 Alaa Mansour (@AlaaSaadAbdo)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define POINTING_DEVICE_TASK_THROTTLE_MS 5
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define POINTING_DEVICE_ROTATION_90 // move to cirque specific config
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_ROTATION_90_RIGHT
#define CIRQUE_PINNACLE_TAP_ENABLE true
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE true
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE true
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C1_CLOCK_SPEED  400000
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 1500
#define AUTO_MOUSE_DELAY 1000
#define NO_ACTION_ONESHOT

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_TERM 30
#define ENCODERS_PAD_A { D2 , D4 }
#define ENCODERS_PAD_B { D3 , C6 }
