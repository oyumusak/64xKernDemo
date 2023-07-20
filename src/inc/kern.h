#ifndef KERN_H

# define KERN_H

#define VGAWIDTH 80
#define VGAHEIGHT 25

# define LINES 25 // 2 bytes each
# define COLUMNS_IN_LINE 80

# define IDT_SIZE 256 // Specific to x86 architecture
# define KERNEL_CODE_SEGMENT_OFFSET 0x10
# define IDT_INTERRUPT_GATE_32BIT 0x8e

# define PIC1_COMMAND_PORT 0x20
# define PIC1_DATA_PORT 0x21
# define PIC2_COMMAND_PORT 0xA0
# define PIC2_DATA_PORT 0xA1

# define KEYBOARD_DATA_PORT 0x60
# define KEYBOARD_STATUS_PORT 0x64

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

# pragma GCC diagnostic ignored "-Waddress-of-packed-member"

struct IDT_pointer {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct IDT_entry {
	unsigned short offset_lowerbits; // 16 bits
	unsigned short selector; // 16 bits
	unsigned char zero; // 8 bits
	unsigned char type_attr; // 8 bits
	unsigned short offset_upperbits; // 16 bits
} __attribute__((packed));

extern unsigned short *termBuff;
extern const unsigned int	vgaWidth;
extern const unsigned int	vgaHeight;
extern unsigned int	prompt[8];
extern const unsigned int	promptMax;
extern unsigned short termLines[8][VGAHEIGHT * 2][VGAWIDTH];
extern unsigned int	lineCount;
extern unsigned char colorSet;
extern unsigned short (*termLinesBegin)[VGAWIDTH];
extern unsigned int arrowBuff;
extern unsigned char termNumber;


extern struct IDT_entry IDT[IDT_SIZE];

//boot.s funcs
extern void				keyboard_handler();
extern	char			port_in(unsigned short nbr);
extern	void			port_out(unsigned short portNo, unsigned char val);
extern void				load_idt(unsigned int* idt_address);
extern void				enable_interrupts();
extern	unsigned int				strlen(unsigned char *str);

//keyboard.c funcs
void	kb_init();
void	init_idt();
void	handle_keyboard_interrupt();

//extern	unsigned char *strdup(unsigned char *str);
void	termReset(void);
void	write(int fd, unsigned char *str, unsigned int len);
void    initTermLines();
void	print(unsigned char *str);
void	putnbr(int nbr);
void	ArrowHandler(unsigned char mode);
void leftRightArrowHandler(unsigned char mode);





#endif