#include "Timer.h"
void TIMER_Configuration () {
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
/* Time Peripheral clock enable */
RCC_APB2PeriphClockCmd (RCC_APB2Periph_TIM1, ENABLE);
TIM_TimeBaseInitStruct. TIM_CounterMode= TIM_CounterMode_Up;
TIM_TimeBaseInitStruct. TIM_Period = 0xFFFF;
TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;
TIM_TimeBaseInit (TIM1, &TIM_TimeBaseInitStruct);
TIM_Cmd (TIM1, ENABLE);
}
void Delay_Ms(uint16_t DelayCounter) { 
	while (DelayCounter) {
	TIM_SetCounter(TIM1,0U);//TIM1->CNT = 0U;
	while ((TIM1->CNT) <1000U) {}
		DelayCounter--;
}
	}
void Delay_Us (uint16_t DelayCounter){
while (DelayCounter) {
	TIM_SetCounter(TIM1,0U);//TIM1->CNT = 0U;
while ((TIM1->CNT) <1U) {}
		DelayCounter--;
}
}