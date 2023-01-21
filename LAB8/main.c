// 1) 프로그램에 필요한 헤더파일, 타입, 함수를 선언한다.
#include "stm32f10x_lib.h"
#include "System_func.h"
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
unsigned int key2DoReMi(unsigned int key);
void Change_FREQ(unsigned int freq);
void STOP_FREQ();
int main(void){
// 2) 시스템을 초기화한다.
  Init_STM32F103();
// 3) 필요한 변수를 선언한다.
  u16 key_vlaue = 0; //입력되는 키값을 저장하는 변수
  u16 freq_value = 0; // 각키에 대한 주파수값을저장하는 변수
// 4) 타이머3 클럭 인가
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
// 5) 포트 A와 포트 C를 인가하고, 포트 C의  모든 핀을 50MHz, 입력 모드로 설정
// 한다.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC , ENABLE);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = 0x00FF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
// 6) 타이머3의 클럭설정.
  TIM_TimeBaseStructure.TIM_Period = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = 360 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //또는 0
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
// 7) 타이머 PWM 설정.
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInit(TIM3, &TIM_OCInitStructure);
// 8) TIMx_CCR1,TIMx_ARR레지스터를 enable한다.
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
// 9) 스위치로 값을 입력 받아 도,레,미,파,솔,라,시,도에 맞게 주파수를 설정한다.
  while (1){
    STOP_FREQ();
    while(!GPIO_ReadInputDataBit(GPIOC,0x00FF));
    key_vlaue = GPIO_ReadInputData(GPIOC) &0xFF;
    freq_value = key2DoReMi(key_vlaue);
    Change_FREQ(freq_value);
    while(GPIO_ReadInputDataBit(GPIOC,0x00FF));
  }//end while
}//end main
void STOP_FREQ(){
  TIM_Cmd(TIM3, DISABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_6);
}
void Change_FREQ(unsigned int freq){
  u16 tmp = (unsigned int)(100000/freq);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  TIM_Cmd(TIM3, DISABLE);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM3, DISABLE);
  TIM_SetAutoreload(TIM3,tmp);
  TIM_SetCompare1(TIM3,(unsigned int)(tmp/2));
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
}
unsigned int key2DoReMi(unsigned int key){
  unsigned int _ret=0;
  switch(key){
  case 0x01:
    _ret = 523;
  break;
  case 0x02:
    _ret = 587;
  break;
  case 0x04:
    _ret = 659;
  break;
  case 0x08:
    _ret = 698;
  break;
  case 0x10:
    _ret = 783;
  break;
  case 0x20:
    _ret = 880;
  break;
  case 0x40:
    _ret = 987;
  break;
  case 0x80:
    _ret = 1046;
  break;
  }
  return _ret;
}