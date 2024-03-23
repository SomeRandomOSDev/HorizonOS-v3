CC = i386-elf-gcc
CFLAGS = -std=gnu99 -nostdlib -lgcc -ffreestanding -Wall -masm=intel -m32 # -O3

all: horizonos.iso

horizonos.iso: src/kernel/kernelentry.asm Makefile rmBin libc
	tar cvf initrd.tar initrd

	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	nasm -f elf -o "bin/gdt.o" "src/kernel/GDT/gdt.asm"
	nasm -f elf -o "bin/idt.o" "src/kernel/IDT/idt.asm"
	nasm -f elf -o "bin/syscalls.o" "src/kernel/IDT/syscalls.asm"

	$(CC) -c "src/kernel/kmain.c" -o "bin/kmain.o" $(CFLAGS)

	ld -m elf_i386 -T src/link.ld -o "bin/kernel.bin"

	mkdir -p root/boot/grub

	cp bin/kernel.bin root/boot/kernel.bin
	cp src/grub.cfg root/boot/grub/grub.cfg

	grub-mkrescue -o horizonos.iso root

libc:
	echo "Building libc..."
	
	nasm -f elf -o "src/libc/lib/crt0.o" "src/libc/functions/crt0.asm"
	nasm -f elf -o "src/libc/lib/crti.o" "src/libc/functions/crti.asm"
	nasm -f elf -o "src/libc/lib/crtn.o" "src/libc/functions/crtn.asm"
	
	nasm -f elf -o "src/libc/lib/putc.o" "src/libc/functions/stdio/putc.asm"

rmBin:
	rm -rf bin/*
	rm -rf root
	rm -rf src/libc/lib/*
	rm -rf initrd.tar

clean: rmBin
	rm -f horizonos.iso