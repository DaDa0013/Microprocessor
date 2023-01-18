#include "stm32f10x_lib.h"
#include "System_func.h"
u8 flag=0;

unsigned char time_10ms= 0,time_100ms=0, time_1s=0, time_10s=0;
char Time_STOP=1;

void GPIO_Configuration(void);
void Delay(vu32 nCount);

int main(void)
{
  
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X67,
0X77,0X7C,0X39,0X5E,0X79,0X71,0X08,0X80};

  Init_STM32F103();
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| 
  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // 7) 외부 인터럽트0가 상승엣지에서 발생되게 설정한다
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
   
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  GPIO_Configuration();
  
  while (1) {

    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2| GPIO_Pin_3);
    GPIO_ResetBits(GPIOB, GPIO_Pin_3); //C0 선택 (가장왼쪽의 FND)
    
    GPIO_ResetBits(GPIOC, 0x00FF); // 0~7핀을 의미
    GPIO_SetBits(GPIOC, FND_DATA_TBL[time_10ms]);
    Delay(0x1FFF);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2| GPIO_Pin_3);
    GPIO_ResetBits(GPIOB, GPIO_Pin_2); //C1
    
    GPIO_ResetBits(GPIOC, 0x00FF);
    GPIO_SetBits(GPIOC, FND_DATA_TBL[time_100ms]);
    Delay(0x1FFF);

    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2| GPIO_Pin_3);
    GPIO_ResetBits(GPIOB, GPIO_Pin_1); //C2
    GPIO_ResetBits(GPIOC, 0x00FF);
    
    GPIO_SetBits(GPIOC, FND_DATA_TBL[time_1s]|0x80); //GPIO_Pin_0 대신x01
    Delay(0x1FFF);
    
    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2| GPIO_Pin_3);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0); //C3
    
    GPIO_ResetBits(GPIOC, 0x00FF);
    GPIO_SetBits(GPIOC, FND_DATA_TBL[time_10s]);
    Delay(0x1FFF);

//인터럽트에 대한 처리
    if(Time_STOP==0) continue; //인터럽트에 의한 Stop/Resume 처리
    
    time_10ms++;
    
    if(time_10ms == 10){
      time_10ms = 0;
      time_100ms++ ;}
    if(time_100ms == 10){
      time_100ms = 0;
      time_1s++ ;}
    if(time_1s == 10){
      time_1s = 0;
      time_10s++ ;}
    if(time_10s == 10){
      time_10s = 0;
    } 
  }
}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void GPIO_Configuration(void){
  
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOB, &GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOC, &GPIO_InitStructure);

}