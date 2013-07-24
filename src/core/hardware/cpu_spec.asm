; ./src/core/hardware/cpu_spec.asm

global cpuid_check

SECTION .text

cpuid_check:
	pushfd
	push	ebx
	push	ebp
	push	esi
	push	edi
	pushfd
	pop		eax
	mov		ebx, eax
	xor		eax, 0x200000
	push	eax
	popfd
	pushfd
	pop		eax
	xor		eax, ebx
	pop		edi
	pop		esi
	pop		ebp
	pop		ebx
	popfd
	ret
	