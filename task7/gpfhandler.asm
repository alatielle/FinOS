global	gpfhandler

gpfhandler:
	mov	word [0xb8000],0x0331
	jmp	$