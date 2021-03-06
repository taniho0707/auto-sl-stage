SHELL = /bin/sh
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16
SPLDIR = /home/nonoho/Programs/STM32F4/STM32F4xx_DSP_StdPeriph_Lib
INCLUDE_DIRS =  -I ./ \
				-I $(SPLDIR)/Libraries \
				-I $(SPLDIR)/Libraries/STM32F4xx_StdPeriph_Driver/inc \
				-I $(SPLDIR)/Libraries/CMSIS/Device/ST/STM32F4xx/Include \
				-I $(SPLDIR)/Libraries/CMSIS/Include \
				-I $(TOOLDIR)../arm-none-eabi/include \
				-I $(TOOLDIR)../arm-none-eabi/include/c++/4.9.3
STARTUP_DIR = $(SPLDIR)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7
MPU_OPTS = -DSTM32F401xx
BOARD_DIR = -DHSE_VALUE=\(\(uint32_t\)8000000\) $(MPU_OPTS)
FIRMWARE_OPTS = -DUSE_STDPERIPH_DRIVER
COMPILE_OPTS = -Os -g3 -ffunction-sections -fpermissive -fdata-sections -funsigned-char -fno-rtti -fexceptions -Wall -std=c++11 -fmessage-length=0 $(INCLUDE_DIRS) $(BOARD_OPTS) $(FIRMWARE_OPTS) $(MPU_OPTS)

TOOLDIR = /usr/bin
CC = $(TOOLDIR)/arm-none-eabi-g++
CXX = $(CC)
AS = $(CC)
LD = $(CC)
AR = $(TOOLDIR)/arm-none-eabi-ar
OBJCOPY = $(TOOLDIR)/arm-none-eabi-objcopy
CFLAGS = $(COMPILE_OPTS) $(TARGET_ARCH)
CXXFLAGS = $(COMPILE_OPTS) $(TARGET_ARCH)
ASFLAGS = -x assembler-with-cpp -c $(TARGET_ARCH) $(COMPILE_OPTS)
LDFLAGS = -Wl,-lgcc,-lc,-lm,-lrdimon,--gc-sections,-Map=bin/main.map,-cref -T stm32_flash.ld $(INCLUDE_DIRS) -lm -lstdc++ -L $(TOOLDIR)/../arm-none-eabi/lib/thumb -L $(SPLDIR)/Libraries -nostartfiles --specs=nano.specs --specs=rdimon.specs -u _printf_float $(TARGET_ARCH)

.PHONY: all
all: libstm32f401xx startup bin/main.bin flash

bin/main.bin: $(patsubst %.c,%.o,$(wildcard *.c)) $(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(STARTUP_DIR)/startup_stm32f401xx.o $(SPLDIR)/Libraries/libstm32f401xx.a
	$(LD) $(LDFLAGS) $(TARGET_ARCH) $^ -o bin/main.elf
	$(OBJCOPY) -O binary bin/main.elf bin/main.bin
	etags *.[ch]

LIB_OBJS = $(sort \
 $(patsubst %.c,%.o,$(wildcard $(SPLDIR)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c)))

libstm32f401xx: $(LIB_OBJS)
	$(AR) cr $(SPLDIR)/Libraries/libstm32f401xx.a $(LIB_OBJS)

startup:
	$(AS) -o $(STARTUP_DIR)/startup_stm32f401xx.o $(ASFLAGS) $(STARTUP_DIR)/startup_stm32f401xx.s

$(LIB_OBJS): \
 $(wildcard $(SPLDIR)/Libraries/STM32F4xx_StdPeriph_Driver/inc/*.h) \
 $(wildcard $(SPLDIR)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.c) \

.PHONY: clean
clean:
	rm -rf *.o *.s bin/* *\~

.PHONY: debug
debug:
	python2 write_main.py
	gtkterm

.PHONY: flash
flash:
	python2 write_main.py

