MCU     = atmega328p
F_CPU   = 16000000UL
TARGET  = app
BUILD_DIR = build

CC      = avr-gcc
OBJCOPY = avr-objcopy
SIZE    = avr-size
AVRDUDE = avrdude

PROGRAMMER = arduino
PORT       = COM3
BAUD       = 115200

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c11 \
         -Iinclude \
         -Ihal \
         -Isrc \
         -Idrivers/gpio \
         -Idrivers/uart \
         -Idrivers/millis \
         -Idrivers/spi \
         -Idrivers/i2c \
         -Idrivers/keypad \
         -Idrivers/mfrc522rfid \
         -Idrivers/shift_register \
         -Idrivers/led \
         -Idrivers/buzzer \
         -Idrivers/servo \
         -Idrivers/ds1307

SRCS = \
	src/main.c \
	src/app.c \
	drivers/gpio/gpio.c \
	drivers/uart/uart.c \
	drivers/uart/ring_buffer.c \
	drivers/millis/millis.c \
	drivers/spi/spi.c \
	drivers/i2c/twi.c \
	drivers/keypad/keypad.c \
	drivers/mfrc522rfid/mfrc522.c \
	drivers/shift_register/shift_register.c \
	drivers/led/led.c \
	drivers/buzzer/buzzer.c \
	drivers/servo/servo.c \
	drivers/ds1307/ds1307.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
ELF  = $(BUILD_DIR)/$(TARGET).elf
HEX  = $(BUILD_DIR)/$(TARGET).hex
MAP  = $(BUILD_DIR)/$(TARGET).map

all: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $<

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) -Wl,-Map=$(MAP) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(HEX)
	$(AVRDUDE) -c $(PROGRAMMER) -p m328p -P $(PORT) -b $(BAUD) -U flash:w:$(HEX):i

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

.PHONY: all clean flash