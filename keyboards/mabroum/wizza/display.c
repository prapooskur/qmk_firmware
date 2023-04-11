#include "display.h"
#include "quantum.h"
#include "keyboards/mabroum/mab_pointing.h"
#include "layers.h"
#include <ctype.h>

lv_obj_t * mbox1;
lv_obj_t * mbox1_title;
lv_obj_t * mbox1_text;
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1_Label_CPI;
lv_obj_t * ui_Screen1_deflayer;
lv_obj_t * ui_Screen1_Label_POINTING_MODE;
lv_obj_t * ui_Screen1_Label_RGB;
lv_obj_t * ui_Screen1_layout;
lv_obj_t * ui_Screen1_Label_ALTMOD;
lv_obj_t * ui_Screen1_Label_CMDMOD;
lv_obj_t * ui_Screen1_Label_SHIFTMOD;
lv_obj_t * ui_Screen1_Label_CTRLMOD;
lv_obj_t * ui_Layer_Indicator;
lv_obj_t * ui_Screen1_deflayer_list;

lv_obj_t * ui_Screen2;
lv_obj_t * ui_Image1;

#define MODS_SHIFT ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)
#define MODS_CTRL  ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL)
#define MODS_ALT   ((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT)
#define MODS_GUI   ((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI)

uint8_t USER_EVENT_CPI_UPDATE = 0;
uint8_t USER_EVENT_ACTIVE_LAYER_CHANGE = 1;
uint8_t USER_EVENT_CAPS_WORD_UPDATE = 2;
uint8_t USER_EVENT_POINTING_MODE_UPDATE = 5;
uint8_t USER_EVENT_RGBMODE_UPDATE = 6;
uint8_t USER_EVENT_ALTMOD = 7;
uint8_t USER_EVENT_CMDMOD = 8;
uint8_t USER_EVENT_SHIFTMOD = 9;
uint8_t USER_EVENT_CTRLMOD = 10;

void ui_active_layer_change(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_ACTIVE_LAYER_CHANGE) {
        switch (get_highest_layer(layer_state)) {
            case NAV:
                lv_img_set_src(ui_Layer_Indicator, &tools);
                break;
            case SYM:
                lv_img_set_src(ui_Layer_Indicator, &hash);
                 break;
            default:
                if (keymap_config.swap_lctl_lgui) {
                  lv_img_set_src(ui_Layer_Indicator, &apple);
                } else {
                  lv_img_set_src(ui_Layer_Indicator, &window);
                }
                break;
        }
  }
}

void set_cpi_text_value(lv_obj_t* lbl) {
    if (lv_obj_is_valid(lbl)) {
        char buf[11];
        snprintf(buf, sizeof(buf), "CPI: %d", (int)qmk_lv_get_cpi());
        lv_label_set_text(lbl, buf);
    }
}


//----------------------------------------------------------
// RGB Matrix naming
#ifdef RGB_MATRIX_ENABLE

extern rgb_config_t rgb_matrix_config;

#if defined(RGB_MATRIX_ENABLE)
#    include <rgb_matrix.h>

#    if defined(RGB_MATRIX_EFFECT)
#        undef RGB_MATRIX_EFFECT
#    endif // defined(RGB_MATRIX_EFFECT)

#    define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
};

#    define RGB_MATRIX_EFFECT(x)    \
        case RGB_MATRIX_EFFECT_##x: \
            return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
        default:
            return "UNKNOWN";
    }
}
#endif // defined(RGB_MATRIX_ENABLE)


void set_rgbmode_text_value(lv_obj_t* lbl) {
    char buf[32];
    if (!rgb_matrix_config.enable) {
        sprintf(buf, "RGB: OFF");
    }
    else {
        uint8_t curr_effect = rgb_matrix_config.mode;
        if (lv_obj_is_valid(lbl)) {
            snprintf(buf, sizeof(buf), "RGB: %s", rgb_matrix_name(curr_effect));
            for (int i = 5; i < sizeof(buf); ++i) {
                if (buf[i] == 0)
                    break;
                else if (buf[i] == '_')
                    buf[i] = ' ';
                else if (buf[i - 1] == ' ')
                    buf[i] = toupper(buf[i]);
                else if (buf[i - 1] != ' ')
                    buf[i] = tolower(buf[i]);
            }
        }
    }
    lv_label_set_text(lbl, buf);
}

void ui_render_rgbmode(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_RGBMODE_UPDATE) {
         set_rgbmode_text_value(ui_Screen1_Label_RGB);
    }
}

#endif /* ifdef RGB_MATRIX_ENABLE */

void ui_render_altmod(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_ALTMOD) {
        if (MODS_ALT) {
          lv_obj_clear_flag(ui_Screen1_Label_ALTMOD, LV_OBJ_FLAG_HIDDEN);
        }
        else {
          lv_obj_add_flag(ui_Screen1_Label_ALTMOD, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void ui_render_cmdmod(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_CMDMOD) {
        if (MODS_GUI) {
          lv_obj_clear_flag(ui_Screen1_Label_CMDMOD, LV_OBJ_FLAG_HIDDEN);
        }
        else {
          lv_obj_add_flag(ui_Screen1_Label_CMDMOD, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void ui_render_shiftmod(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_SHIFTMOD) {
        if (MODS_SHIFT) {
          lv_obj_clear_flag(ui_Screen1_Label_SHIFTMOD, LV_OBJ_FLAG_HIDDEN);
        }
        else {
          lv_obj_add_flag(ui_Screen1_Label_SHIFTMOD, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void ui_render_ctrlmod(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_CTRLMOD) {
        if (MODS_CTRL) {
          lv_obj_clear_flag(ui_Screen1_Label_CTRLMOD, LV_OBJ_FLAG_HIDDEN);
        }
        else {
          lv_obj_add_flag(ui_Screen1_Label_CTRLMOD, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void set_pointing_mode_text_value(lv_obj_t* lbl) {
    if (lv_obj_is_valid(lbl)) {
        char buf[16];
    switch (get_toggled_pointing_mode_id()) {
        case 1:
          snprintf(buf, sizeof(buf), "PM: Sniping");
          break;
        case 2:
          snprintf(buf, sizeof(buf), "PM: Drag");
          break;
        case 3:
          snprintf(buf, sizeof(buf), "PM: Caret");
          break;
        case 5:
          snprintf(buf, sizeof(buf), "PM: Volume");
          break;
        default:
          snprintf(buf, sizeof(buf), "PM: Normal");
          break;
    }
    lv_label_set_text(lbl, buf);
    }
}

void ui_render_cpi(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_CPI_UPDATE) {
         set_cpi_text_value(ui_Screen1_Label_CPI);
    }
}

void ui_render_pointing_mode(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_POINTING_MODE_UPDATE) {
         set_pointing_mode_text_value(ui_Screen1_Label_POINTING_MODE);
    }
}

void ui_render_layout(lv_event_t * e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  if(event_code == USER_EVENT_LAYOUT_UPDATE) {
    char buf[11];
    switch (get_highest_layer(default_layer_state)) {
        case HDN:
            snprintf(buf, sizeof(buf), "HDN");
            break;
        case APT:
            snprintf(buf, sizeof(buf), "APT");
             break;
    }
  lv_label_set_text(ui_Screen1_layout, buf);
  }
}

uint16_t qmk_lv_get_cpi(void) {
    uint16_t cpi = 0;
    cpi = get_pointing_mode_id() == 1 ? mab_get_pointer_sniping_dpi() : mab_get_pointer_default_dpi();
    return cpi;
}


void lvgl_event_triggers(void) {
    static uint16_t last_cpi   = 0xFFFF;
    uint16_t curr_cpi   = get_pointing_mode_id() == 1 ? mab_get_pointer_sniping_dpi() : mab_get_pointer_default_dpi();
    bool cpi_redraw = false;
    if (last_cpi != curr_cpi) {
        last_cpi   = curr_cpi;
        cpi_redraw = true;
    }
    if (cpi_redraw) {
        lv_event_send(ui_Screen1_Label_CPI, USER_EVENT_CPI_UPDATE, NULL);
    }

    static uint16_t last_pm   = 0xFFFF;
    uint16_t curr_pm   = get_toggled_pointing_mode_id();
    bool pm_redraw = false;
    if (last_pm != curr_pm) {
        last_pm   = curr_pm;
        pm_redraw = true;
    }
    if (pm_redraw) {
        lv_event_send(ui_Screen1_Label_POINTING_MODE, USER_EVENT_POINTING_MODE_UPDATE, NULL);
    }

    static uint32_t last_dl_state   = 0;
    bool dl_state_redraw = false;
    if (last_dl_state != default_layer_state) {
        last_dl_state   = default_layer_state;
        dl_state_redraw = true;
    }
    if (dl_state_redraw) {
        lv_event_send(ui_Screen1_layout, USER_EVENT_LAYOUT_UPDATE, NULL);
    }
    bool layer_state_redraw = false;

    static uint32_t last_layer_state   = 0;
    if (last_layer_state != layer_state) {
        last_layer_state   = layer_state;
        layer_state_redraw = true;
    }
    if (layer_state_redraw) {
        lv_event_send(ui_Layer_Indicator, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);
    }

#ifdef RGB_MATRIX_ENABLE
    bool            rgb_effect_redraw = false;
    static uint16_t last_effect       = 0xFFFF;
    uint8_t         curr_effect       = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect       = curr_effect;
        rgb_effect_redraw = true;
    }
    static uint16_t last_rgb_status   = 0xFFFF;
    uint8_t  curr_rgb_status  = rgb_matrix_config.enable;
    if (last_rgb_status  != curr_rgb_status) {
        last_rgb_status   = curr_rgb_status;
        rgb_effect_redraw = true;
    }
    if (rgb_effect_redraw) {
        lv_event_send(ui_Screen1_Label_RGB, USER_EVENT_RGBMODE_UPDATE, NULL);
    }
#endif /* ifdef RGB_MATRIX_ENABLE */

    bool altmod_state_redraw = false;
    static uint32_t last_altmod_state   = 0;
    if (last_altmod_state != MODS_ALT) {
        last_altmod_state = MODS_ALT;
        altmod_state_redraw = true;
    }
    if (altmod_state_redraw) {
      lv_event_send(ui_Screen1_Label_ALTMOD, USER_EVENT_ALTMOD, NULL);
    }

    bool cmdmod_state_redraw = false;
    static uint32_t last_cmdmod_state   = 0;
    if (last_cmdmod_state != MODS_GUI) {
        last_cmdmod_state = MODS_GUI;
        cmdmod_state_redraw = true;
    }
    if (cmdmod_state_redraw) {
      lv_event_send(ui_Screen1_Label_CMDMOD, USER_EVENT_CMDMOD, NULL);
    }

    bool shiftmod_state_redraw = false;
    static uint32_t last_shiftmod_state   = 0;
    if (last_shiftmod_state != MODS_SHIFT) {
        last_shiftmod_state = MODS_SHIFT;
        shiftmod_state_redraw = true;
    }
    if (shiftmod_state_redraw) {
      lv_event_send(ui_Screen1_Label_SHIFTMOD, USER_EVENT_SHIFTMOD, NULL);
    }

    bool ctrlmod_state_redraw = false;
    static uint32_t last_ctrlmod_state   = 0;
    if (last_ctrlmod_state != MODS_CTRL) {
        last_ctrlmod_state = MODS_CTRL;
        ctrlmod_state_redraw = true;
    }
    if (ctrlmod_state_redraw) {
      lv_event_send(ui_Screen1_Label_CTRLMOD, USER_EVENT_CTRLMOD, NULL);
    }
}

void ui_Screen1_screen_init(void) {

    ui_Screen1 = lv_obj_create(NULL);

    ui_Layer_Indicator = lv_img_create(ui_Screen1);
    lv_obj_add_event_cb(ui_Layer_Indicator, ui_active_layer_change, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);
    lv_obj_set_width(ui_Layer_Indicator, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Layer_Indicator, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Layer_Indicator, 25);
    lv_obj_set_y(ui_Layer_Indicator, -25);
    lv_obj_set_align(ui_Layer_Indicator, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Layer_Indicator, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Layer_Indicator, LV_OBJ_FLAG_SCROLLABLE);
    lv_event_send(ui_Layer_Indicator, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);

    ui_Screen1_Label_CPI = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_CPI, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label_CPI, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label_CPI, 120);
    lv_obj_set_y(ui_Screen1_Label_CPI, 25);
    lv_obj_set_style_text_font(ui_Screen1_Label_CPI, &rb_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Label_CPI, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_Screen1_Label_CPI, ui_render_cpi, USER_EVENT_CPI_UPDATE, NULL);

    ui_Screen1_Label_POINTING_MODE = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_POINTING_MODE, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label_POINTING_MODE, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label_POINTING_MODE, 120);
    lv_obj_set_y(ui_Screen1_Label_POINTING_MODE, 65);
    lv_obj_set_style_text_font(ui_Screen1_Label_POINTING_MODE, &rb_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Label_POINTING_MODE, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_Screen1_Label_POINTING_MODE, ui_render_pointing_mode, USER_EVENT_POINTING_MODE_UPDATE, NULL);

#ifdef RGB_MATRIX_ENABLE
    ui_Screen1_Label_RGB = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_RGB, 150);
    lv_obj_set_style_text_font(ui_Screen1_Label_RGB, &rb_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_x(ui_Screen1_Label_RGB, 120);
    lv_obj_set_y(ui_Screen1_Label_RGB, 105);
    lv_label_set_text(ui_Screen1_Label_RGB, "RGB");
    lv_obj_add_event_cb(ui_Screen1_Label_RGB, ui_render_rgbmode, USER_EVENT_RGBMODE_UPDATE, NULL);
#endif /* ifdef RGB_MATRIX_ENABLE */

    ui_Screen1_layout = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_layout , 100);
    lv_obj_set_style_text_font(ui_Screen1_layout, &rb_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_x(ui_Screen1_layout, 40);
    lv_obj_set_y(ui_Screen1_layout, 95);
    lv_obj_add_event_cb(ui_Screen1_layout, ui_render_layout, USER_EVENT_LAYOUT_UPDATE, NULL);
    lv_event_send(ui_Screen1_layout, USER_EVENT_LAYOUT_UPDATE, NULL);

    ui_Screen1_Label_ALTMOD = lv_img_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_ALTMOD, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Screen1_Label_ALTMOD, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Screen1_Label_ALTMOD, -20);
    lv_obj_set_y(ui_Screen1_Label_ALTMOD, -50);
    lv_obj_set_align(ui_Screen1_Label_ALTMOD, LV_ALIGN_RIGHT_MID);
    lv_img_set_src(ui_Screen1_Label_ALTMOD, &alt);
    lv_obj_add_event_cb(ui_Screen1_Label_ALTMOD, ui_render_altmod, USER_EVENT_ALTMOD, NULL);
    lv_event_send(ui_Screen1_Label_ALTMOD, USER_EVENT_ALTMOD, NULL);

    ui_Screen1_Label_CMDMOD = lv_img_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_CMDMOD, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Screen1_Label_CMDMOD, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Screen1_Label_CMDMOD, -20);
    lv_obj_set_y(ui_Screen1_Label_CMDMOD, -23);
    lv_obj_set_align(ui_Screen1_Label_CMDMOD, LV_ALIGN_RIGHT_MID);
    lv_img_set_src(ui_Screen1_Label_CMDMOD, &cmd);
    lv_obj_add_event_cb(ui_Screen1_Label_CMDMOD, ui_render_cmdmod, USER_EVENT_CMDMOD, NULL);
    lv_event_send(ui_Screen1_Label_CMDMOD, USER_EVENT_CMDMOD, NULL);

    ui_Screen1_Label_SHIFTMOD = lv_img_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_SHIFTMOD, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Screen1_Label_SHIFTMOD, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Screen1_Label_SHIFTMOD, -20);
    lv_obj_set_y(ui_Screen1_Label_SHIFTMOD, 4);
    lv_obj_set_align(ui_Screen1_Label_SHIFTMOD, LV_ALIGN_RIGHT_MID);
    lv_img_set_src(ui_Screen1_Label_SHIFTMOD, &shift);
    lv_obj_add_event_cb(ui_Screen1_Label_SHIFTMOD, ui_render_shiftmod, USER_EVENT_SHIFTMOD, NULL);
    lv_event_send(ui_Screen1_Label_SHIFTMOD, USER_EVENT_SHIFTMOD, NULL);

    ui_Screen1_Label_CTRLMOD = lv_img_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_CTRLMOD, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Screen1_Label_CTRLMOD, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Screen1_Label_CTRLMOD, -20);
    lv_obj_set_y(ui_Screen1_Label_CTRLMOD, 31);
    lv_obj_set_align(ui_Screen1_Label_CTRLMOD, LV_ALIGN_RIGHT_MID);
    lv_img_set_src(ui_Screen1_Label_CTRLMOD, &caret);
    lv_obj_add_event_cb(ui_Screen1_Label_CTRLMOD, ui_render_ctrlmod, USER_EVENT_CTRLMOD, NULL);
    lv_event_send(ui_Screen1_Label_CTRLMOD, USER_EVENT_CTRLMOD, NULL);
}

void ui_Screen2_screen_init(void) {
    ui_Screen2 = lv_obj_create(NULL);
    ui_Image1 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Image1, &cowboy_bebop); // set image on startup
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Image1, 25);
    lv_obj_set_align(ui_Image1, LV_ALIGN_LEFT_MID);
}

void display_init(void) {
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();

    if (is_keyboard_left()) {
        lv_disp_load_scr(ui_Screen2);
    }
    if (!is_keyboard_left()) {
        lv_disp_load_scr(ui_Screen1);
    }
}
