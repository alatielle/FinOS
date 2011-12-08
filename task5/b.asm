extern _f
	section .text
org 0x7c00
cli
mov ax,cs
mov ss,ax
mov ds,ax
mov es,ax
mov sp,0xffff
xor ax,ax
sti
;bits 32
;mov	word [0xb8000],0x403
;jmp looper
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
	;call	_f
	mov	word [0xb8000],0x403
looper:
	cli
	hlt
	jmp	looper
times 510-($-$$) db 0
db 0x55
db 0xaa
cplace: