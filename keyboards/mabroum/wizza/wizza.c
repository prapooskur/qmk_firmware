#include "quantum.h"
#include "wizza.h"
#include "display.h"
#include "rgblight.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    {     4,     3,     2,     1,      0 },
    {     5,     6,     7,     8,      9 },
    {     13,    12,    11,    10,     14 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },

    {     15,   16,    17,    18,      19 },
    {     24,   23,    22,    21,      20 },
    {     29,    25,    26,   27,      28 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }

}, {
    {2,1},{25,0},{48,2},{63,10},{77,20},{72,31},{56,21},{40,13},{18,10},{0,12},{15,22},{32,24},{38,31},
    {51,44},{58,53},
    {164,53},{180,44},
    {185,31},{200,24},{217,22},{224,12},{204,10},{185,13},{169,21},{155,31},{160,20},{174,10},{189,2},{212,0},{237,1}
}, {
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4,
    1, 1, 1, 1,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4,
} };

#endif /* ifndef RGB_MATRIX_ENABLE */

#include "qp.h"
#include "qp_lvgl.h"

kb_runtime_config kb_state;

static painter_device_t display;

/* void kb_state_update(void) { */
/* #ifdef BACKLIGHT_ENABLE */
/*     if (is_keyboard_master()) { */
/*         // Modify allowed current limits */
/*         // Turn off the LCD if there's been no matrix activity */
/*         kb_state.lcd_power = (last_input_activity_elapsed() < 30000) ? 1 : 0; */
/*     } */
/* #endif [> ifdef BACKLIGHT_ENABLE <] */
/* } */

void keyboard_post_init_user(void) {
  /* debug_enable=true; */
  /* debug_matrix=false; */
  /* debug_keyboard=false; */
  /* debug_mouse=true; */

  /* setPinOutput(LCD_POWER_ENABLE_PIN); */
  /* writePinHigh(LCD_POWER_ENABLE_PIN); */
  if (is_keyboard_left()) {
    display = qp_st7789_make_spi_device(200, 320, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 8, 3);
    qp_set_viewport_offsets(display, 0, 34);
    qp_init(display, QP_ROTATION_270); // Initialise the display
    qp_power(display, true);
    qp_rect(display, 0, 0, 319, 171, 0, 0, 0, true);
  } else {
    display = qp_st7789_make_spi_device(200, 320, DISPLAY_CS_PIN_RIGHT, DISPLAY_DC_PIN_RIGHT, DISPLAY_RST_PIN_RIGHT, 8, 3);
    qp_set_viewport_offsets(display, 0, 34);
    qp_init(display, QP_ROTATION_270); // Initialise the display
    qp_power(display, true);
    qp_rect(display, 0, 0, 319, 171, 0, 0, 0, true);
  }

  if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
    wait_ms(50);
    display_init();
  }

  pointing_device_set_cpi_on_side(true, 800); //Set cpi on left side to a low value for slower scrolling.
  pointing_device_set_cpi_on_side(false, 800); //Set cpi on right side to a reasonable value for mousing.
}

void housekeeping_task_user(void) {
  /* #ifdef BACKLIGHT_ENABLE */
  /* kb_state_update(); */
  /* static bool lcd_on = false; */
  /* if (lcd_on != (bool)kb_state.lcd_power) { */
  /*     lcd_on = (bool)kb_state.lcd_power; */
  /*     qp_power(display, lcd_on); */
  /* } */
  /* if (kb_state.lcd_power) { */
  /*     backlight_level_noeeprom(3); */
  /*   } else { */
  /*     backlight_level_noeeprom(0); */
  /*   } */
  /* #endif [> ifdef BACKLIGHT_ <] */
  lvgl_event_triggers();
}

void board_init(void) {}
