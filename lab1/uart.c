#include "gpio.h"

/* provideing mini UART registers  */
#define AUX_ENABLE      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR      ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD     ((volatile unsigned int*)(MMIO_BASE+0x00215068))


enum {SUCCESS, FAILED, OUTOFRANGE};
/* 
 * Set baud rate and characterostocs amd ,a[ tp GPIO
 */

/* Setup(Lab1)  */


int strcmp(char *s, char *t)
{
	while(*s && *s == *t) {
		s++;
		t++;
	}
	
	return *s - *t;
}

char *memset(void *s, int n, int size)
{
	char *str = (char *)s;
	char *tmp = str;
	while(size--) {
		*str = n;
		str++;
	}
	return tmp;
}

void uart_init()
{
	//register unsigned int r;

	*AUX_ENABLE |= 1; /* mini UART register can be accessed */
	*AUX_MU_CNTL = 0; /* Disable transmitter and receiver during configuration */
	*AUX_MU_LCR  = 3; /* Set the data size to 8 bits */
	*AUX_MU_MCR  = 0; /* No need auto flow control */
	*AUX_MU_IER  = 0; /* Disable interrupt in this lab */
	*AUX_MU_IIR  = 0xc6; /* No FIFO */
	*AUX_MU_BAUD = 270; /* 115200 baud */ 

}

/* Send a character */

void uart_send(unsigned int c) 
{
	/* wait until we can send */
	/* translate into assmble nop */
	do {asm volatile("nop");}while(!(*AUX_MU_LSR&0x20));
	/* write the character to the buffer */
	*AUX_MU_IO = c;
}

/* receive a character */

char uart_getc()
{
	char r;
	do {asm volatile("nop");}while (!(*AUX_MU_LSR&0x01));
	r = (char)(*AUX_MU_IO);
	return r == '\r'?'\n':r;
}

int uart_gets(char *r, int size) 
{
	char c = 0;
	char *ptr = r;
	memset(r, 0, 10);
	while(ptr - r < size && c != '\n') {
		c = uart_getc();
		uart_send(c);
		*ptr++ = c;
	}
	*(ptr-1) = '\0';
	if (ptr - r >= size)
		return OUTOFRANGE;
	return SUCCESS;
}

/* Display a string */
void uart_puts(char *s) 
{
	while(*s) {
		if (*s == '\n')
			uart_send('\r');
		uart_send(*s++);
	}
}
