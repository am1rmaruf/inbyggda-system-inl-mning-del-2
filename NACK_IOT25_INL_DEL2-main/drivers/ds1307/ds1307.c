#include "ds1307.h"
#include "twi.h"

#define DS1307_ADDRESS 0x68

static uint8_t bcd_to_decimal(uint8_t value)
{
    return ((value >> 4) * 10) + (value & 0x0F);
}

void ds1307_init(void)
{
    twi_init(100000);
}

uint8_t ds1307_get_time(ds1307_time_t *time)
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;

    if (time == 0)
    {
        return 1;
    }

    if (twi_read_register(DS1307_ADDRESS, 0x00, &seconds) != TWI_OK)
    {
        return 1;
    }

    if (twi_read_register(DS1307_ADDRESS, 0x01, &minutes) != TWI_OK)
    {
        return 1;
    }

    if (twi_read_register(DS1307_ADDRESS, 0x02, &hours) != TWI_OK)
    {
        return 1;
    }

    time->seconds = bcd_to_decimal(seconds & 0x7F);
    time->minutes = bcd_to_decimal(minutes);
    time->hours = bcd_to_decimal(hours & 0x3F);

    return 0;
}