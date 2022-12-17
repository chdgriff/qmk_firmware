#include QMK_KEYBOARD_H

#define _Base_Layer             0
#define _Function_Layer         1
#define _Mac_Function_Layer     2
#define _Blank_Layer            3
#define _Blank_Function_Layer   4
#define RGB_DEFAULT_HUE         169
#define RGB_DEFAULT_SAT         242
#define RGB_DEFAULT_VAL         255

#define BACKLIGHT_TIMEOUT 7    // in minutes
static uint16_t idle_timer = 0;
static uint8_t min_counter = 0;
static bool led_on = true;
static HSV old_hsv;

enum custom_keycodes {
    SWPCTRL = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Base_Layer] = LAYOUT_75_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_END,   KC_PSCR, KC_HOME,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,           KC_INS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
        KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                   KC_UP,    KC_PGDN,
        KC_LCTL,  KC_LGUI,  KC_LALT,                               KC_SPC,                   KC_RALT,    MO(_Function_Layer),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

   [_Function_Layer] = LAYOUT_75_ansi(
        DF(_Blank_Layer), _______,  _______,  _______,  _______,  _______,  _______,  KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_MUTE,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,                 _______,   _______,
        SWPCTRL,  MAGIC_TOGGLE_GUI,  _______,                                _______,                  _______,        _______,         _______,  _______,  _______,   _______
        ),

    [_Mac_Function_Layer] = LAYOUT_75_ansi(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            DEBUG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS,
                                            KC_TRNS, KC_TRNS, RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, RGB_SAD, RGB_HUD, RGB_SAI, RGB_RMOD, KC_TRNS, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_VAD, RGB_TOG, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_Blank_Layer] = LAYOUT_75_ansi(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(_Blank_Function_Layer), KC_NO, KC_NO, KC_NO, KC_NO),

    [_Blank_Function_Layer] = LAYOUT_75_ansi(DF(_Base_Layer), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case SWPCTRL:
                process_magic(MAGIC_TOGGLE_CTL_GUI, record);
                process_magic(MAGIC_UNSWAP_RCTL_RGUI, record);
                break;
            // case MACRO_1:
            //     SEND_STRING("");
            //     break;
        }
        if (led_on == false) {
		    rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(old_hsv.h, old_hsv.s, old_hsv.v);
            led_on = true;
            }
        idle_timer = timer_read();
        min_counter = 0;
    }
    return true;
};

const rgblight_segment_t PROGMEM capslock_light_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 3, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {6, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_light_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
    rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    // rgblight_sethsv_noeeprom(120, 80, 93);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    // rgblight_set_layer_state(1, layer_state_cmp(state, _Blank_Layer));
    if (layer_state_cmp(state, _Blank_Layer)) {
        rgblight_sethsv_noeeprom(HSV_RED);
    }
    else if (layer_state_cmp(state, _Base_Layer)){
        rgblight_sethsv_noeeprom(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
    }
    return state;
}

void matrix_scan_user(void) {
  // idle_timer needs to be set one time
    if (idle_timer == 0) idle_timer = timer_read();
    if ( led_on && timer_elapsed(idle_timer) > 60000) {
        min_counter++;
        idle_timer = timer_read();
    }

    if (led_on && min_counter >= BACKLIGHT_TIMEOUT) {
        old_hsv = rgblight_get_hsv();
        rgblight_sethsv_noeeprom(0,0,0);
        rgblight_disable_noeeprom();
        led_on = false;
        min_counter = 0;
    }
};
