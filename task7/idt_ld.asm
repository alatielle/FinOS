global idt_ld

idt_ld:
    mov eax, [esp+4]
    lidt [eax]
    ret