#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <vector>

using namespace std;

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

vector <uint8_t> to_bytes(mp_obj_t byte_array) {
    mp_obj_iter_buf_t iter_buf;
    mp_obj_t item, iterable = mp_getiter(byte_array, &iter_buf);

    vector <uint8_t> bytes;
    while ((item = mp_iternext(iterable)) != MP_OBJ_STOP_ITERATION) {
        bytes.push_back(mp_obj_get_int(item));
    }

    return bytes;
}

// Write the bytes to the pin at the specified frequency, big endian
mp_obj_t gpio_pulser_write(mp_obj_t freq, mp_obj_t byte_array) {
    if (gpio_pulser_pin < 0) {
        mp_raise_msg(&mp_type_RuntimeError, NOT_INITIALISED_MSG);
        return mp_const_none;
    }

    float interval_us = 1e6 / mp_obj_get_float(freq);
    auto bytes = to_bytes(byte_array);

    auto start = get_absolute_time();
    uint64_t s = 0;

    for (uint8_t byte: bytes) {
        for (int i = 7; i >= 0; i--) {
            bool bit = (byte >> i) & 0b1;

            busy_wait_until(delayed_by_us(start, interval_us * ++s));
            gpio_put(gpio_pulser_pin, bit);
        }
    }

    return mp_const_none;
}
}
