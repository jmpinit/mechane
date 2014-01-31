NAME := motor_module

ifeq ($(OS),Windows_NT)
S := \\
else
S := /
endif

SRCDIR := src
OBJDIR := obj
BINDIR := bin

HEX := $(BINDIR)$(S)$(NAME).hex
BIN := $(BINDIR)$(S)$(NAME).bin
OUT := $(OBJDIR)$(S)$(NAME).out
MAP := $(OBJDIR)$(S)$(NAME).map

SOURCES =	main.c \
			Serial.c \
			Motor.c \
			rfm12.c
INCLUDES = -Isrc$(S)inc -Ilibs
OBJECTS = $(patsubst %,$(OBJDIR)$(S)%,$(SOURCES:.c=.o))
MCU := atmega328p
MCU_AVRDUDE := atmega328p
MCU_SIMULATE := atmega328
MCU_FREQ := 8000000UL

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size -C --mcu=$(MCU)

CFLAGS := -Wall -pedantic -mmcu=$(MCU) -std=gnu99 -g -Os -DF_CPU=$(MCU_FREQ) -gstabs

all: $(HEX) $(BIN)

clean:
ifeq ($(OS),Windows_NT)
	del $(HEX) $(OUT) $(MAP) $(OBJECTS)
else
	rm $(HEX) $(OUT) $(MAP) $(OBJECTS)
endif

bootloader:
	sudo avrdude -F -V -v -c arduino -p $(MCU_AVRDUDE) -P /dev/ttyUSB0 -b 57600 -U flash:w:$(HEX)

usbtiny: $(HEX)
	sudo avrdude -y -c usbtiny -p $(MCU_AVRDUDE) -U flash:w:$(HEX)

sim: $(OUT) data/
	simulavr -V -d $(MCU_SIMULATE) -F $(MCU_FREQ) -W 0xC6,data/serial --file $(OBJDIR)/$(NAME).out

data/:
	mkdir data

$(HEX): $(OUT)
	$(OBJCOPY) -R .eeprom -O ihex $< $@

$(BIN): $(OUT)
	$(OBJCOPY) -R .eeprom -O binary $< $@

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ -Wl,-Map,$(MAP) $^
	@echo = = = = = = = = =
	$(SIZE) $@

$(OBJDIR)$(S)%.o: $(SRCDIR)$(S)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	
$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: all clean flash

