#include "../inc/kern.h"



static inline unsigned short vga_entry(unsigned char uc, unsigned char color)
{
	return (unsigned short) uc | (unsigned short) color << 8;
}


//16bit
// ilk 8 >> ilk 4 >> bg color >> ikinci 4 fg color
// sonraki 8 bit asci char

void	termReset(void)
{
	unsigned int	wid;
	unsigned int	hei;


	termBuff = (unsigned short *)0xB8000;

	hei = 0;
	while (hei < vgaHeight)
	{
		wid = 0;
		while (wid < vgaWidth)
		{
			termBuff[(80 * hei) + wid] = vga_entry(' ', colorSet);
			wid++;
		}
		hei++;
	}
}

void    initTermLines()
{
    unsigned int    wid;
    unsigned int    hei;

    hei = 0;
    while (hei < VGAHEIGHT * 2)
    {
        wid = 0;
        while (wid < VGAWIDTH)
        {
            termLines[hei][wid] = vga_entry(' ', colorSet);
            wid++;
        }
        hei++;
    }
}

void	flushTerm()
{
	unsigned int	counter;


	termBuff = (unsigned short *)0xB8000;
	counter = -1;
	while (++counter < VGAWIDTH * VGAHEIGHT)
	{
		termBuff[counter] = termLinesBegin[counter / VGAWIDTH][counter % VGAWIDTH];
	}
}


void	write(int fd, unsigned char *str, unsigned int len)
{
	unsigned int	counter;
	unsigned int	tmp;

	(void)fd;

	counter = -1;
	while (++counter < len)
	{
		if (*(str + counter) == '\n')
		{
			prompt += (VGAWIDTH - (prompt % VGAWIDTH));
			tmp = -1;
			while (++tmp < prompt)
				termLines[prompt / VGAWIDTH][prompt % VGAWIDTH] = vga_entry(' ', colorSet);
			continue;
		}
		termLines[prompt / VGAWIDTH][prompt % VGAWIDTH] = vga_entry(*(str + counter), colorSet);
		prompt++;
	}
	flushTerm();
}

void	putnbr(int nbr)
{
	char str[2];
	str[1] = 0;

	if (nbr > 9)
	{
		putnbr(nbr / 10);
		str[0] = (nbr % 10) + 48;
		write(1, str, 1);
	}
	else if (nbr < 0)
	{
		str[0] = '-';
		write(1, str, 1);
		nbr = nbr * -1;
		putnbr(nbr);
	}
	else
	{
		str[0] = nbr + 48;
		write(1, str, 1);
	}

}