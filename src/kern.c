#include "inc/kern.h"


//Global Variables!
unsigned short *termBuff;
const unsigned int	vgaWidth = VGAWIDTH;
const unsigned int	vgaHeight = VGAHEIGHT;
unsigned short termLines[8][VGAHEIGHT * 2][VGAWIDTH];
unsigned char	termNumber;
unsigned short (*termLinesBegin)[VGAWIDTH];
unsigned int	prompt[8];
unsigned int	lineCount;
const unsigned int	promptMax = (VGAHEIGHT * 2) * VGAWIDTH;
unsigned char colorSet;
unsigned int arrowBuff;
struct IDT_entry IDT[256];

static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}



int	kmain()
{
	unsigned char counter;

	counter = -1;
	while (++counter < 8)
	{
		prompt[counter] = 0;
	}

	lineCount = 0;
	arrowBuff = 0;
	termNumber = 0;
	//termLinesBegin = termLines;
	colorSet = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	//unsigned char	kernMessage[] = "Merhaba\n DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba DunyaMerhaba Dunya";
	//unsigned char	gelenVeri = 0;

	termReset();
	initTermLines();



	init_idt();
	kb_init();
	enable_interrupts();


	return (0);
}