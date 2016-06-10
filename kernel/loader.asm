MAGIC 		equ 0x1BADB002
FLAGS		equ (1<<0 | 1<<1)
CHECKSUM	equ -(MAGIC + FLAGS)


STACK_SIZE	equ 16384 ;16kB

section .multiboot
align 4

	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .text

global loader
loader:
	mov esp, stack + STACK_SIZE

	push eax ;multiboot magic number
	push ebx ;multiboot info structure

	extern main
	call main

	cli
	hlt
		
	jmp $

section .bss
align 4
stack:
	resb STACK_SIZE