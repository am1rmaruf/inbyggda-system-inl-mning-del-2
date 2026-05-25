#include "servo.h"
#include "pins.h"
#include <avr/io.h>

void servo_init(void)
{
    SERVO_DDR |= (1 << SERVO_PIN);

    TCCR1A = 0;
    TCCR1B = 0;

    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << WGM11);

    TCCR1B |= (1 << WGM13);
    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS11);

    ICR1 = 39999;

    servo_close();
}

void servo_open(void)
{
    OCR1A = 4000;
}

void servo_close(void)
{
    OCR1A = 2000;
}