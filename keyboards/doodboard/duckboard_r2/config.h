/* Copyright 2020-2021 doodboard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* media key slowdown for windows */
#define TAP_CODE_DELAY 20

#ifdef RGBLIGHT_ENABLE
#define RGBLED_NUM 8    // Number of LEDs
#endif

//Turn off OLED after a certain duration of no keys being pressed
#define OLED_TIMEOUT 20000
