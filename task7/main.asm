extern	setgpf
extern	testgpf

;org	0x8200
cli
lgdt	[seg0ptr]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp	8:aft
seg0ptr dw 24
dd segdes0
align 16
segdes0 dq 0
segdes1	db 0xff
	db 0xff
	db 0
	db 0
	db 0
	db 0x9a
	db 0x4f
	db 0
segdes2	db 0xff
	db 0xff
	db 0
	db 0
	db 0
	db 0x92
	db 0x4f
	db 0
bits 32
aft:
mov ax, 16
mov ds, ax
mov ss, ax
mov esp, 0x10000
mov     word [0xB8000], 0x0730
call	setgpf
sti
call	testgpf
jmp	$