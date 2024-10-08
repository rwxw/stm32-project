#ifndef __UART_FRAME_H__
#define __UART_FRAME_H__

#include <stdio.h>
#include <stdarg.h>

typedef int (*uart_send_fn_t)(void);
typedef int (*uart_receive_fn_t)(void);

struct uart_i {
	uart_send_fn_t send;
	uart_receive_fn_t receive;
};

static inline int uart_send(void *self)
{
	return (*(struct uart_i **)self)->send();
}

static inline int uart_receive(void *self)
{
	return (*(struct uart_i **)self)->receive();
}

struct uart {
	struct uart_i *interface;
	unsigned char *data;
	int size;
};

/* printf redirect function */
void my_uart_printf(struct uart_i *uart_dev, char *format, ...)
{
	unsigned short size;
	unsigned char  String[100];				
	va_list arg;					
	va_start(arg, format);			
	vsprintf((char*)&String, format, arg);	
	va_end(arg);					
	
	for (size = 0; String[size] != '\0'; size ++)
	{
		uart_send(uart_dev);
	}	
}

int uart_dev_init(struct uart *self);

#endif
