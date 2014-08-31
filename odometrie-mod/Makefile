TARGET = odometrie-mod

ifndef PLATFORM
PLATFORM = m16-15
LIBDIR = /opt/nibobeelib/lib
HEXDIR = /opt/nibobeelib/hex
else
LIBDIR = /opt/nibobeelib/lib/$(PLATFORM)
HEXDIR = /opt/nibobeelib/hex/$(PLATFORM)
endif

include /opt/nibobeelib/src/config-$(PLATFORM).mk
include /opt/nibobeelib/src/version.mk

OBJS = \
   odometrie-mod.o \

# AVR compiler setup
PREFIX =
CC = $(PREFIX)avr-gcc
OBJCOPY = $(PREFIX)avr-objcopy
OBJDUMP = $(PREFIX)avr-objdump

# AVR compiler and linker flags
CFLAGS += -Os -ffunction-sections -DAVR -I /opt/nibobeelib/src -mmcu=$(DEVICE) -std=c99
CFLAGS += -DF_CPU=$(F_CPU) -DVERSION="\"$(VERSION)\"" -D_NIBOBEE_
CLDFLAGS += -v -mmcu=$(DEVICE) -L$(LIBDIR)

# MATH lib and Stdlib
#MATH = -lm -Wl,-u,vfprintf -lprintf_flt
MATH = -lm

# Nibobee libraries
LIBS = /opt/nibobeelib/lib/libnibobee_base.a /opt/nibobeelib/lib/libnibobee_utils.a

#            1  means not!
# 7 BODLEVEL 1  Brown-out Detector trigger level
# 6 BODEN 6  1  Brown-out Detector enable
# 5 SUT1 5   1  Select start-up time
# 4 SUT0 4   0  Select start-up time
# 3 CKSEL3   1  Select Clock source
# 2 CKSEL2   1  Select Clock source
# 1 CKSEL1   1  Select Clock source
# 0 CKSEL0   1  Select Clock source
LFUSE = 0xef

#            1  means not!
# 7 OCDEN    1  Enable OCD
# 6 JTAGEN   1  Enable JTAG
# 5 SPIEN    0  Enable SPI Serial Program and Data Downloading
# 4 CKOPT    1  Oscillator options
# 3 EESAVE   0  EEPROM memory is preserved through the Chip Erase
# 2 BOOTSZ1  0  Select Boot Size
# 1 BOOTSZ0  0  Select Boot Size
# 0 BOOTRST  1  Select reset vector
HFUSE = 0xd1

PROGRAMMER = usbasp

# build intel hex files
all: $(TARGET).hex $(TARGET).xhex

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

%.d:%.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's#\($*\)\.o[ :]*#\1.o $@ : #g' > $@ ; \
	[ -s $@ ] || rm -f $@

# avr specific entries
%.elf: $(OBJS) $(NIBO_OBJS)
	$(CC) $(CLDFLAGS) -o $@ $(OBJS) $(LIBS) $(MATH)
	avr-size -A $(TARGET).elf

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(TARGET).lss: $(TARGET).elf
	avr-objdump -h -S $(TARGET).elf >$(TARGET).lss

%.xhex: %.hex
	@echo "building $@"
	@echo >$@ "<?xml version=\"1.0\"?>"
	@echo >>$@ "<xhex version=\"1.0\">"
	@echo >>$@ "<platform>NIBObee-$(PLATFORM)</platform>"
	@echo >>$@ "<programmer type=\"$(PROGRAMMER)\"/>"
	@echo >>$@ "<device part=\"$(DEVICE)\" erase=\"yes\">"
	@echo >>$@ "<segment id=\"hfuse\" verify=\"yes\"><data>$(HFUSE)</data></segment>"
	@echo >>$@ "<segment id=\"lfuse\" verify=\"yes\"><data>$(LFUSE)</data></segment>"
	@echo >>$@ "<segment id=\"flash\" format=\"ihex\">"
	@cat >>$@ $<
	@echo >>$@ "</segment>"
	@echo >>$@ "</device>"
	@echo >>$@ "</xhex>"

lss: $(TARGET).lss


avrdude: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p m16 -B 10 -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m
	avrdude -c $(PROGRAMMER) -p m16 -B 2 -U flash:w:$(TARGET).hex

clean:
	rm -f *.d *.o *~ *.elf $(TARGET).hex $(TARGET).lss $(TARGET).xhex $(NIBO_OBJS)

tarball: $(TARGET).hex $(TARGET).xhex
	@mkdir -p $(HEXDIR)
	cp $^ $(HEXDIR)

include $(OBJS:.o=.d)

.PHONY: clean
.SECONDARY: $(TARGET).hex $(OBJS) $(LOBJS)
