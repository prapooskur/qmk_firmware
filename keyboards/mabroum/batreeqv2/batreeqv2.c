#include "quantum.h"
#include "batreeqv2.h"
#include "display.h"

led_config_t g_led_config = { {
    {     32,     31,     30,     29,      4,      3,      2,      1 },
    {     25,     26,     27,     28,      5,      6,      7,      8 },
    { NO_LED,     23,     22,     21,     12,     11,     10, NO_LED },
    {     33,     24,     20,     19,     14,     13,      9,      0 },
    { NO_LED, NO_LED,     18,     17,     16,     15, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
    {2,1},{25,0},{48,2},{63,10},{77,20},{72,31},{56,21},{40,13},{18,10},{0,12},{15,22},{32,24},{38,31},
    {51,44},{58,53},
    {84,68},{102,69},{120,69},{138,68},
    {164,53},{180,44},
    {185,31},{200,24},{217,22},{224,12},{204,10},{185,13},{169,21},{155,31},{160,20},{174,10},{189,2},{212,0},{237,1}
}, {
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4,
    1, 1, 1, 1, 1, 1, 1, 1,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4,
} };

#include "qp.h"
#include "qp_lvgl.h"

kb_runtime_config kb_state;

static painter_device_t display;

/* void kb_state_update(void) { */
/*     if (is_keyboard_master()) { */
/*         // Modify allowed current limits */
/*         // Turn off the LCD if there's been no matrix activity */
/*         kb_state.lcd_power = (last_input_activity_elapsed() < 30000) ? 1 : 0; */
/*     } */
/* } */

void keyboard_post_init_user(void) {
  debug_enable=true;
  /* debug_matrix=false; */
  /* debug_keyboard=false; */
  /* debug_mouse=true; */

  /* setPinOutput(LCD_POWER_ENABLE_PIN); */
  /* writePinHigh(LCD_POWER_ENABLE_PIN); */
  display = qp_st7789_make_spi_device(200, 320, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 8, 3);
  qp_set_viewport_offsets(display, 0, 34);
  qp_init(display, QP_ROTATION_90); // Initialise the display
  qp_power(display, true);
  qp_rect(display, 0, 0, 319, 171, 0, 0, 0, true);

  if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
    wait_ms(50);
    display_init();
  }
}

void housekeeping_task_user(void) {
  /* kb_state_update(); */
  /* static bool lcd_on = false; */
  /* if (lcd_on != (bool)kb_state.lcd_power) { */
  /*     lcd_on = (bool)kb_state.lcd_power; */
  /*     qp_power(display, lcd_on); */
  /* } */
  lvgl_event_triggers();
}

void board_init(void) {}
