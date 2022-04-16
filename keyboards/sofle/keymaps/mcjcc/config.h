 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

// More lighting options in quantum/rgblight/rgblight.h
#ifdef RGBLIGHT_ENABLE
// #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+2

// When flashed, this is the color that it defaults to (purplish)
#define RGBLIGHT_DEFAULT_HUE 40 
#define RGBLIGHT_DEFAULT_SAT 230 
#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL 
// #define RGBLIGHT_LAYERS_RETAIN_VAL // I think this only works if RGBLIGHT_LAYERS is defined

// colors
#define hsv_PURP              200, 191, RGBLIGHT_DEFAULT_VAL
#define hsv_RED                 0, 220, RGBLIGHT_DEFAULT_VAL
#define hsv_GREEN              96, 181, RGBLIGHT_DEFAULT_VAL
#define hsv_ORANGE             16, 255, RGBLIGHT_DEFAULT_VAL
#define hsv_GOLD               40, 230, RGBLIGHT_DEFAULT_VAL


// Disabling some of these is a good way to save flash space.
#undef RGBLIGHT_EFFECT_ALTERNATING     // 108
#undef RGBLIGHT_EFFECT_RGB_TEST        // 158
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD    // 160
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT // 168
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL   // 192
#undef RGBLIGHT_EFFECT_BREATHING       // 348
#undef RGBLIGHT_EFFECT_KNIGHT          // 336
#undef RGBLIGHT_EFFECT_SNAKE           // 406
#undef RGBLIGHT_EFFECT_CHRISTMAS       // 508
#undef RGBLIGHT_EFFECT_TWINKLE         // 1156
#endif

// Disabled to save space
#define NO_ACTION_ONESHOT  // 332
#define NO_ACTION_MACRO    // 0
#define NO_ACTION_FUNCTION // 0
#define DISABLE_LEADER     // 0

#define OLED_FONT_H "./keymaps/mcjcc/glcdfont.c"

#define UNICODE_SELECTED_MODES UC_WINC

// More saving space stuff
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define SPLIT_WPM_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

// syncing keyboard settings
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define COMBO_TERM 40
// #define COMBO_STRICT_TIMER
// #define COMBO_MUST_PRESS_IN_ORDER

// #define OLED_FONT_WIDTH    6
// #define OLED_FONT_HEIGHT   8