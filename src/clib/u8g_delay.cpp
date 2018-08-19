#if defined(ARDUINO) && defined(STM32F1) || defined(STM32F1xx) || defined(STM32F4) || defined(STM32F4xx)

#include "u8g.h"
#include "Arduino.h"

void u8g_Delay(uint16_t val) {
   delay(val);
}

#endif // defined(ARDUINO) && defined(STM32F1) || defined(STM32F1xx) || defined(STM32F4) || defined(STM32F4xx)
