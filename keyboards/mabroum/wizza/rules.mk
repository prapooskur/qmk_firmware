SERIAL_DRIVER = vendor

FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches

SRC += haptic.c
SRC += pointing.c

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360
OPT_DEFS += -DFP_TRACKBALL_ENABLE

HAPTIC_DRIVER += DRV2605L

QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_LVGL_INTEGRATION = yes

#PER KEY RGB
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = vendor

COMBO_ENABLE = yes
CAPS_WORD_ENABLE = yes
MAGIC_ENABLE = yes

DEFERRED_EXEC_ENABLE             = yes
ENCODER_MAP_ENABLE               = yes

SRC += nshot_mod.c \
       repeat.c \
       swapper.c
VPATH += keyboards/gboards

SRC += assets/rb_24.c \
       assets/rb_18.c \
       assets/window.c \
			 assets/tools.c \
			 assets/hash.c \
			 assets/apple.c \
			 assets/cmd.c \
			 assets/shift.c \
			 assets/caret.c \
			 assets/alt.c \
			 assets/cowboy_bebop.c

SRC += display.c
