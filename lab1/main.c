/* this file is for setting uart that include GPIO based on MMIO */
#include "uart.h"
#include "main.h"


void main()
{
	/* set up serial console */
	uart_init();
	shell();
}

void shell()
{
	char command[SIZE];
	while(1) {
		uart_puts("Shell -> ");
		uart_gets(command, SIZE);
		if (!strcmp(command, "help")) {
			help();	
		} else if(!strcmp(command, "hello")) {
			hello();
		} else {
			uart_puts("Err: command ");
			uart_puts(command);
			uart_puts(" noy found, try <help>\n");
		}

	}
}

void hello()
{
	uart_puts("Hello World!\n");
}

void help()
{
	for (int i = 0;i < sizeof(command)/sizeof(command[0]);i++) { 
		uart_puts(command[i]); 
		uart_send('\n');
	}
}
