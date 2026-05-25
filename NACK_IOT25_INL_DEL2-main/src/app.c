#include "app.h"
#include "config.h"

#include "uart.h"
#include "millis.h"
#include "shift_register.h"
#include "keypad.h"
#include "led.h"
#include "buzzer.h"
#include "servo.h"
#include "mfrc522.h"
#include "ds1307.h"

#include <util/delay.h>
#include <string.h>
#include <stdint.h>

#define CODE_LENGTH 4

static char entered_code[CODE_LENGTH + 1];
static unsigned char code_index = 0;

static const char correct_code[] = "1234";

static uint8_t rfid_mode = 0;

static void print_hex_digit(uint8_t value)
{
    if (value < 10)
    {
        uart_write_char('0' + value);
    }
    else
    {
        uart_write_char('A' + (value - 10));
    }
}

static void print_hex_byte(uint8_t value)
{
    print_hex_digit((value >> 4) & 0x0F);
    print_hex_digit(value & 0x0F);
}

static void print_two_digits(uint8_t value)
{
    uart_write_char('0' + (value / 10));
    uart_write_char('0' + (value % 10));
}

static void print_rtc_time(void)
{
    ds1307_time_t time;

    if (ds1307_get_time(&time) == 0)
    {
        uart_write_string("RTC time: ");
        print_two_digits(time.hours);
        uart_write_char(':');
        print_two_digits(time.minutes);
        uart_write_char(':');
        print_two_digits(time.seconds);
        uart_write_string("\n");
    }
    else
    {
        uart_write_string("RTC could not be read\n");
    }
}

static void blink_blue(void)
{
    led_all_off();
    blue_led_on();

    _delay_ms(80);

    blue_led_off();
    red_led_on();
}

static void locked_mode(void)
{
    led_all_off();
    red_led_on();
    servo_close();
}

static void access_granted(void)
{
    led_all_off();
    green_led_on();

    buzzer_quiet();
    servo_open();

    uart_write_string("Access granted\n");
    print_rtc_time();

    _delay_ms(3000);

    servo_close();

    led_all_off();
    red_led_on();
}

static void access_denied(void)
{
    led_all_off();
    red_led_on();

    buzzer_scream();

    uart_write_string("Access denied\n");

    _delay_ms(800);

    buzzer_quiet();
}

static void check_code(void)
{
    entered_code[CODE_LENGTH] = '\0';

    if (strcmp(entered_code, correct_code) == 0)
    {
        access_granted();
    }
    else
    {
        access_denied();
    }

    code_index = 0;
}

static void handle_keypad(void)
{
    char key = keypad_get_key_debounced();

    if (key == 0)
    {
        return;
    }

    uart_write_string("Key: ");
    uart_write_char(key);
    uart_write_string("\n");

    if (key >= '0' && key <= '9')
    {
        blink_blue();
    }

    if (key == 'A')
    {
        rfid_mode = 1;
        code_index = 0;
        uart_write_string("RFID mode active\n");
        return;
    }

    if (key == '*')
    {
        code_index = 0;
        rfid_mode = 0;
        uart_write_string("Code cleared\n");
        return;
    }

    if (key == '#')
    {
        if (code_index == CODE_LENGTH)
        {
            check_code();
        }
        else
        {
            access_denied();
            code_index = 0;
        }

        return;
    }

    if (key < '0' || key > '9')
    {
        return;
    }

    if (code_index < CODE_LENGTH)
    {
        entered_code[code_index] = key;
        code_index++;
    }

    if (code_index == CODE_LENGTH)
    {
        check_code();
    }
}

static void handle_rfid(void)
{
    uint8_t atqa[2];
    uint8_t atqa_len;
    mfrc522_uid_t uid;
    mfrc522_status_t status;

    if (rfid_mode == 0)
    {
        return;
    }

    status = mfrc522_request_a(atqa, &atqa_len);

    if (status != MFRC522_OK)
    {
        return;
    }

    uart_write_string("RFID card found\n");

    status = mfrc522_anticoll_select(&uid);

    if (status == MFRC522_OK)
    {
        uart_write_string("RFID UID: ");

        for (uint8_t i = 0; i < uid.size; i++)
        {
            print_hex_byte(uid.uid[i]);
            uart_write_char(' ');
        }

        uart_write_string("\n");
    }

    rfid_mode = 0;

    access_granted();
}

void app_init(void)
{
    millis_init();
    uart_init(UART_BAUDRATE);

    shift_register_init();
    led_init();
    keypad_init();
    buzzer_init();
    servo_init();
    ds1307_init();
    mfrc522_init();

    print_rtc_time();

    locked_mode();

    uart_write_string("System ready\n");
    uart_write_string("Code is 1234\n");
    uart_write_string("Press A for RFID\n");
}

void app_run(void)
{
    handle_keypad();
    handle_rfid();
}