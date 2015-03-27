
PROJ = demo

DEVICE = atmega168
MCU = atmega168
AVRDUDE_DEVICE = m168
DEVICE ?= atmega168
MCU ?= atmega168
AVRDUDE_DEVICE ?= m168

CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) $(DEVICE_SPECIFIC_CFLAGS) -Os -I/usr/local/libpololu-avr/
CC=avr-gcc
OBJ2HEX=avr-objcopy 
LDFLAGS=-Wl,-gc-sections -lpololu_$(DEVICE) -Wl,-relax -L/usr/local/libpololu-avr/

PORT ?= /dev/ttyACM0
AVRDUDE=avrdude

OBJECT_FILES=$(PROJ).o

all: $(PROJ).hex

clean:
	rm -f *.o *.hex *.obj *.hex

%.hex: %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

$(PROJ).o: $(PROJ).c

%.obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

program: $(PROJ).hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c dragon_isp -P usb -U flash:w:$(PROJ).hex
