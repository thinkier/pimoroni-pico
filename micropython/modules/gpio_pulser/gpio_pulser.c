#include "gpio_pulser.h"

/***** Constants *****/


////////////////////////////////////////////////////////////////////////////////////////////////////
// GPIO Pulser Module
////////////////////////////////////////////////////////////////////////////////////////////////////

/***** Module Functions *****/
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gpio_pulser_init_obj, gpio_pulser_init);

STATIC MP_DEFINE_CONST_FUN_OBJ_2(gpio_pulser_write_obj, gpio_pulser_write);

/***** Globals Table *****/
STATIC const mp_map_elem_t gpio_pulser_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gpio_pulser) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&gpio_pulser_init_obj) },

    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&gpio_pulser_write_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mp_module_gpio_pulser_globals, gpio_pulser_globals_table);

/***** Module Definition *****/
const mp_obj_module_t gpio_pulser_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_gpio_pulser_globals,
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#if MICROPY_VERSION <= 70144
MP_REGISTER_MODULE(MP_QSTR_gpio_pulser, gpio_pulser_user_cmodule, MODULE_GPIO_PULSER_ENABLED);
#else
MP_REGISTER_MODULE(MP_QSTR_gpio_pulser, gpio_pulser_user_cmodule);
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
