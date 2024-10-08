#include "software.h"

/**
  *传入正确的包头
  *传入包头长度
  */
int header_check(uint8_t *header, uint8_t size)
{
	uint8_t *tmp;
	
	if (!get_header_data(tmp, size))
	{
		if (!tmp)
		{
			for (int i = 0; i < size; i++)
			{
				if (tmp[i] == header[i])
				{
					
				} else {
					/* 包头错误 */
					return 3;
				}
			}
			return 0;
		} else {
			/* 获取到无效的数据，空指针 */
			return 2;
		}
	} else {
		/* 没有正确获取到数据 */
		return 1;
	}
}
