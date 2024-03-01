CC = i386-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -Wall -masm=intel -m32 -lgcc # -O3

all: horizonos.iso

horizonos.iso: src/kernel/kernelentry.asm Makefile clean
	echo "Building HorizonOS..."
	echo "  Building asm files..."
	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	nasm -f elf -o "bin/gdt.o" "src/kernel/GDT/gdt.asm"
	nasm -f elf -o "bin/idt.o" "src/kernel/IDT/idt.asm"
	echo "  Building C files..."
	echo
	$(CC) -c "src/kernel/kmain.c" -o "bin/kmain.o" $(CFLAGS)
	ld -m elf_i386 -T link.ld -o "bin/kernel.bin"
	echo "Installing GRUB..."
	echo
	mkdir -p iso/boot/grub
	cp bin/kernel.bin iso/boot/kernel.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o horizonos.iso iso

clean:
	rm -rf bin/*
	rm -rf iso