POINTING_DEVICE_ENABLE = yes
CIRQUE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration

COMBO_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
SRC += oneshot.c
VPATH += keyboards/gboards
