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


/**
 * @brief Unlock the flash for write access
 * @param None
 */
void Flash_Unlock(void) {
    if (HAL_FLASH_Unlock() != HAL_OK) {
    }
}

/**
 * @brief Update the flash specified memory address with the given data
 * @param None
 */
HAL_StatusTypeDef updateFlash(void)
{
	Flash_Unlock();
	
	HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, 0x08088000, 0xAB);

	HAL_FLASH_Lock();

	return status;
}