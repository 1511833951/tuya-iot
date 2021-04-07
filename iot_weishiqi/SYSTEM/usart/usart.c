#include "sys.h"
#include "usart.h"	
#include "wifi.h"
#include "stdio.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//����1��ʼ��		
////////////////////////////////////////////////////////////////////////////////// 	  
 
int tim2=0;
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
/* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init1(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}
void usart_init2(uint32_t bound)
{
	
	GPIO_InitTypeDef GPIOA_InitStructure;
	USART_InitTypeDef USART2_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//TX,RX gpio���ų�ʼ��
	GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOA_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);
	//TX,RX gpio���ų�ʼ��
	GPIOA_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIOA_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIOA_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);
	USART2_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART2_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART2_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART2_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2,&USART2_InitStructure);
	USART_Cmd(USART2,ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//nvic���ò���
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
  NVIC_Init(&NVIC_InitStructure);
}
void USART1_IRQHandler(void)
{
		unsigned char Res=0;
		if(USART_GetITStatus(USART1,USART_IT_RXNE)==ENABLE)
	{
	
			Res=USART_ReceiveData(USART1);
		uart_receive_input(Res);
			//GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	}
}
void USART_SendChar(USART_TypeDef* USARTx, unsigned char ucChar)
{
  while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));//???????
  USART_SendData(USARTx, ucChar);//??????
 //GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//	 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}
void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	unsigned char Res=0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		 uart_receive_input(Res);
		//	printf("�����ѽ���");
  	//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
  	
    }
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
	}
#endif	
//////////////////////////////////////////////////////////////////////////////////	 
//ʹ�ܶ�ʱ��2
////////////////////////////////////////////////////////////////////////////////// 	  
// void time2_init()
// {
//	 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDef;
//	 NVIC_InitTypeDef NVIC_InitStructure;
//	 RCC_APB1PeriphResetCmd( RCC_APB1Periph_TIM2,ENABLE);
//	 TIM_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode_Up;
//	 TIM_TimeBaseInitTypeDef.TIM_Period=4999;
//	 TIM_TimeBaseInitTypeDef.TIM_Prescaler=7199;
//	 TIM_TimeBaseInitTypeDef.TIM_ClockDivision = TIM_CKD_DIV1;
//	 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitTypeDef);
//	 TIM_Cmd(TIM2, ENABLE);
//	 TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//	 NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
//	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	 NVIC_Init(&NVIC_InitStructure);
// }
// 
void TIM2_Int_Init(u16 arr,u16 psc)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //��ʱ�� TIM3 ʹ��
//��ʱ�� TIM3 ��ʼ��
TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ������ڵ�ֵ
TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ALIENTEK ս�� STM32F103 V3 ������̳�

TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIM3
TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //����������ж�
//�ж����ȼ� NVIC ����
NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //TIM3 �ж�
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0 ��
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ� 3 ��
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
NVIC_Init(&NVIC_InitStructure); //�ܳ�ʼ�� NVIC �Ĵ���
TIM_Cmd(TIM4, ENABLE); //��ʹ�� TIM3
}
//void TIM3_Int_Init(u16 arr,u16 psc)
//{
//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//NVIC_InitTypeDef NVIC_InitStructure;
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //��ʱ�� TIM3 ʹ��
////��ʱ�� TIM3 ��ʼ��
//TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ������ڵ�ֵ
//TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
//TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ALIENTEK ս�� STM32F103 V3 ������̳�

//TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //�ڳ�ʼ�� TIM3
//TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //����������ж�
////�ж����ȼ� NVIC ����
//NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3 �ж�
//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0 ��
//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ� 3 ��
//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
//NVIC_Init(&NVIC_InitStructure); //�ܳ�ʼ�� NVIC �Ĵ���
//TIM_Cmd(TIM3, ENABLE); //��ʹ�� TIM3
//}
////��ʱ�� 3 �жϷ�������
//void TIM3_IRQHandler(void) //TIM3 �ж�
//{
//if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //��� TIM3 �����жϷ������
//{
//TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //��� TIM3 �����жϱ�־
//printf("hao");
//}
//}
void TIM4_IRQHandler(void) //TIM3 �ж�
{
if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //��� TIM3 �����жϷ������
{
TIM_ClearITPendingBit(TIM4, TIM_IT_Update ); //��� TIM3 �����жϱ�־
tim2++;
	printf("ni");
}
}
