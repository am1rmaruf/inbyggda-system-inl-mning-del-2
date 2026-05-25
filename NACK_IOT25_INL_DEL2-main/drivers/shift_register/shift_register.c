#include "shift_register.h"
#include "spi.h"
#include "gpio.h"
#include "pins.h"

static uint8_t shift_state = 0;

static void shift_register_update(void)
{
    gpio_pin_low(&SHIFT_LATCH_PORT, SHIFT_LATCH_PIN);
    spi_transfer(shift_state);
    gpio_pin_high(&SHIFT_LATCH_PORT, SHIFT_LATCH_PIN);
}

void shift_register_init(void)
{
    gpio_pin_output(&SHIFT_LATCH_DDR, SHIFT_LATCH_PIN);
    gpio_pin_high(&SHIFT_LATCH_PORT, SHIFT_LATCH_PIN);

    spi_init();

    shift_state = 0;
    shift_register_update();
}

void shift_register_write(uint8_t value)
{
    shift_state = value;
    shift_register_update();
}

void shift_register_set_bit(uint8_t bit)
{
    shift_state = shift_state | (1 << bit);
    shift_register_update();
}

void shift_register_clear_bit(uint8_t bit)
{
    shift_state = shift_state & ~(1 << bit);
    shift_register_update();
}