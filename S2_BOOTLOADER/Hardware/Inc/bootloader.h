#include "stm32l496xx.h"

typedef void (*AppFunc)(void);

//#define bootloader

void JumpToApp(uint32_t appAddr);