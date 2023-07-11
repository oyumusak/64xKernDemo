#include "inc/kern.h"


//Global Variables!
unsigned short *termBuff;
const unsigned int	vgaWidth = VGAWIDTH;
const unsigned int	vgaHeight = VGAHEIGHT;
unsigned short termLines[VGAHEIGHT * 2][VGAWIDTH];
unsigned short (*termLinesBegin)[VGAWIDTH];
unsigned int	prompt;
unsigned int	lineCount;
const unsigned int	promptMax = VGAHEIGHT * VGAWIDTH;
unsigned char colorSet;
struct IDT_entry IDT[256];

static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

int	kmain()
{
	prompt = 0;
	lineCount = 0;
	termLinesBegin = termLines;
	colorSet = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	init_gdt();
	//unsigned char	kernMessage[] = "Merhaba\n DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba Dunya";
	//unsigned char	gelenVeri = 0;

	//termReset();
	//initTermLines();

	init_idt();
	kb_init();
	enable_interrupts();

	while(42);
	//write(1, kernMessage, strlen(kernMessage));
}