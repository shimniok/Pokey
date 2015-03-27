
PROJ = ff

MCU = atmega168

PROGRAMMER = dragon_isp
PORT = usb
AVRDUDEFLAGS = -B 1

SRCS = \
$(PROJ).c \
I2C_master.c

OBJS=$(SRCS:.c=.o)

LIBDIR = -L/usr/local/libpololu-avr/
INCLUDES = -I/usr/local/libpololu-avr/
LDFLAGS = -Wl,-gc-sections -Wl,-relax $(LIBDIR) -lpololu_$(MCU) 
CFLAGS = -g -Wall -mcall-prologues -mmcu=$(MCU) -Os $(INCLUDES)

RM = rm -rf

# Add inputs and outputs from these tool invocations to the build variables
LSS += \
$(PROJ).lss \

MAP += \
$(PROJ).map

ELF += \
$(PROJ).elf

HEX += \
$(PROJ).hex \

EEP += \
$(PROJ).eep \

SIZEDUMMY += \
sizedummy \

# All Target
all: $(ELF) secondary-outputs

# Tool invocations
$(ELF): $(OBJS)
	avr-gcc -Wl,-Map,$(MAP) -mmcu=$(MCU) -o $(ELF) $(OBJS) $(LDFLAGS) 

$(LSS): $(ELF)
	@avr-objdump -h -S $(ELF) >$(LSS)

$(HEX): $(ELF)
	@avr-objcopy -R .eeprom -O ihex $(ELF) $@

$(EEP): $(ELF)
	@avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $(ELF) $(EEP)

sizedummy: $(ELF)
	@echo ' '
	@avr-size --format=berkeley -t $(ELF)

# Other Targets
clean:
	-$(RM) $(OBJS) $(EEP) $(HEX) $(ELF) $(LSS) $(MAP) $(SIZEDUMMY)

install: $(HEX)
	avrdude $(AVRDUDEFLAGS) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -v -U flash:w:$(HEX)

fuses:
	avrdude -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -v -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

secondary-outputs: $(LSS) $(HEX) $(EEP) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

.c.o:
	avr-gcc -c $(CFLAGS) -mmcu=$(MCU) $< -o $@

.cpp.o:
	avr-g++ -c $(CPPFLAGS) -mmcu=$(MCU) $< -o $@

