#include "uart_frame.h"

int my_uart_send(void);
int my_uart_receive(void);

struct uart_i uart_interface = {
	.send = my_uart_send,
	.receive = my_uart_receive,
};

int my_uart_send()
{
	//放不同平台的串口发送函数
	return 0;
}

int my_uart_receive()
{
	//放不同平台的串口接收函数
	return 0;
}

int uart_dev_init(struct uart *self)
{
	self->interface = &uart_interface;
	self->data = NULL;
	self->size = 0;
	
	return 0;
}
