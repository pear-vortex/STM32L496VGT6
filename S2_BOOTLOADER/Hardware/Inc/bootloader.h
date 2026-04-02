#include "stm32l496xx.h"
#include "stm32l4xx_hal.h"

typedef void (*AppFunc)(void);

//#define bootloader

void JumpToApp(uint32_t appAddr);
void Flash_Unlock(void);
HAL_StatusTypeDef updateFlash(void);