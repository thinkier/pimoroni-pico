// Include MicroPython API.
#include "py/runtime.h"
#include "py/objstr.h"

// Declare the functions we'll make available in Python
extern mp_obj_t gpio_pulser_init(mp_obj_t pin);

extern mp_obj_t gpio_pulser_write(mp_obj_t freq, mp_obj_t byte_array);
