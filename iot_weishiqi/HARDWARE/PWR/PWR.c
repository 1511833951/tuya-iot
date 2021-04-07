#include  "stm32f10x_it.h"
#include "PWR.h"
void PWR_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
}