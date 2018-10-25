#pragma once

#include <stdint.h>
#include "FreeRTOS.h"
#include "stm32f0xx_hal.h"

static inline Delay(const uint32_t ms)
{
	if(xTaskGetCurrentTaskHandle() != NULL)
		vTaskDelay(pdMS_TO_TICKS(ms));
	else
		HAL_Delay(ms);
}