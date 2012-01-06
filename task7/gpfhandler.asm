global	_gpfhandler
extern _printstring
extern _printhex

_gpfhandler:
	mov	edx,gpfstring
	push	edx
	mov	edx,[curpos]
	push	edx
	call	_printstring
	mov	edx,[esp]
	mov	[curpos],edx
	add	esp,8
;
	; mov	edx,esp
	; push	edx
	; mov	edx,[curpos]
	; push	edx
	; call	_printhex
	; mov	edx,[esp]
	; add	edx,2
	; mov	[curpos],edx
	; add	esp,8
;
	mov	edx,[esp+0x1c]
	push	edx
	mov	edx,[curpos]
	push	edx
	call	_printhex
	mov	edx,[esp]
	add	edx,2
	mov	[curpos],edx
	add	esp,8
;
	; mov	edx,[esp+8]
	; push	edx
	; mov	edx,[curpos]
	; push	edx
	; call	_printhex
	; mov	edx,[esp]
	; mov	[curpos],edx
	; add	esp,8
;
	add	edx,160
	mov	[curpos],edx
	jmp	$
	
curpos: dd 0xb8000
gpfstring: db 'GPF at 0x',0