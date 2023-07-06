#include "./inc/utils.h"

unsigned short *termBuff;
const unsigned int	vgaWidth = 80;
const unsigned int	vgaHeight = 25;
unsigned int	prompt;
const unsigned int	promptMax = 80 * 25;

extern	int	strlen(char *str);
extern	unsigned char *strdup(unsigned char *str);
extern	unsigned char port_in(unsigned short nbr);
extern	void	port_out(unsigned short portNo, unsigned char val);

void enable_cursor(unsigned char cursor_start, unsigned char cursor_end)
{
	//renk
	port_out(0x3D4, 0x0F);

	//yatay konum
	port_out(0x3D5, 1);

	//dikey konum
	port_out(0x3D6, 1);

	//yazma komutu
	port_out(0x3D7, 0x0c);
	//port_out(0x3D4, 0x0A);
	/*
	unsigned char	a;

	a = port_in(0x3D5);
	putnbr((int)a);

	port_out(0x3D4, 0x0A);
	port_out(0x3D5, (port_in(0x3D5) & 0xC0) | cursor_start);
 
	port_out(0x3D4, 0x0B);
	port_out(0x3D5, (port_in(0x3D5) & 0xE0) | cursor_end);
	*/
}

int	kmain()
{
	prompt = 0;
	termReset();

	enable_cursor((unsigned char)200, (unsigned char)15);

	unsigned char x[] = "abi";
	unsigned char y[] = "abii";


	unsigned char a;

	int diff;

	diff = strcmp(x, y);
	//putchar('o');

	putnbr(diff);
	//print(x);
	return (0);
}