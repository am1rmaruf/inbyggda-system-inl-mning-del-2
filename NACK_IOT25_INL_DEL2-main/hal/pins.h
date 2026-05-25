#ifndef PINS_H
#define PINS_H

#include <avr/io.h>

#define SHIFT_LATCH_DDR   DDRD
#define SHIFT_LATCH_PORT  PORTD
#define SHIFT_LATCH_PIN   PD2

#define BUZZER_DDR        DDRD
#define BUZZER_PORT       PORTD
#define BUZZER_PIN        PD3

#define KEYPAD_COL_DDR    DDRD
#define KEYPAD_COL_PORT   PORTD
#define KEYPAD_COL_PIN    PIND

#define KEYPAD_COL1       PD7
#define KEYPAD_COL2       PD6
#define KEYPAD_COL3       PD5
#define KEYPAD_COL4       PD4

#define SERVO_DDR         DDRB
#define SERVO_PIN         PB1

#define RFID_SS_DDR       DDRB
#define RFID_SS_PORT      PORTB
#define RFID_SS_PIN       PB2

#define RFID_RST_DDR      DDRB
#define RFID_RST_PORT     PORTB
#define RFID_RST_PIN      PB0

#define ROW1_BIT          0
#define ROW2_BIT          1
#define ROW3_BIT          2
#define ROW4_BIT          3

#define RED_LED_BIT       5
#define GREEN_LED_BIT     6
#define BLUE_LED_BIT      7

#endif