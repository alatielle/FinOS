global _idt_ld

_idt_ld:
    mov eax, [esp+4]
    lidt [eax]
    ret