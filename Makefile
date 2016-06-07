GPPPARAMS= -m32 -fno-use-cxa-atexit -Wall -Wextra -nostdlib -fno-rtti -fno-exceptions -ffreestanding -fno-leading-underscore -Wwrite-strings  -Iinclude
OBJS=obj/loader.o obj/kernel.o obj/Screen.o obj/ioports.o obj/string.o obj/math.o obj/stdlib.o
#Temporary, I'm linking libc .o files with kernel files. Later I'm going to use GNU/ar

ErykOS.iso: kernel.bin
	grub-mkrescue -o $@ iso/

kernel.bin: $(OBJS)
	ld -m elf_i386 -T link.ld $^ -o iso/boot/$@

obj/%.o: kernel/%.asm
	nasm -f elf32 $< -o $@

obj/%.o: kernel/%.cpp
	g++ -c $< -o $@ $(GPPPARAMS)

obj/%.o: libc/%.cpp
	g++ -c $< -o $@ $(GPPPARAMS)
