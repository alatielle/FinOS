global  _g
        section .text
_g:
finit
fld qword [esp+4]
fimul dword [esp+12]
ret