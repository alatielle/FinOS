#!/usr/bin/perl
eval("use String::CRC32;");
die ("no String::CRC32 module was found. Please install it.") if $@;
$outp='s';
open O,'>',$outp.'.bin.asm' or die("Error: $!");
open F,'<','s' or die("Error: $!");
binmode F;
(undef,undef,undef,undef,undef,undef,undef,$size,
       undef,undef,undef,undef,undef)
           = stat(F);
die ("Too large") if ($size>512*32);
my $filebuf;
read(F,$filebuf,512*32) or die("Error: $!");
$crc = crc32($filebuf);
$crc=sprintf("%X",$crc);
close F;
$asm='org 0x7c00
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
mov al,'.(length($filebuf)%512==0?(int (length($filebuf)/512) ):(int (length($filebuf)/512) + 1))."\n".
'mov cx, 4
mov bx, buf
int 0x13
jc	@err
mov cx,sp
sub cx,4
pushfd
cmp cx,sp
je ok32
popfd
mov	bp,not32str
mov	bx,4
mov ah,3
int 0x10
mov	cx,18
mov	ax,0x1301
int	0x10
jmp @a
ok32:
popfd
mov ecx, 0
xor di, di
_tab:
        mov eax, ecx
        push cx
        mov cx, 8
        _mktab:
                shr eax,1
                jnc mktabend
                xor eax, 0xEDB88320
mktabend:
        loop _mktab
        mov [crctab+di], eax
        add di, 4
        pop cx

inc	cx
cmp	cx,0xff
jbe	_tab
;-)
mov eax, 0xFFFFFFFF
mov ecx, [len]
xor esi, esi
calc:
	mov	edx,eax
	shr	edx,8
	mov	ebx,eax
	xor	bl,[buf+esi]
	inc	esi
	and	ebx,0xff
	shl	ebx,2
	mov	ebx,[ebx+crctab]
	xor	ebx,edx
	mov	eax,ebx
loop calc
xor eax, 0xFFFFFFFF
;;;

;;;
cmp	eax,[crc]
je	crcok
mov	bp,failstr
mov	bx,4
mov ah,3
int 0x10
mov	cx,15
mov	ax,0x1301
int	0x10
@err:
    mov	bp,errstr
    mov bx,4
    mov ah,3
    int 0x10
    mov	cx,24
    mov	ax,0x1301
;    int	0x10
@a:
cli
hlt
jmp	@a
crcok:
jmp	0x0:buf
failstr: db \'CRC not equal! \'
errstr: db \'Error. Execution stopped.\'
not32str: db \'Error. Not 32-bit.\'
len: dd '.length($filebuf)."\n".
'crc: dd '."0x$crc\n".
'times 510-($-$$) db 0
db 0x55
db 0xaa
crctab: times 256 dd 0
buf: db 0';
print O $asm;
close O;
system("nasm $outp.bin.asm") == 0
or die("nasm failure: $?");
open B,'<',"$outp.bin" or die("Error: $!");
binmode B;
read B,$combuf,512*3 or die("Error: $!");
close B;
open B,'>',"$outp.bin" or die("Error: $!");
binmode B;
print B $combuf;
printf B "%s%n",$filebuf,$tot;
$tot=512-($tot % 512);
$filebuf='';
$filebuf.="\0" for (1..$tot);
printf B $filebuf;
close B;