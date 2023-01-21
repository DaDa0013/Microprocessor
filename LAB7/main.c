// 1) 프로그램에 필요한 헤더파일을 선언한다.

#include "stm32f10x_lib.h"
#include "System_func.h"

int main(void){
  // 2) 시스템을 초기화한다. (타이머x의 클럭은 72MHz이다.)
  Init_STM32F103();
  
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStruct;
  
  unsigned int LED_data = 0x0080;
  
  
  // 3) LED로 출력을 발생하는 포트A의 클럭 및 출력핀을 설정한다.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  // 4) 타이머2 클럭 및 타이머2 분주비, 주기등을 결정한다.
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  
  TIM2_TimeBaseInitStruct.TIM_Prescaler = 7200 -1;
  TIM2_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM2_TimeBaseInitStruct.TIM_Period = 5000 -1;
  TIM2_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseInitStruct);
  
  // 5) 타이머2를 동작시킨다.
  TIM_Cmd(TIM2,ENABLE);
  // 6) TIM_GetFlagStatus(TIM2,TIM_IT_Update)를 체크해서 업데이트 이벤트가 발생할때까지 대기하며(1초). 이벤트가 발생하면, TIM_ClearFlag함수로 pending bit를 클리어하고, LED를 점등한다.
  while (1){
    
    GPIO_ResetBits(GPIOA, LED_data);
    
    if(LED_data == 0x0080)
      LED_data = 0x0001;
    else
      LED_data<<=1;
    GPIO_SetBits(GPIOA, LED_data);

    while(TIM_GetFlagStatus(TIM2,TIM_IT_Update)==RESET);
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
  }//end while
} //end main