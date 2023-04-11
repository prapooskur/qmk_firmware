CONVERT_TO = promicro_rp2040

FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
ENCODER_ENABLE = yes

SRC += matrix_74hc595_spi.c
QUANTUM_LIB_SRC += spi_master.c
CUSTOM_MATRIX = lite

POINTING_DEVICE_ENABLE = yes
CIRQUE_ENABLE = yes
# POINTING_DEVICE_DRIVER = pmw3360
# OPT_DEFS += -DFP_TRACKBALL_ENABLE
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi


HAPTIC_ENABLE = yes
HAPTIC_DRIVER += DRV2605L

COMBO_ENABLE = yes
ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
# SRC += oneshot.c
SRC += nshot_mod.c
VPATH += keyboards/gboards
