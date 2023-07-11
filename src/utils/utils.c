//#include "../inc/utils.h"
//
//int strcmp(const char *s1, const char *s2)
//{
//    unsigned int    counter;
//
//    counter = 0;
//    while (s1[counter] == s2[counter] && s1[counter])
//        counter++;
//    return (s1[counter] - s2[counter]);
//}

//void    putchar(char c)
//{
//	unsigned char	color;
//
//	color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
//	termBuff = (unsigned short *)0xB8000;
//
//    if (c == '\n')
//        prompt = prompt + vgaWidth;
//    else
//        termBuff[prompt++] = vga_entry(c, color);
//}
//
//void    putnbr(int nbr)
//{
//    if (nbr == -2147483648)
//    {
//        print("-2147483648");
//        return;
//    }
//    if (nbr > 9)
//    {
//        putnbr(nbr / 10);
//        putchar((nbr % 10) + 48);
//    }
//    else if (nbr < 0)
//    {
//        putchar('-');
//        nbr = nbr * -1;
//        putnbr(nbr);
//    }
//    else
//        putchar((nbr % 10) + 48);
//}