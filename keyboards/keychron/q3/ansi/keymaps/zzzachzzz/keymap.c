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

#if (__has_include("jokes.h"))
#include "jokes.h"
#else
#define PARTLY_FUNNY_JOKE ""
#endif

enum layers {
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
    C_G_L = LCTL(LGUI(KC_LEFT)),
    C_G_R = LCTL(LGUI(KC_RIGHT)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L0] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_SCRL,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        ESC_L1,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        SFT_CAPS,           KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  TT(L1),     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [L1] = LAYOUT_tkl_ansi(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  RGB_TOG,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  KC_MS_U,  _______,  _______,  _______,  _______,  KC_BTN1,  KC_BTN2,  _______,  KC_MPRV,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_DEL,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_MPLY,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  KC_MNXT,  _______,  C_G_L,    C_G_R,    _______,              _______,            _______,
        _______,  _______,  _______,                                QK_LEAD,                                _______,  _______,  _______,    _______,  RGB_RMOD, _______, RGB_MOD),
};

LEADER_EXTERNS();

#define LEADER_RESET (leading = false, leader_end())

void matrix_scan_user(void) {
    if (leading && leader_sequence_size > 0) {
        SEQ_ONE_KEY(KC_LEFT) {
            register_code(KC_HOME);
            unregister_code(KC_HOME);
            return LEADER_RESET;
        }
        SEQ_ONE_KEY(KC_RIGHT) {
            register_code(KC_END);
            unregister_code(KC_END);
            return LEADER_RESET;
        }
        SEQ_ONE_KEY(KC_DOWN) {
            register_code(KC_PAGE_DOWN);
            unregister_code(KC_PAGE_DOWN);
            return LEADER_RESET;
        }
        SEQ_ONE_KEY(KC_UP) {
            register_code(KC_PAGE_UP);
            unregister_code(KC_PAGE_UP);
            return LEADER_RESET;
        }
        SEQ_FOUR_KEYS(KC_PGDN, KC_BSPC, KC_PGDN, KC_BSPC) {
            SEND_STRING(PARTLY_FUNNY_JOKE);
            return LEADER_RESET;
        }
    }

    if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT) {
        return LEADER_RESET;
    }
}
