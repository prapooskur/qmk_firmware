MCU_HELIOS = yes

ifeq ($(strip $(MCU_HELIOS)), yes)
   OPT_DEFS += -DMCU_HELIOS
endif

BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = software