extern	printsome

;org 0x7c00
jmp	0x0:start
start:
cli
xor ax,ax
mov ss,ax
mov ds,ax
mov es,ax
mov sp,0xffff
sti
mov ah, 2
mov al, 1
mov cx, 2
mov bx, buf
int 0x13
jc	@err
mov cx,sp
sub cx,4
pushfd
cmp cx,sp
je ok32
popfd
jmp	@err
ok32:
popfd
jmp	buf
@err:
mov	bp,errstr
mov	bx,4
mov ah,3
int 0x10
mov	cx,18
mov	ax,0x1301
int	0x10
jmp $
errstr: db 'Error.'
times 510-($-$$) db 0
db 0x55
db 0xaa
buf:
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
call	printsome
jmp	$