#include "main.h"
#include <stdio.h>
#include <stdarg.h>

static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

static void Delay(__IO uint32_t nTime);


int main(void){
	SystemInit();
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 960);
	
	while (1){
		
	}
}

void Delay(__IO uint32_t nTime){
	uwTimingDelay = nTime;

	while(uwTimingDelay != 0);
}

void TimingDelay_Decrement(void){
	if (uwTimingDelay != 0x00){
		uwTimingDelay--;
	}
}

