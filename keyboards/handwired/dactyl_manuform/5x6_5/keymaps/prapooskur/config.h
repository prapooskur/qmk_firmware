/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EE_HANDS

#define KINETIC_SPEED

<<<<<<<< HEAD:keyboards/handwired/dactyl_manuform/5x6_5/keymaps/prapooskur/config.h
#define COMBO_COUNT 2
#define COMBO_ONLY_FROM_LAYER 0

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
========
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

#define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 12

// USART Config

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.

//TX pin autodefined as soft_serial_pin for some reason

//#define SERIAL_USART_TX_PIN D0     // USART TX pin
#define SERIAL_USART_RX_PIN D1     // USART RX pin

#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 12
>>>>>>>> 78d1c42cda321f524d74a4553aa024094787aab4:keyboards/handwired/dactyl_manuform/5x6_5/config.h
