#include "../inc/kern.h"

#define ROW prompt[termNumber] / VGAWIDTH
#define COLUMN prompt[termNumber] % VGAWIDTH

static inline unsigned short vga_entry(unsigned char uc, unsigned char color)
{
	return (unsigned short) uc | (unsigned short) color << 8;
}

void update_cursor(int x, int y)
{
	unsigned short pos = y * VGAWIDTH + x;

	port_out(0x3D4, 0x0F); //burda birazdan row degeri yolliyacagimizi belirtiyoruz
	port_out(0x3D5, (unsigned char) (pos & 0xFF)); // son 8 bit
	port_out(0x3D4, 0x0E);// burdada birazdan column degerini yolliyacagimizi belirtiyoruz
	port_out(0x3D5, (unsigned char) ((pos >> 8) & 0xFF)); // ilk 8 bit
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
	unsigned char	counter;

	counter = 0;
	while (counter < 8)
	{
		hei = 0;
		while (hei < VGAHEIGHT * 2)
		{
			wid = 0;
			while (wid < VGAWIDTH)
			{
				termLines[counter][hei][wid] = vga_entry(' ', colorSet);
				wid++;
			}
			hei++;
		}
		counter++;
	}
}

void	flushTermOld()
{
	unsigned int	counter;
	unsigned int	counter2;

	//termReset();
	termBuff = (unsigned short *)0xB8000;

	if (ROW < VGAHEIGHT)
	{
		counter = -1;
		while (++counter < (VGAHEIGHT - (ROW + 1)) * VGAWIDTH)
		{
			termBuff[counter] = termLines[termNumber][(50 - (VGAHEIGHT - ROW)) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
		counter2 = -1;
		while (++counter2 < ROW * VGAWIDTH)
		{
			termBuff[counter + counter2] = termLines[termNumber][counter2 / VGAWIDTH][counter2 % VGAWIDTH];
		}
	}
	else
	{
		counter = -1;
		while (++counter < ((VGAHEIGHT - 1) * VGAWIDTH))
		{
			termBuff[counter] = termLines[termNumber][(ROW - 24) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
	}
}

void leftRightArrowHandler(unsigned char mode)
{
	if (mode == 0) // mode 0 = leftArrow
	{
		if (termNumber > 0)
			termNumber -= 1;
	}
	else if (mode == 1) // mode 1 rightArrow
	{
		if (termNumber < 7)
			termNumber += 1;
	}
	flushTermOld();
}
void	ArrowHandler(unsigned char mode)
{
	unsigned int	counter;
	unsigned int	counter2;
	unsigned int	supRow;

	if (mode == 1)
	{
		if (ROW <= arrowBuff)
			return;
		arrowBuff += 1;
	}
	else
	{
		if (arrowBuff < 1)
			return;
		arrowBuff -= 1;
	}

	supRow = ROW - arrowBuff;

	termBuff = (unsigned short *)0xB8000;
	if (supRow < VGAHEIGHT)
	{
		counter = -1;
		while (++counter < (VGAHEIGHT - (supRow + 1)) * VGAWIDTH)
		{
			termBuff[counter] = termLines[termNumber][(50 - (VGAHEIGHT - supRow)) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
		counter2 = -1;
		while (++counter2 < supRow * VGAWIDTH)
		{
			termBuff[counter + counter2] = termLines[termNumber][counter2 / VGAWIDTH][counter2 % VGAWIDTH];
		}
	}
	else
	{
		counter = -1;
		while (++counter < ((VGAHEIGHT - 1) * VGAWIDTH))
		{
			termBuff[counter] = termLines[termNumber][(supRow - 24) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
	}
}

void	flushLastRow(unsigned char *lastRow, unsigned int len)
{
	unsigned int	counter;
	unsigned char	header[] = "Oyumusak-Kfs1:";
	static unsigned int	promptLast = 14;

	termBuff = (unsigned short *)0xB8000;

	counter = -1;
	while (header[++counter])
		termBuff[counter + ((VGAHEIGHT - 1) * VGAWIDTH)] = vga_entry(header[counter], colorSet);

	counter = 0;
	while (counter < len)
	{
		if (*(lastRow + counter) == '\n')
		{
			counter = -1;
			while (++counter < VGAWIDTH)
			{
				termBuff[counter + ((VGAHEIGHT - 1) * VGAWIDTH)] = vga_entry(' ', colorSet);
			}
			counter = -1;
			while (header[++counter])
				termBuff[counter + ((VGAHEIGHT - 1) * VGAWIDTH)] = vga_entry(header[counter], colorSet);
			promptLast = 14;
			update_cursor((promptLast) , VGAHEIGHT - 1);
			arrowBuff = 0;
			break;
		}
		termBuff[promptLast + counter + ((VGAHEIGHT - 1) * VGAWIDTH)] = vga_entry(lastRow[counter], colorSet);
		update_cursor((promptLast) , VGAHEIGHT - 1);
		counter++;
		promptLast++;
	}
}

void	flushTerm()
{
	unsigned int	counter;
	unsigned int	counter2;

	termReset();
	termBuff = (unsigned short *)0xB8000;

	if (ROW < VGAHEIGHT)
	{
		// 1
		// 25 - 1 = 24
		counter = -1;
		while (++counter < (VGAHEIGHT - (ROW + 1)) * VGAWIDTH)
		{
			termBuff[counter] = termLines[termNumber][(50 - (VGAHEIGHT - ROW)) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
		counter2 = -1;
		while (++counter2 < (ROW + 1) * VGAWIDTH)
		{
			termBuff[counter + counter2] = termLines[termNumber][counter2 / VGAWIDTH][counter2 % VGAWIDTH];
		}
	}
	else
	{
		counter = -1;
		while (++counter < ((VGAHEIGHT) * VGAWIDTH))
		{
			termBuff[counter] = termLines[termNumber][(ROW - 24) + (counter / VGAWIDTH)][counter % VGAWIDTH];
		}
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
			tmp = prompt[termNumber] + (VGAWIDTH - (prompt[termNumber] % VGAWIDTH));
			while (prompt[termNumber] < tmp)
			{
				termLines[termNumber][ROW][COLUMN] = vga_entry(' ', colorSet);
				prompt[termNumber] += 1;
			}
			if (prompt[termNumber] >= promptMax)
				prompt[termNumber] = 0;
			continue;
		}
		termLines[termNumber][ROW][COLUMN] = vga_entry(*(str + counter), colorSet);
		prompt[termNumber] += 1;
		if (prompt[termNumber] >= promptMax)
			prompt[termNumber] = 0;
	}
	flushTermOld();
	flushLastRow(str, len);
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
		/*
  		 * 0x80000000 is an unsigned value
		 * -Wall -Wextra -Werror fails.
   		 * ~0x7FFFFFFF = 0x80000000
  		 */
		if (nbr == ~0x7FFFFFFF)
		{
			nbr = -147483648;
			str[0] = '2';
			write(1, str, 1);
		}
		nbr = nbr * -1;
		putnbr(nbr);
	}
	else
	{
		str[0] = nbr + 48;
		write(1, str, 1);
	}

}
