# wildcard is makefile syntax, it will show *.c
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

all: clean kernel8.img

boot: boot.S
	aarch64-linux-gnu-gcc $(CFLAGS) -c boot.S -o boot.o

%.o: %.c
	aarch64-linux-gnu-gcc $(CFLAGS) -c $< -o $@

# NOTE: qemu does not redirect UART1 to terminal by default, only UART0, so you have to use -serial null -serial stdio.
kernel8.img: boot $(OBJS)
	aarch64-linux-gnu-ld -nostdlib -nostartfiles boot.o $(OBJS) -T linker.ld -o kernel8.elf
	aarch64-linux-gnu-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o *.img >/dev/null 2>/dev/null || true

qemu: all
	qemu-system-aarch64  -M raspi3 -kernel kernel8.img -serial null -serial stdio
