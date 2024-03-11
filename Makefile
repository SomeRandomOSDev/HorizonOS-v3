CC = i386-elf-gcc
CFLAGS = -std=gnu99 -nostdlib -lgcc -ffreestanding -Wall -masm=intel -m32 -O3

all: horizonos.iso

horizonos.iso: src/kernel/kernelentry.asm Makefile rmBin libc
	echo "Building HorizonOS..."
	echo "  Building asm files..."
	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	nasm -f elf -o "bin/gdt.o" "src/kernel/GDT/gdt.asm"
	nasm -f elf -o "bin/idt.o" "src/kernel/IDT/idt.asm"
	nasm -f elf -o "bin/syscalls.o" "src/kernel/IDT/syscalls.asm"
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

libc:
	nasm -f elf -o "src/libc/lib/crt0.o" "src/libc/functions/crt0.asm"
	nasm -f elf -o "src/libc/lib/crti.o" "src/libc/functions/crti.asm"
	nasm -f elf -o "src/libc/lib/crtn.o" "src/libc/functions/crtn.asm"
	
	nasm -f elf -o "src/libc/lib/putc.o" "src/libc/functions/stdio/putc.asm"

rmBin:
	rm -rf bin/*
	rm -rf iso
	rm -rf src/libc/lib/*

clean: rmBin
	rm -f horizonos.iso