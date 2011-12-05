global  _g
extern	_f
	section .data
dbl dq 0
        section .text
_g:
finit
fld qword [esp+4]
fimul dword [esp+12]
fstp qword [dbl]

push	dword [dbl+4]
push	dword [dbl]
call	_f
add	sp,8
ret
