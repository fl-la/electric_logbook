#pragma once

#include "FreeRTOS.h"

typedef struct{
	StaticTask_t	task;
	UBaseType_t		priority;
    StackType_t		stack[];
}task_manage_t;