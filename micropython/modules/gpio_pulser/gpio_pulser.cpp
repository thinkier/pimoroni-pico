#include "hardware/gpio.h"

using namespace pimoroni;

int8_t gpio_pulser_pin = -1;

extern "C" {
#include "gpio_pulser.h"
#include "pimoroni_i2c.h"

#define NOT_INITIALISED_MSG     "GPIO Pulser: Not initialised. Call gpio_pulser.init(<gpio #>) first."

mp_obj_t gpio_pulser_init(mp_obj_t pin) {
    gpio_pulser_pin = mp_obj_get_int(pin);

    gpio_init(gpio_pulser_pin);
    gpio_set_dir(gpio_pulser_pin, GPIO_OUT);

    return mp_const_none;
}

// Write the bytes to the pin at the specified frequency, big endian
mp_obj_t gpio_pulser_write_bits(mp_obj_t freq, mp_obj_t byte_array) {
    if (gpio_pulser_pin < 0) {
        mp_raise_msg(&mp_type_RuntimeError, NOT_INITIALISED_MSG);
        return mp_const_none;
    }

    return mp_const_none;
}
}
