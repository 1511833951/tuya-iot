#include "led.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//LED��������	   
						  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 
unsigned int moto_flag=100; //�����ֵ�������ƿ����
unsigned int moto_fla=100;
void moto_init()
{
	 //����IO��ʼ�����ýṹ��
   GPIO_InitTypeDef  GPIO_InitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//��PC�˿�ʱ�� 
	 
   GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_6|GPIO_Pin_7;	
	 //IO���ٶ�Ϊ50MHz
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 //����Ϊ�������
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 //����IO
   GPIO_Init(GPIOC, &GPIO_InitStructure);	
}
//////////////////////////////////////////////////////////////////////////////////	 
//�����ǵ����������Ҫ����ιʳ�ֵĿ���					  
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
	moto_flag--;                                //ѭ����
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
	moto_flag++;                               //ѭ����	
		
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
	moto_flag++;                               //ѭ����	
		
	}
}
//////////////////////////////////////////////////////////////////////////////////	 
//�������������ʵ�֣�����Ƿ������ιʳ���ԣ�GPIO_Mode_AIN = 0x0,
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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO����

	GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_11;//����PA4gpio��

  GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_Out_PP;//ipd��������

GPIO_Init(GPIOB, &GPIO_InitStructure_A);//��ʼ��GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
	
}
//////////////////////////////////////////////////////////////////////////////////	 
//һ���ǿ���ֱ����������������
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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE); //ʹ��PB�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOF, &GPIO_InitStructure);		//�����趨������ʼ��GPIOB 
  //��ʱ�Ȱ�IO�����͵�ƽ��Ҳ���Բ���
  GPIO_ResetBits(GPIOF,GPIO_Pin_11|GPIO_Pin_12);
}
