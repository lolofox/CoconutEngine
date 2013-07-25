; ./src/core/hardware/cpu_spec.asm

SECTION .TEXT

GLOBAL cpuid_check

;------------------------------
; int cpuid_check(void)
; return 0 if unsupported.
;------------------------------
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
	