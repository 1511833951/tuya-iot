#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE核心板
//LED驱动代码	   
							  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	 
void LED_Init(void);//初始化
void moto_init(void);
void moto_open(void);
void moto_close(void);
void all_led(void);
void anmimal_recognition_init(void);
void Motor_Init();
#define in1 GPIO_Pin_6
#define in2 GPIO_Pin_7
#define in3 GPIO_Pin_8
#define in4 GPIO_Pin_9
#endif 

