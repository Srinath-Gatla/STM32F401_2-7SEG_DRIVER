#include "STM32F401_7SEG.h"
uint8_t ISPRIME(uint8_t num)
{
	if(num<2)
	{
		return 0;
	}
	for(uint32_t j=2;j<=(num/2);j++)
	{
		if((num%j)==0)
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	Init7SEG();
	while(1)
	{
		for(uint32_t i=0;i<=99;i++)
		{
			if(ISPRIME(i))
			{
				Disp_7SEG(i);
			}
		}
	}
}
