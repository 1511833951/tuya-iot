#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//ADC ��������			   

////////////////////////////////////////////////////////////////////////////////// 	  
 		 
 
   
short Get_Temprate(void);			//��ȡ�ڲ��¶ȴ������¶�ֵ
void T_Adc_Init(void); //ADCͨ����ʼ��
u16  T_Get_Adc(u8 ch); //���ĳ��ͨ��ֵ  
u16  T_Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 	  
#endif 
