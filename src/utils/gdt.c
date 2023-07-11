#include "../inc/kern.h"
#include "../inc/gdt.h"

/* ************************************************************************** */
/* Globals                                                                    */
/* ************************************************************************** */

t_gdt_entry	gdt_entries[GDT_ENTRIES];
t_gdt_ptr	*gdt_ptr = (t_gdt_ptr *)GDT_ADDRESS;

/* ************************************************************************** */
/* Code                                                                       */
/* ************************************************************************** */

static void create_descriptor(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags)
{
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].access = access;
	gdt_entries[num].attributes = (limit >> 16) & 0x0F;
	gdt_entries[num].attributes |= ((flags << 4) & 0xF0);
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
}

void	init_gdt()
{
	gdt_ptr->limit = (sizeof(t_gdt_entry) * GDT_ENTRIES) - 1;
	gdt_ptr->base = ((unsigned int)(&gdt_entries));

	create_descriptor(0, 0, 0, 0, FLAG_D_32);				// null
	create_descriptor(1, 0, 0xFFFFF, (unsigned char)(GDT_CODE_PL0),  FLAG_D_32);	// kernel code (kernel binary)
	create_descriptor(2, 0, 0xFFFFF, (unsigned char)(GDT_DATA_PL0),  FLAG_D_32);	// kernel data (kernel heap)
	create_descriptor(3, 0, 0xFFFFF, (unsigned char)(GDT_STACK_PL0), FLAG_D_32);	// kernel stack
	create_descriptor(4, 0, 0xBFFFF, (unsigned char)(GDT_CODE_PL3),  FLAG_D_32);	// user code (user-executed binaries)
	create_descriptor(5, 0, 0xBFFFF, (unsigned char)(GDT_DATA_PL3),  FLAG_D_32);	// user data (user heap)
	create_descriptor(6, 0, 0xBFFFF, (unsigned char)(GDT_STACK_PL3), FLAG_D_32);	// user stack

	load_gdt(((unsigned int)gdt_ptr));
}