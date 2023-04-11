CONVERT_TO = kb2040

FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
ENCODER_ENABLE = yes

SRC += keyboards/mabroum/mab_haptic.c
SRC += keyboards/mabroum/mab_pointing.c

SRC += keyboards/mabroum/matrix_74hc595_spi.c
QUANTUM_LIB_SRC += spi_master.c
CUSTOM_MATRIX = lite

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360
OPT_DEFS += -DFP_TRACKBALL_ENABLE

HAPTIC_ENABLE = yes
HAPTIC_DRIVER += DRV2605L

COMBO_ENABLE = yes
MAGIC_ENABLE = yes

ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
SRC += nshot_mod.c \
       repeat.c \
       swapper.c
VPATH += keyboards/gboards
