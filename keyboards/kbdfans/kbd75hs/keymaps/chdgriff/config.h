#ifdef RGBLIGHT_DEFAULT_MODE
  #undef RGBLIGHT_DEFAULT_MODE
#endif

#ifdef RGBLIGHT_DEFAULT_HUE
  #undef RGBLIGHT_DEFAULT_HUE
#endif

#ifdef RGBLIGHT_DEFAULT_SAT
  #undef RGBLIGHT_DEFAULT_SAT
#endif

#ifdef RGBLIGHT_DEFAULT_VAL
  #undef RGBLIGHT_DEFAULT_VAL
#endif

#ifdef RGBLIGHT_LIMIT_VAL
  #undef RGBLIGHT_LIMIT_VAL
#endif

#define RGBLIGHT_DEFAULT_MODE       (RGBLIGHT_MODE_TWINKLE + 1)
#define RGBLIGHT_DEFAULT_HUE        163
#define RGBLIGHT_DEFAULT_SAT        245
#define RGBLIGHT_DEFAULT_VAL        230
#define RGBLIGHT_LIMIT_VAL          242

#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define USB_POLLING_INTERVAL_MS     1

#define RGB_DISABLE_TIMEOUT 30000 // milliseconds
#define RGB_DISABLE_WHEN_USB_SUSPENDED 1
