SECTIONS
{
    .chmode32 0x8200 :
    {
        *(.chmode32)
        . = ALIGN(4096);
    }
    .text 0x9000 :
    {
        *(.text)
        . = ALIGN(4096);
    }
}