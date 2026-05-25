#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
} ds1307_time_t;

void ds1307_init(void);
uint8_t ds1307_get_time(ds1307_time_t *time);

#endif