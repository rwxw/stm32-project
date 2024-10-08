#ifndef __DATA_PROCESS_H__
#define __DATA_PROCESS_H__

#include "data.h"

int header_check(uint8_t *header, uint8_t size);
uint8_t *get_bit_information(uint8_t size);

#endif
