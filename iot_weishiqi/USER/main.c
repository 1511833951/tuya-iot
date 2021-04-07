#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "wifi.h"
#include "HC-SR04.h" 
#include "dht11.h"
#include "mcu_api.h"
#include "protocol.h" 
#include "oled.h"
#include "bmp.h"
/************************************************
 //STM32F103ZE���İ�
 
 ����ʵ�� 

************************************************/
char  num[100];
unsigned char olednum[100];
int i=0;
short temp;
short temp2;
void T_Adc_Init();
int anmimal_test;
extern unsigned char mcu_get_wifi_work_state(void);
void OLED_SHOW();
void read_allnum();
short Get_Temprate();
u8 temperature;  	    
	u8 humidity;  
u32 didatime=0;
 	u8 t;  
	u16 len=0;	
	u16 times=0;
extern int tim2;
 int car_hongwai();
 int main(void)
 {			    
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	 LED_Init();
	 moto_init();
	 KEY_Init();
	exti_init(); 
anmimal_recognition_init();
	 T_Adc_Init();//�ڲ��¶ȴ�����
	uart_init1(115200);
 usart_init2(9600);
	 TIM2_Int_Init(4999,7199);
//TIM3_Int_Init(4999,7199);
anmimal_test=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
  Hcsr04Init();		 //��ʼ���밴�����ӵ�Ӳ���ӿ�
	wifi_protocol_init();//wifi����
	  sr04_value();//������ֵ
	 	 Motor_Init();//ֱ�����ʹ��
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_Refresh();
//	 while(DHT11_Init()) //DHT11 ��ʼ��
//{
//delay_ms(200);
//printf("errror");
//	delay_ms(200);
//	
//}
 moto_open();
 	while(1)
	{
		//	delay_ms(1000);
 wifi_uart_service();
//delay_ms(1000);
//car_hongwai();	
OLED_SHOW();		
		sr04_value();
		GPIO_ResetBits(GPIOF,GPIO_Pin_11);
		GPIO_SetBits(GPIOF,GPIO_Pin_12);
   }
}
 

/************************************************
�������
************************************************/
 
void read_allnum()//��ʪ���ж�
 {
		
		printf("�¶�:%dC,ʪ��:%d\r\n",temperature,humidity);//����ʪ��ֵ
	 	temp=Get_Temprate()/100;
		temp2=Get_Temprate()%100;
		sprintf(num,"CPU�¶�:%d.%.f\r\n",temp,(float)temp2);
		printf("%s",num);//���ڲ��¶�ֵ
 }
 int car_hongwai()//�����ϰ��ж�
{
   int left=1;
	 left= GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//��ȡA4���ŵ�ֵ
	printf("%d     ",left);//���ڴ�ӡ
	if(tim2%10==1)
	{
		delay_ms(500);
		if(left==0)
			len++;
	}
	if((len==5)&&(tim2<100))
	{
	moto_open();
		len=0;
	}
	return left;
}
void OLED_SHOW()
{
	char value;
	//OLED_ShowPicture(0,0,128,8,BMP1);
			OLED_ShowChinese(0,32,11,16);//��
		OLED_ShowChinese(18,32,12,16);//��
	DHT11_Read_Data(&temperature,&humidity); //��ȡ��ʪ��ֵ
		sprintf((char *)olednum,":%d C",temperature);
		OLED_ShowString(34,32,olednum,16);
		OLED_ShowChinese(0,16,13,16);//ʪ
		OLED_ShowChinese(18,16,12,16);//��
	  sprintf((char *)olednum,":%dRH",humidity);
		OLED_ShowString(33,16,olednum,16);

		OLED_ShowChinese(90,16,16,16);//ʪ
		OLED_ShowChinese(108,16,17,16);//��
		OLED_ShowChinese(90,32,15,16);//ʪ
		OLED_ShowChinese(108,32,17,16);//��
		OLED_Refresh();//���µ�oled��ʾ����

}
