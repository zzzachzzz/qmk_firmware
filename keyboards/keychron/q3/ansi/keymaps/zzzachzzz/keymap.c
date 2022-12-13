/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

enum layers{
    L0,
    L1,
};

enum {
    TD_LSFT_CAPS,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

enum {
    SFT_CAPS = TD(TD_LSFT_CAPS),
    ESC_L1 = LT(L1, KC_ESC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L0] = LAYOUT_tkl_ansi(
        TG(L1),             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_SCRL,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        ESC_L1,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        SFT_CAPS,           KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  TT(L1),     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [L1] = LAYOUT_tkl_ansi(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  KC_MS_U,  _______,  _______,  _______,  _______,  KC_BTN1,  KC_BTN2,  _______,  KC_MPRV,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_MPLY,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  KC_MNXT,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case LT(L1, KC_ESC):
        //     return 500;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    switch (keycode) {
        case KC_LEFT: {
            static bool home_key_registered = false;
            if (record->event.pressed) {
                if (
                    // On Layer 1, H bound to Left
                    layer_state_is(L1)
                    && mods & MOD_MASK_ALT
                ) {
                    del_mods(MOD_MASK_ALT);
                    register_code(KC_HOME);
                    home_key_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else if (home_key_registered) {
                unregister_code(KC_HOME);
                home_key_registered = false;
                return false;
            }
            return true;
        }
        case KC_RIGHT: {
            static bool end_key_registered = false;
            if (record->event.pressed) {
                if (
                    // On Layer 1, L bound to Right
                    layer_state_is(L1)
                    && mods & MOD_MASK_ALT
                ) {
                    del_mods(MOD_MASK_ALT);
                    register_code(KC_END);
                    end_key_registered = true;
                    set_mods(mods);
                    return false;
                }
            } else if (end_key_registered) {
                unregister_code(KC_END);
                end_key_registered = false;
                return false;
            }
            return true;
        }
    }
    return true;
}
