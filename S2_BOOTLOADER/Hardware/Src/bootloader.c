#include "bootloader.h"
#include "main.h"

void JumpToApp(uint32_t appAddr)
{
	__disable_irq();
	
	SysTick->CTRL = 0;
	
	HAL_RCC_DeInit();
	HAL_DeInit();
	
	for (int i = 0; i < 91; i++)
	{
			NVIC_DisableIRQ(i);
			NVIC_ClearPendingIRQ(i);
	}
	
	//Relocate the vecort table
	SCB->VTOR = appAddr;
	
	//Set stack start address
	__set_MSP(*(uint32_t *)appAddr);
	
	//Point to app reset function address
	AppFunc app_func = (AppFunc) *(__IO uint32_t *)(appAddr + 4);
	
	//Execute app function
	app_func();
}