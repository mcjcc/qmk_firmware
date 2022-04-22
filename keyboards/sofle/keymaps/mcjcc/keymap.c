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

#include QMK_KEYBOARD_H

#include "oled.c"
#include "encoder.c"

// Base layer is the number of layers CYCLE selects from.
#define BASE_LAYERS 2

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here (4 bytes)
    CYCLE                      // cycle through first BASE_LAYERS (62 bytes)
};

enum custom_layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE
};

enum combo_events {
    BSPC_LSFT_CLEAR,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};


combo_t key_combos[] = {
    [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo)
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case BSPC_LSFT_CLEAR:
            if (pressed) {
                tap_code16(LGUI(KC_RGHT));
                tap_code16(S(LGUI(KC_LEFT)));
                tap_code16(KC_BSPC);
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch(combo_index) {
        case BSPC_LSFT_CLEAR:
            return 1000;
    }

    return COMBO_TERM;
}

// Extra keys are added for rotary encoder support in VIA
#define LAYOUT_via( \
    LA1, LA2, LA3, LA4, LA5, LA6,           RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6, LB7, RB7, RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6, LE1, RE6, RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, LD7, RD7, RD6, RD5, RD4, RD3, RD2, RD1, \
              LE2, LE3, LE4, LE5, LE6, RE5, RE4, RE3, RE2, RE1 \
    ) \
    { \
        { LA1, LA2, LA3, LA4, LA5, LA6, KC_NO }, \
        { LB1, LB2, LB3, LB4, LB5, LB6, LB7   }, \
        { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO }, \
        { LD1, LD2, LD3, LD4, LD5, LD6, LD7   }, \
        { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO }, \
        { RA1, RA2, RA3, RA4, RA5, RA6, KC_NO }, \
        { RB1, RB2, RB3, RB4, RB5, RB6, RB7   }, \
        { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO }, \
        { RD1, RD2, RD3, RD4, RD5, RD6, RD7   }, \
        { RE1, RE2, RE3, RE4, RE5, RE6, KC_NO } \
    }

//Default keymap. This can be changed in Via. Use oled.c to change beavior that Via cannot change.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |-------.  C  ,-------|   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.  D  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LCTR | LAlt | LGUI |LOWER | /Enter  /        \Enter \  |RAISE | Space| RAlt | RCTR |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT_via(
KC_GRV, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
KC_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_VOLU,       KC_BRMD, KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
KC_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_MUTE,       KC_NO  , KC_H    , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
KC_LSFT, KC_Z  , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_BRMU, KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
              KC_LCTRL, KC_LALT ,KC_LGUI,MO(_LOWER), KC_ENT ,       KC_ENT , MO(_RAISE),KC_SPC, KC_LBRC, KC_RBRC
),
/*
 * COLEMAK - Vanilla
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |-------.  C  ,-------|   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.  D  ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
/*
[_COLEMAK] = LAYOUT_via(
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
  KC_ESC , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_VOLU,       KC_PGUP,  KC_J    , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
  KC_TAB , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_MUTE,       KC_NO  ,  KC_H    , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_VOLD,       KC_PGDN,  KC_N    , KC_M   , KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                  KC_LGUI, KC_LALT,KC_LCTRL,MO(_LOWER), KC_ENT ,           KC_SPC ,MO(_RAISE),KC_RCTRL, KC_RALT, KC_RGUI
),
*/

/*
 * COLEMAK-DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   B  |-------.  C  ,-------|   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   G  |-------.  D  ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|  R  |-------|   K  |   H  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LCTR | LAlt | LGUI |LOWER | /Enter  /        \Enter \  |RAISE | Space| RAlt | RCTR |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_COLEMAK] = LAYOUT_via(
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS ,
  KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   , KC_VOLU,       KC_BRMD,  KC_J    , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
  KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   , KC_MUTE,       XXXXXXX,  KC_M    , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   , KC_VOLD,       KC_BRMU,  KC_K    , KC_H   , KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
                  KC_LCTRL, KC_LALT ,KC_LGUI,MO(_LOWER), KC_ENT,       KC_ENT ,MO(_RAISE),KC_SPC  , KC_LBRC, KC_RBRC
),

/* LOWER
 * ,----------------------------------------.                      ,-----------------------------------------.
 * |Cycle |      |      |      |      |      |-------.  E  ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * |      | Ins  | Pscr | Menu |      |      |-------.  C  ,-------|      |      |  Up  |      | DLine|      |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * |      | LAt  | LCtl |LShift|      | Caps |-------.  D  ,-------|      | Left | Down | Rigth|  Del |      |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * |      | Undo |  Cut | Copy | Paste|      |-------|  R  |-------|      |      |      | LEnd |      |      |
 * `-----------------------------------------/      /       \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter /         \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/      /           \      \ |      |      |      |      |
 *            `----------------------------------'             '------''---------------------------'
 */
[_LOWER] = LAYOUT_via(
    CYCLE, _______, _______, _______, _______ , _______,                       _______, _______, KC_PSLS, KC_PAST , KC_PMNS , KC_EQL,
  _______, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN , XXXXXXX, _______,    RGB_VAD,  KC_PGUP, KC_7   , KC_8   , KC_9    , KC_PPLS , KC_DEL ,
  _______, XXXXXXX, KC_LEFT, KC_UP  , KC_DOWN , KC_RGHT, _______,    RGB_TOG,  KC_PGDN, KC_4   , KC_5   , KC_6    , KC_EQL  , _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX , KC_SPC , _______,    RGB_VAI,  KC_LBRC, KC_1   , KC_2   , KC_3    , _______ , _______,
                   _______, _______, _______, _______, _______,        _______, _______, KC_0, KC_LPRN, KC_RPRN
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------.  E  ,-------|  F8  |  F9  |  F10 |  F11 | F12  |      |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |-------.  C  ,-------|   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.  D  ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|  R  |-------|   [  |   ]  |   ;  |   :  |   \  |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_RAISE] = LAYOUT_via(
  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                         KC_F7  , KC_F8  , KC_F9  , KC_F10  , KC_F11  , KC_F12 ,
  _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,       _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN , KC_RPRN , KC_DEL ,
  _______, XXXXXXX, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,       _______, KC_LEFT, KC_DOWN, KC_UP , KC_RGHT , KC_RPRN , KC_PIPE,
  _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS  , _______,
                  _______, _______, _______, _______, _______,           _______, _______, _______, KC_LPRN, KC_RPRN
)
};

// Custom keycode handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // handling this once instead of in each keycode uses less program memory.
    if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
        return false;
    }

    switch (keycode) {
        case CYCLE:
            set_single_persistent_default_layer((1+get_highest_layer(default_layer_state)) % BASE_LAYERS);
            break;
    }

    // this uses less memory than returning in each case.
    return keycode < SAFE_RANGE;
};

#ifdef SPLIT_KEYBOARD
void housekeeping_task_user(void) {
    static uint32_t last_sync = 0;
    static layer_state_t old_layer_state = 0;
    if (timer_elapsed32(last_sync) > 500 && (!is_keyboard_master() && old_layer_state != layer_state)) {
       #ifdef CONSOLE_ENABLE
       print("house_keeping_task_user fired!\n");
       #endif
        old_layer_state = layer_state;
        layer_state_set_user(layer_state);
    }
}
#endif

#ifdef RGBLIGHT_ENABLE

// per key LEDs
// static uint8_t left_leds_sm[][2] = {{0,0}, {2,3}, {5, 9}, {11, 12}, {14, 15}, {17, 24}, {26, 27}, {29, 35}};
// static uint8_t right_leds_sm[][2] = {{38, 44}, {46, 47}, {49, 56}, {58, 59}, {61, 62}, {64, 68}, {70, 71}, {73,73}};

// underglow LEDS
static uint8_t left_leds_underglow[] = {4, 16, 28, 1, 13, 25, 10};
static uint8_t right_leds_underglow[] = {45, 57, 69, 48, 60, 72, 63};

static uint8_t left_thumb_led = 36;
static uint8_t right_thumb_led = 37;

static led_t led_state;

void apply_underglow(uint8_t *arr, size_t len, uint8_t hue, uint8_t sat, uint8_t val, void (*fnPtr)(uint8_t, uint8_t, uint8_t, uint8_t)) {
    for(size_t i = 0; i < len; ++i) {
        fnPtr(hue, sat, val, arr[i]);
    }             
};

// lets keep brightness between layer changes
void update_rgblight_val(HSV *color, uint8_t *val) {
    color->v = *val;
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))


void update_led(void) {
    HSV layer_color = rgblight_get_hsv();
    uint8_t rgblight_value = layer_color.v;

    HSV indicator_color = layer_color;

    switch(get_highest_layer(layer_state)) {
        case _LOWER:
            layer_color = (HSV){hsv_RED};
            break;
        case _RAISE:
            layer_color = (HSV){hsv_GREEN};
            break;
        default:
            layer_color = (HSV){hsv_GOLD};
            break;
    }
    indicator_color = (led_state.caps_lock) ? (HSV){hsv_PURP} : layer_color;

    update_rgblight_val(&layer_color, &rgblight_value);
    update_rgblight_val(&indicator_color, &rgblight_value);

    uint8_t lh = layer_color.h;
    uint8_t ls = layer_color.s;
    uint8_t lv = layer_color.v;

    uint8_t ih = indicator_color.h;
    uint8_t is = indicator_color.s;
    uint8_t iv = indicator_color.v; 

    apply_underglow(right_leds_underglow, ARRAY_SIZE(right_leds_underglow), lh, ls, lv, rgblight_sethsv_at);
    apply_underglow(left_leds_underglow, ARRAY_SIZE(left_leds_underglow), lh, ls, lv, rgblight_sethsv_at);

    // set caps lock indicator colors
    rgblight_sethsv_range(ih, is, iv, left_thumb_led, right_thumb_led+1);
}

layer_state_t layer_state_set_user(layer_state_t layer_state) {
    update_led();
    return layer_state;
}

bool led_update_user(led_t state) {
    led_state = state;
    update_led();
    return true;
}


void keyboard_post_init_user() {
    // for (size_t i = 0; i < ARRAY_SIZE(left_leds_sm); ++i) {
    //     rgblight_set_effect_range(left_leds_sm[i][0],left_leds_sm[i][1] - left_leds_sm[i][0] + 1);
    //     rgblight_sethsv_noeeprom(hsv_PURP);

    //     rgblight_set_effect_range(right_leds_sm[i][0],right_leds_sm[i][1] - right_leds_sm[i][0] + 1);
    //     rgblight_sethsv_noeeprom(hsv_PURP);

    //     // rgblight_sethsv_range(hsv_GOLD, left_leds_sm[i][0], left_leds_sm[i][1]+1);
    //     // rgblight_sethsv_range(hsv_GOLD, right_leds_sm[i][0], right_leds_sm[i][1]+1);
    // }

    // apply_underglow(right_leds_underglow, ARRAY_SIZE(right_leds_underglow), hsv_PURP, rgblight_sethsv_at);
    // apply_underglow(left_leds_underglow, ARRAY_SIZE(left_leds_underglow), hsv_PURP, rgblight_sethsv_at);
    // rgblight_sethsv_range(hsv_PURP, left_thumb_led, right_thumb_led+1);

}


#endif