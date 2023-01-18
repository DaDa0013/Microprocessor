
#include "stm32f10x_lib.h"
#include "System_func.h"

void Delay(vu32 nCount);

int main(void)
{
  Init_STM32F103();
  
  GPIO_InitTypeDef GPIO_InitStructure;

  unsigned int LED_data = 0x0080;    
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| 
  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  while (1)  {

    GPIO_ResetBits(GPIOA, LED_data);
  
    if(LED_data == 0x0080)
      LED_data = 0x0001;
     else
       LED_data<<=1;

    GPIO_SetBits(GPIOA, LED_data);
    Delay(0xAFFFF);
  }
  
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


