export LD_LIBRARY_PATH=kernel/include
OBJS=obj/loader.o obj/kernel.o obj/Screen.o obj/ioports.o
LDPARAMS = 
GPPPARAMS= -m32 -fno-use-cxa-atexit -nostdlib -fno-rtti -fno-exceptions -fno-leading-underscore -Wwrite-strings  -Iinclude

ErykOS.iso: kernel.bin
	grub-mkrescue -o $@ iso/
kernel.bin: $(OBJS)
	ld -m elf_i386 -T link.ld $^ -o iso/boot/$@

obj/loader.o: kernel/loader.asm
	nasm -f elf32 $< -o $@

obj/kernel.o: kernel/kernel.cpp
	g++ -c $< -o $@ $(GPPPARAMS)

obj/Screen.o: kernel/Screen.cpp
	g++ -c $< -o $@ $(GPPPARAMS)

obj/ioports.o: kernel/ioports.cpp
	g++ -c $< -o $@ $(GPPPARAMS)

