/* 数据层：负责和底层驱动交互，获取数据 */
#include "data.h"
#include "deque.h"

/* adc数据缓存数组 */
Deque *adc_data_deque;
uint32_t adc_value = 0;

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim2)
	{
		static uint8_t i = 0;
		/* 获取adc数据 */
		HAL_ADC_Start(&hadc1);
		while(!(HAL_ADC_PollForConversion(&hadc1, 0xffff) == HAL_OK));
		adc_value = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
		
		if (i > BUFFER_LENGTH)
		{
			deleteFront(adc_data_deque);
			insertRear(adc_data_deque, adc_value);
		} else {
			/* 将adc数据写入缓存数组中 */
			insertRear(adc_data_deque, adc_value);
		}
		i++;
	}
}

Deque *adc_data_get(void)
{
	return adc_data_deque;
}
