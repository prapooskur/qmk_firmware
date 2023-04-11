#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 5
#define MATRIX_COLS 8

// SHIFT REGISTER
// Only needed for matrix_74hc595_spi.c
#define SHIFTREG_MATRIX_COL_CS B5
#define SHIFTREG_DIVISOR 128 // needs to be the same as the PMW33XX_CS_DIVISOR below
#define MATRIX_ROW_PINS_SR {D4, C6, D7, E6, B4}

#define I2C_DRIVER I2CD1

// SPI config for shift register (and trackball if enabled)
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN B1
#define SPI_MOSI_PIN B2
#define SPI_MISO_PIN B3

#define ENCODERS_PAD_A {F4}
#define ENCODERS_PAD_B {F5}
#define ENCODER_RESOLUTION 1

// #define PMW33XX_CS_PIN D2
// #define PMW33XX_CPI 1200
// #define PMW33XX_CS_DIVISOR 128 // needs to be the same as the SHIFTREG_DIVISOR above
// // #define POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_INVERT_X

#define FB_ERM_LRA 1
#define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
#define RATED_VOLTAGE 2
#define V_PEAK 2.8
#define V_RMS 2.0
#define F_LRA 150 // resonance freq
#define DRV_GREETING  alert_750ms

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_TERM 35

// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// #define AUTO_MOUSE_DELAY 100
// #define AUTO_MOUSE_TIME 100
#define CIRQUE_PINNACLE_SPI_CS_PIN D2
#define POINTING_DEVICE_TASK_THROTTLE_MS 5
#define CIRQUE_PINNACLE_DIAMETER_MM 40
// #define POINTING_DEVICE_ROTATION_90 // move to cirque specific config
// #define POINTING_DEVICE_ROTATION_90_RIGHT
#define CIRQUE_PINNACLE_TAP_ENABLE true
// #define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE true
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE

#define MOUSE_EXTENDED_REPORT
