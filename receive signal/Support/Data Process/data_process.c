/* 数据处理层：获取数据层的数据进行一些逻辑判断 */
#include "data_process.h"

static int get_bit_data();
static int is_legal_high_bit(Deque *adc_data_buffer, uint8_t size, uint16_t judge_standard);
static int is_legal_low_bit(Deque *adc_data_buffer, uint8_t size, uint16_t judge_standard);
static int remove_extremum(Deque *data_buffer, uint8_t size);

extern TIM_HandleTypeDef htim2;
int extremum_arr[2];

Deque *bit_deque;
#define BIT_DEQUE_LENGTH  18

uint8_t bit_arr[10] = {0};

int header_check(uint8_t *header, uint8_t size)
{
	get_bit_data();
	Node *deque_cursor = bit_deque->front;
	
	for (int i = 0; i < size; i++)
	{
		deque_cursor = deque_cursor->next;
		if (header[i] == deque_cursor->data){}
		else { return 1;}
	}
	return 0;
}

uint8_t *get_bit_information(uint8_t size)
{
	Node *deque_cursor = bit_deque->front;
	for (int i = 0; i < 14; i++)
	{
		deque_cursor = deque_cursor->next;
		if (i < size)
		{
			
		} else {
			bit_arr[i - 4] = deque_cursor->data;
		}
	}
	
	return bit_arr;
}

/* 后面可以把这些属性都放到一个结构体里面 */
/**
  *传入包头长度
  */
static int get_bit_data()
{
	static uint8_t i = 0;
	Deque *adc_data;
	adc_data = adc_data_get();
	
	if (!adc_data)
	{
		i++;
		HAL_TIM_Base_Stop_IT(&htim2);
		
		if (!is_legal_high_bit(adc_data, BUFFER_LENGTH, 2500))
		{
			if (i > BUFFER_LENGTH)
			{
				deleteFront(bit_deque);
				insertRear(bit_deque, 1);
			} else {
				insertRear(bit_deque, 1);
			}
		}
		
		if (!is_legal_low_bit(adc_data, BUFFER_LENGTH, 50))
		{
			if (i > BUFFER_LENGTH)
			{
				deleteFront(bit_deque);
				insertRear(bit_deque, 0);
			} else {
				insertRear(bit_deque, 0);
			}
		}
		
		HAL_TIM_Base_Start_IT(&htim2);
		
	} else {
		/* adc数据获取失败 */
		return 1;
	}
	
	return 0;
}

static int is_legal_high_bit(Deque *adc_data_buffer, uint8_t size, uint16_t judge_standard)
{
	remove_extremum(adc_data_buffer, size);
	Node *deque_cursor = adc_data_buffer->front;
	
	uint16_t sum = 0;
	
	for (int i = 1; i < size; i++)
	{
		deque_cursor = deque_cursor->next;
		if ((deque_cursor->data != extremum_arr[0]) && (deque_cursor->data != extremum_arr[1]))
			sum = sum + deque_cursor->data;
	}
	
	if ((sum / (size - 2)) > judge_standard) 
		return 0;
	else
		return 1;
}

static int is_legal_low_bit(Deque *adc_data_buffer, uint8_t size, uint16_t judge_standard)
{
	remove_extremum(adc_data_buffer, size);
	Node *deque_cursor = adc_data_buffer->front;
	
	uint16_t sum = 0;
	
	for (int i = 1; i < size; i++)
	{
		deque_cursor = deque_cursor->next;
		if ((deque_cursor->data != extremum_arr[0]) && (deque_cursor->data != extremum_arr[1]))
			sum = sum + deque_cursor->data;
	}
	
	if ((sum / (size - 2)) < judge_standard) 
		return 0;
	else
		return 1;
}

static int remove_extremum(Deque *adc_data_buffer, uint8_t size)
{
	int max_tmp = adc_data_buffer->rear->data;
	int min_tmp = adc_data_buffer->front->data;
	
	Node *deque_cursor = adc_data_buffer->front;
	
	for (int i = 1; i < size; i++)
	{
		deque_cursor = deque_cursor->next;
		if (deque_cursor->data > max_tmp)
		{
			max_tmp = deque_cursor->data;
		}
		
		if (deque_cursor->data < min_tmp)
		{
			max_tmp = deque_cursor->data;
		}
	}

	extremum_arr[0] = max_tmp;
	extremum_arr[1] = min_tmp;
	
	return 0;
}
