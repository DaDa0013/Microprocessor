// 1) ���α׷��� �ʿ��� ��������� �����Ѵ�.

#include "stm32f10x_lib.h"
#include "System_func.h"

int main(void){
  // 2) �ý����� �ʱ�ȭ�Ѵ�. (Ÿ�̸�x�� Ŭ���� 72MHz�̴�.)
  Init_STM32F103();
  
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStruct;
  
  unsigned int LED_data = 0x0080;
  
  
  // 3) LED�� ����� �߻��ϴ� ��ƮA�� Ŭ�� �� ������� �����Ѵ�.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  // 4) Ÿ�̸�2 Ŭ�� �� Ÿ�̸�2 ���ֺ�, �ֱ���� �����Ѵ�.
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  
  TIM2_TimeBaseInitStruct.TIM_Prescaler = 7200 -1;
  TIM2_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM2_TimeBaseInitStruct.TIM_Period = 5000 -1;
  TIM2_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseInitStruct);
  
  // 5) Ÿ�̸�2�� ���۽�Ų��.
  TIM_Cmd(TIM2,ENABLE);
  // 6) TIM_GetFlagStatus(TIM2,TIM_IT_Update)�� üũ�ؼ� ������Ʈ �̺�Ʈ�� �߻��Ҷ����� ����ϸ�(1��). �̺�Ʈ�� �߻��ϸ�, TIM_ClearFlag�Լ��� pending bit�� Ŭ�����ϰ�, LED�� �����Ѵ�.
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