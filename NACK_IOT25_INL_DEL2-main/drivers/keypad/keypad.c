#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "keypad.h"
#include "shift_register.h"
#include "pins.h"

static const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void keypad_init(void)
{
    KEYPAD_COL_DDR &= ~((1 << KEYPAD_COL1) |
                        (1 << KEYPAD_COL2) |
                        (1 << KEYPAD_COL3) |
                        (1 << KEYPAD_COL4));

    KEYPAD_COL_PORT |= (1 << KEYPAD_COL1) |
                       (1 << KEYPAD_COL2) |
                       (1 << KEYPAD_COL3) |
                       (1 << KEYPAD_COL4);

    shift_register_set_bit(ROW1_BIT);
    shift_register_set_bit(ROW2_BIT);
    shift_register_set_bit(ROW3_BIT);
    shift_register_set_bit(ROW4_BIT);
}

static void keypad_all_rows_high(void)
{
    shift_register_set_bit(ROW1_BIT);
    shift_register_set_bit(ROW2_BIT);
    shift_register_set_bit(ROW3_BIT);
    shift_register_set_bit(ROW4_BIT);
}

static void keypad_one_row_low(uint8_t row)
{
    keypad_all_rows_high();

    if (row == 0)
    {
        shift_register_clear_bit(ROW1_BIT);
    }
    else if (row == 1)
    {
        shift_register_clear_bit(ROW2_BIT);
    }
    else if (row == 2)
    {
        shift_register_clear_bit(ROW3_BIT);
    }
    else if (row == 3)
    {
        shift_register_clear_bit(ROW4_BIT);
    }
}

static uint8_t keypad_read_column(void)
{
    if (!(KEYPAD_COL_PIN & (1 << KEYPAD_COL1)))
    {
        return 0;
    }

    if (!(KEYPAD_COL_PIN & (1 << KEYPAD_COL2)))
    {
        return 1;
    }

    if (!(KEYPAD_COL_PIN & (1 << KEYPAD_COL3)))
    {
        return 2;
    }

    if (!(KEYPAD_COL_PIN & (1 << KEYPAD_COL4)))
    {
        return 3;
    }

    return 255;
}

char keypad_get_key(void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < 4; row++)
    {
        keypad_one_row_low(row);
        _delay_us(5);

        col = keypad_read_column();

        if (col != 255)
        {
            keypad_all_rows_high();
            return keypad_map[row][col];
        }
    }

    keypad_all_rows_high();
    return 0;
}

char keypad_get_key_debounced(void)
{
    char key = keypad_get_key();

    if (key != 0)
    {
        _delay_ms(20);

        if (key == keypad_get_key())
        {
            while (keypad_get_key() != 0)
            {
                _delay_ms(5);
            }

            return key;
        }
    }

    return 0;
}