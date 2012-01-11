SECTIONS
{
    .text 0x8200 :
    {
        *(.chmode32)
		*(.text)
		. = ALIGN(4096);
    }
}