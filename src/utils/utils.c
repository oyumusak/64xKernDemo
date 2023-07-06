#include "../inc/utils.h"

static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline unsigned short vga_entry(unsigned char uc, unsigned char color)
{
	return (unsigned short) uc | (unsigned short) color << 8;
}

void	termReset(void)
{
	unsigned int	wid;
	unsigned int	hei;
	unsigned char	color;

	color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);


	termBuff = (unsigned short *)0xB8000;

	hei = 0;
	while (hei < vgaHeight)
	{
		wid = 0;
		while (wid < vgaWidth)
		{
			termBuff[(80 * hei) + wid] = vga_entry(' ', color);
			wid++;
		}
		hei++;
	}
}

void	print(unsigned char *str)
{
	unsigned int	counter;
	unsigned char	color;

	color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	termBuff = (unsigned short *)0xB8000;

	counter = 0;
	while (*(str + counter))
	{
		if (*(str + counter) == '\n')
		{
			prompt = prompt + vgaWidth - counter;
			counter++;
			continue;
		}
		termBuff[prompt] = vga_entry(*(str + counter), color);
		prompt++;
		counter++;
	}
}

int strcmp(const char *s1, const char *s2)
{
    unsigned int    counter;

    counter = 0;
    while (s1[counter] == s2[counter] && s1[counter])
        counter++;
    return (s1[counter] - s2[counter]);
}

void    putchar(char c)
{
	unsigned char	color;

	color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	termBuff = (unsigned short *)0xB8000;

    if (c == '\n')
        prompt = prompt + vgaWidth;
    else
        termBuff[prompt++] = vga_entry(c, color);
}

void    putnbr(int nbr)
{
    if (nbr == -2147483648)
    {
        print("-2147483648");
        return;
    }
    if (nbr > 9)
    {
        putnbr(nbr / 10);
        putchar((nbr % 10) + 48);
    }
    else if (nbr < 0)
    {
        putchar('-');
        nbr = nbr * -1;
        putnbr(nbr);
    }
    else
        putchar((nbr % 10) + 48);
}