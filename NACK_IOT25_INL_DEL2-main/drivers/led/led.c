#include "led.h"
#include "shift_register.h"
#include "pins.h"

void led_init(void)
{
    led_all_off();
}

void red_led_on(void)
{
    shift_register_set_bit(RED_LED_BIT);
}

void red_led_off(void)
{
    shift_register_clear_bit(RED_LED_BIT);
}

void green_led_on(void)
{
    shift_register_set_bit(GREEN_LED_BIT);
}

void green_led_off(void)
{
    shift_register_clear_bit(GREEN_LED_BIT);
}

void blue_led_on(void)
{
    shift_register_set_bit(BLUE_LED_BIT);
}

void blue_led_off(void)
{
    shift_register_clear_bit(BLUE_LED_BIT);
}

void led_all_off(void)
{
    red_led_off();
    green_led_off();
    blue_led_off();
}