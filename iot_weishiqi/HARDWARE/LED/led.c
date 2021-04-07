#include "led.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE核心板
//LED驱动代码	   
						  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 输出高 
}
 
unsigned int moto_flag=100; //赋予初值用于限制开与关
unsigned int moto_fla=100;
void moto_init()
{
	 //定义IO初始化配置结构体
   GPIO_InitTypeDef  GPIO_InitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//打开PC端口时钟 
	 
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_6|GPIO_Pin_7;	
	 //IO口速度为50MHz
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 //配置为推挽输出
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 //配置IO
   GPIO_Init(GPIOC, &GPIO_InitStructure);	
}
//////////////////////////////////////////////////////////////////////////////////	 
//以下是电机操作，主要控制喂食仓的开关					  
//////////////////////////////////////////////////////////////////////////////////
void moto_open()
{
	while(moto_flag>0)
	{

	GPIO_SetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	GPIO_ResetBits(GPIOC,in3);
	GPIO_ResetBits(GPIOC,in4);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_SetBits(GPIOC,in2);
	GPIO_ResetBits(GPIOC,in3);
	GPIO_ResetBits(GPIOC,in4);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	GPIO_SetBits(GPIOC,in3);
	GPIO_ResetBits(GPIOC,in4);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	GPIO_ResetBits(GPIOC,in3);
	GPIO_SetBits(GPIOC,in4);
	delay_ms(3);
	moto_flag--;                                //循环减
	}
	delay_ms(1000);
while(moto_flag<100)
	{
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_SetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_SetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	moto_flag++;                               //循环加	
		
	}
}

void moto_close()
{
	while(moto_flag<100)
	{
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_SetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_SetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,in1);
	GPIO_ResetBits(GPIOC,in2);
	delay_ms(3);
	moto_flag++;                               //循环加	
		
	}
}
//////////////////////////////////////////////////////////////////////////////////	 
//以下是人体红外实现，检测是否宠物在喂食器旁，GPIO_Mode_AIN = 0x0,
//  GPIO_Mode_IN_FLOATING = 0x04,
//  GPIO_Mode_IPD = 0x28,
//  GPIO_Mode_IPU = 0x48,
//  GPIO_Mode_Out_OD = 0x14,
//  GPIO_Mode_Out_PP = 0x10,
//  GPIO_Mode_AF_OD = 0x1C,
//  GPIO_Mode_AF_PP = 0x18
//////////////////////////////////////////////////////////////////////////////////
void anmimal_recognition_init(void)
{
 
GPIO_InitTypeDef GPIO_InitStructure_A;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO外设

	GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_11;//定义PA4gpio口

  GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_Out_PP;//ipd下拉输入

GPIO_Init(GPIOB, &GPIO_InitStructure_A);//初始化GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
	
}
//////////////////////////////////////////////////////////////////////////////////	 
//一下是控制直流电机的正反向操作
//GPIO_Mode_AIN = 0x0,
//  GPIO_Mode_IN_FLOATING = 0x04,
//  GPIO_Mode_IPD = 0x28,
//  GPIO_Mode_IPU = 0x48,
//  GPIO_Mode_Out_OD = 0x14,
//  GPIO_Mode_Out_PP = 0x10,
//  GPIO_Mode_AF_OD = 0x1C,
//   = 0x18
//////////////////////////////////////////////////////////////////////////////////
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); //使能PB端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOF, &GPIO_InitStructure);		//根据设定参数初始化GPIOB 
  //暂时先把IO口拉低电平，也可以不拉
  GPIO_ResetBits(GPIOF,GPIO_Pin_11|GPIO_Pin_12);
}
