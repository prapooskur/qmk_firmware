# Things to refactor

- [X] Haptic
- [X] Trackball
- [X] Cirque
- [X] Custom Keys
- [X] repeat
- [X] one_shot
- [X] add ci/cd to build the firmware

```
void keyboard_pre_init_kb(void) {
    // Ensures that GP26 through GP29 are initialized as digital inputs (as
    // opposed to analog inputs).  These GPIOs are shared with A0 through A3,
    // respectively.  On RP2040-B2 and later, the digital inputs are disabled by
    // default (see RP2040-E6).
    gpio_init(GP26);
    gpio_init(GP27);
    gpio_init(GP28);
    gpio_init(GP29);

    keyboard_pre_init_user();
}
```
