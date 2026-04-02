#include "delay.h"

void delay_us(uint32_t _us)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	
	ticks = _us * (SYSCLK/1000000);
	
	told = SysTick->VAL;
	
	while(1)
	{
		tnow = SysTick->VAL;
		if(tnow != told)
		{
			if(tnow < told)
				tcnt += told - tnow;
			else
				tcnt += SysTick->LOAD - (tnow - told);
			told = tnow;
			
			if(tcnt >= ticks)
				break;
		}
	}
}

void delay_ms(uint16_t _ms)
{
	uint16_t i;
	for(i=0;i<_ms; i++)
	{
		delay_us(1000);
	}
}

void delay_s(uint16_t _s)
{
	uint16_t i;
	for(i=0;i<_s; i++)
	{
		delay_ms(1000);
	}
}