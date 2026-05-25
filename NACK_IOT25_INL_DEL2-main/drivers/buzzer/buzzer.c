#include "buzzer.h"
#include "pins.h"
#include <avr/io.h>

void buzzer_init(void)
{
    BUZZER_DDR |= (1 << BUZZER_PIN);

    TCCR2A = 0;
    TCCR2B = 0;

    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

void buzzer_scream(void)
{
    TCCR2A = 0;
    TCCR2B = 0;

    TCCR2A |= (1 << COM2B1);
    TCCR2A |= (1 << WGM21);
    TCCR2A |= (1 << WGM20);

    TCCR2B |= (1 << CS22);

    OCR2B = 128;
}

void buzzer_quiet(void)
{
    TCCR2A = 0;
    TCCR2B = 0;

    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}