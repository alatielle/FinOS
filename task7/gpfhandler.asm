global	_gpfhandler
extern _printstring

_gpfhandler:
	mov	edx,gpfstring
	push	edx
	mov	edx,[curpos]
	push	edx
	call	_printstring
	add	edx,160
	mov	[curpos],edx
	add	esp,8
	mov	word [0xb800a],0x0431
	jmp	$
	
curpos: dd 0xb8000
gpfstring: db 'GPF! ',0