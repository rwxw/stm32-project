#ifndef __DATA_H__
#define __DATA_H__

#include "stm32f1xx_hal.h"
#include "deque.h"

#define BUFFER_LENGTH  9
#define   level_is_high   ((adc_value > 2350) && (adc_value < 2500))

Deque *adc_data_get(void);
#endif
