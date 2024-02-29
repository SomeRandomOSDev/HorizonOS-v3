run: horizonos.iso
	qemu-system-i386 -cdrom "horizonos.iso"

horizonos.iso: src/kernel/kernelentry.asm Makefile clean
	echo "Building HorizonOS..."
	echo "  Building asm files..."
	nasm -f elf -o "bin/kernelentry.o" "src/kernel/kernelentry.asm"
	echo "  Building C files..."
	echo
	gcc -c "src/kernel/kmain.c" -o "bin/kmain.o" -std=gnu99 -ffreestanding -Wall -masm=intel -m32
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