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
 //STM32F103ZE核心板
 
 串口实验 

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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	 LED_Init();
	 moto_init();
	 KEY_Init();
	exti_init(); 
anmimal_recognition_init();
	 T_Adc_Init();//内部温度传感器
	uart_init1(115200);
 usart_init2(9600);
	 TIM2_Int_Init(4999,7199);
//TIM3_Int_Init(4999,7199);
anmimal_test=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
  Hcsr04Init();		 //初始化与按键连接的硬件接口
	wifi_protocol_init();//wifi函数
	  sr04_value();//超声波值
	 	 Motor_Init();//直流电机使能
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Refresh();
//	 while(DHT11_Init()) //DHT11 初始化
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
杂类代码
************************************************/
 
void read_allnum()//温湿度判断
 {
		
		printf("温度:%dC,湿度:%d\r\n",temperature,humidity);//读温湿度值
	 	temp=Get_Temprate()/100;
		temp2=Get_Temprate()%100;
		sprintf(num,"CPU温度:%d.%.f\r\n",temp,(float)temp2);
		printf("%s",num);//读内部温度值
 }
 int car_hongwai()//红外障碍判断
{
   int left=1;
	 left= GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);//读取A4引脚的值
	printf("%d     ",left);//串口打印
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
			OLED_ShowChinese(0,32,11,16);//温
		OLED_ShowChinese(18,32,12,16);//度
	DHT11_Read_Data(&temperature,&humidity); //读取温湿度值
		sprintf((char *)olednum,":%d C",temperature);
		OLED_ShowString(34,32,olednum,16);
		OLED_ShowChinese(0,16,13,16);//湿
		OLED_ShowChinese(18,16,12,16);//度
	  sprintf((char *)olednum,":%dRH",humidity);
		OLED_ShowString(33,16,olednum,16);

		OLED_ShowChinese(90,16,16,16);//湿
		OLED_ShowChinese(108,16,17,16);//度
		OLED_ShowChinese(90,32,15,16);//湿
		OLED_ShowChinese(108,32,17,16);//度
		OLED_Refresh();//更新到oled显示屏内

}
