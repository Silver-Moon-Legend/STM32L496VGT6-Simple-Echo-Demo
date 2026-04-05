# 简易回声demo Makefile

# Toolchain
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy

# 源文件
SRC_FILES = simple_echo_demo.c \
            Drivers/DFSDM/dfsdm_driver.c \
            Drivers/I2S/i2s_driver.c \
            Drivers/Power/power_manager.c

# 头文件路径
INC_FLAGS = -ICore/Inc \
            -IDrivers/DFSDM \
            -IDrivers/I2S \
            -IDrivers/Power

# 编译参数
CFLAGS = -mcpu=cortex-m4 \
         -mthumb \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -Os \
         -g \
         -std=c11 \
         $(INC_FLAGS) \
         -DSTM32L496xx

# 链接参数
LDFLAGS = -mcpu=cortex-m4 \
          -mthumb \
          -mfpu=fpv4-sp-d16 \
          -mfloat-abi=hard \
          -specs=nano.specs \
          -TSTM32L496VGTx_FLASH.ld

# 目标文件
OBJ_FILES = $(SRC_FILES:%.c=%.o)

# 默认目标
all: simple_echo_demo.bin

# 编译
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 链接
simple_echo_demo.elf: $(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@

# 二进制
simple_echo_demo.bin: simple_echo_demo.elf
	$(OBJCOPY) -O binary $< $@

# 清理
clean:
	rm -f *.o *.elf *.bin

# 烧录
flash:
	openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program simple_echo_demo.bin 0x08000000 verify reset exit"

# 调试
debug:
	openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "init; reset halt; program simple_echo_demo.bin 0x08000000 verify; reset"

.PHONY: all clean flash debug
