; ./src/core/hardware/cpu_spec.asm

SECTION .TEXT

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
	
;
; void cpuid_get(int op, int *eax, int *ebx, int *ecx, int *edx)
;
cpuid_get:
	push 	ebp			; Creating the stackframe.
	mov 	ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	push 	esi
	push	edi
	
	; Moving the op variable into eax register before calling cpuid instruction.
	mov		eax, dword [ebp + 8]
	cpuid
	
	mov		dword [ebp + 12], eax
	mov		dword [ebp + 10h], ebx
	mov		dword [ebp + 14h], ecx
	mov		dword [ebp + 18h], edx
	
	pop		edi			; Deleting the stack.
	pop		esi
	pop		edx
	pop		ecx
	pop		ebx
	pop		edx
	mov 	esp, ebp
	pop 	ebp
	ret
	