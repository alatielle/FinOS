#include "stdint.h"

extern void idt_ld(uint32_t);
extern void gpfhandler(void);

struct idt_entry_s
{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t always0;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr_s
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct idt_entry_s idt_entry_t;
typedef struct idt_ptr_s idt_ptr_t;

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	idt_entries[num].flags = flags;
} 

void setgpf()
{
	idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
	idt_ptr.base = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t)*256);
	int i;
	for (i=0; i<13; ++i)
		idt_set_gate( 0, 0 , 0x08, 0x0E);
	idt_set_gate( 13, (uint32_t)gpfhandler , 0x08, 0x8E);
	idt_ld((uint32_t)&idt_ptr);
	return;
}

void testgpf()
{
	return;
}
