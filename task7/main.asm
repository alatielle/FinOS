bits	16
extern _printint
extern _printstring
extern _clrscr
extern _setgpf
extern _testgpf

section	.chmode32
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
		db 0xcf
		db 0
segdes2	db 0xff
		db 0xff
		db 0
		db 0
		db 0
		db 0x92
		db 0xcf
		db 0

bits 32
aft:
	mov ax, 16
	mov ds, ax
	mov ss, ax
	mov esp, 0x10000

;;;;;
; call	_clrscr
; mov	ax,'a'
; mov	edx,0xb8000
; push	ax
; push	edx
; call	_printint
; add	esp,6
; add	edx,4
; mov	eax,somestr
; push	eax
; push	edx
; call	_printstring
; add	esp,8
;;;;;
	call	_setgpf
	sti
	call	_testgpf
	cli
	hlt
	jmp	$