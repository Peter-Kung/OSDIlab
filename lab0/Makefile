ARCGCC := aarch64-linux-gnu-gcc -c
SOURCE := boot
ARCLINK := aarch64-linux-gnu-ld -T 
LINKER := linker.ld
LINKERFLAG := -o
KERNEL := kernel8
ARCOBJ := aarch64-linux-gnu-objcopy -O binary

all:  boot elf img

boot:
	$(ARCGCC) $(SOURCE).S

elf:
	$(ARCLINK) $(LINKER)  $(LINKERFLAG) kernel8.elf $(SOURCE).o

img:
	$(ARCOBJ) $(KERNEL).elf $(KERNEL).img

qemu:
	qemu-system-aarch64 -M raspi3 -kernel $(KERNEL).img -display none -d in_asm

clean:
	rm *.o *.elf *.img
