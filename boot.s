bits 32
section .multiboot
	dd 0x1BADB002	; Magic number
	dd 0x0			; Flags
	dd - (0x1BADB002 + 0x0)	; Checksum


section .text
	global start
	global strlen
	global strdup
	global port_in
	global port_out
	extern kmain

section .data
	myVal db 100


strlen:
	push ebp
	mov ebp, esp
	mov edi, [ebp + 8]

	mov eax, 0
	xor ecx, ecx

	loop:

	cmp byte [edi + ecx], 0
	je end
	inc ecx
	inc eax
	jmp loop

	end:
		pop ebp
		ret

section .data
	bilal db "merhaba falan", 0

strdup:
	push ebp
	mov ebp, esp
	mov edi, [ebp + 8]

	xor ecx, ecx
	duploop:
		cmp byte [edi + ecx], 0
		je son
		mov eax, [edi + ecx]
		mov [bilal + ecx], eax
		;mov byte [esi + ecx], [edi + eax]

		inc ecx
		jmp duploop

		son:
			pop ebp
			mov eax, bilal
			ret


port_in:
	mov dx, [esp + 4]
	in al, dx
	ret

port_out:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

	
start:
	call kmain
	hlt
