#include "pico/stdlib.h"
#include "hardware/gpio.h"

int8_t gpio_pulser_pin = -1;

extern "C" {
#include "gpio_pulser.h"

#define NOT_INITIALISED_MSG     "GPIO Pulser: Not initialised. Call gpio_pulser.init(<gpio #>) first."

mp_obj_t gpio_pulser_init(mp_obj_t pin) {
    gpio_pulser_pin = mp_obj_get_int(pin);

    gpio_init(gpio_pulser_pin);
    gpio_set_dir(gpio_pulser_pin, GPIO_OUT);

    return mp_const_none;
}

// Write the bytes to the pin at the specified frequency, big endian
mp_obj_t gpio_pulser_write(mp_obj_t freq, mp_obj_t byte_array) {
    if (gpio_pulser_pin < 0) {
        mp_raise_msg(&mp_type_RuntimeError, NOT_INITIALISED_MSG);
        return mp_const_none;
    }

//    float f = mp_obj_get_float(freq);

    mp_obj_iter_buf_t iter_buf;
    mp_obj_t item, iterable = mp_getiter(byte_array, &iter_buf);

    auto start = get_absolute_time();
    auto delta_max = 0;
    while ((item = mp_iternext(iterable)) != MP_OBJ_STOP_ITERATION) {
        // do something with the item just retrieved
        auto delta = absolute_time_diff_us(start, get_absolute_time());
        if (delta > delta_max) {
            delta_max = delta;
        }
        start = get_absolute_time();
    }

    return mp_obj_new_int(delta_max);
}
}
