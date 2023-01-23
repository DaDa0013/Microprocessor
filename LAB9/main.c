// 1) ���α׷��� �ʿ��� ��� ����
#include "stm32f10x_lib.h"
#include"system_func.h"
// 2) USART1���� �� ���ڸ� �����ϴ� �Լ�
void putch(u8 c);
// 3) USART1���� ���ڿ��� �����ϴ� �Լ�
void puts(u8 *s);
int main(void)
{
  Init_STM32F103();
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
// 4) ��ƮA(USART1)�� USART1�� Ŭ�� ����
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
  RCC_APB2Periph_USART1, ENABLE);
// 5) Tx���� Alternate function Push-Pull ����, Rx���� input floating ���� ����.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
/* 6) PC�� �ø��� ��ſ� �԰��� ���߱� ����,
���췹��Ʈ 9600bps, ����Ÿ ���� 8��Ʈ, �����Ʈ 1, �и�Ƽ ����,
�帧���� ����, �ۼ��ż���, SCLK�� disable, �񵿱�� ������� ��
���ϱ� ���� CPOL�� 0, CPHA�� 1�� ����. Last bit�� ���� SCLK�� ��µ�
disable���� ����. */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl =
  USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx |
  USART_Mode_Tx;
  USART_InitStructure.USART_Clock = USART_Clock_Disable;
  USART_InitStructure.USART_CPOL = USART_CPOL_Low;
  USART_InitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_InitStructure.USART_LastBit = USART_LastBit_Disable;
  USART_Init(USART1, &USART_InitStructure);
// 7) USART1�� Enable �Ѵ�.
  USART_Cmd(USART1, ENABLE);
// 8) �ѹ��ھ� Hello �� ����ϰ�, Wolrd!! ���ڿ��� ����Ѵ�.
  putch('H');
  putch('e');
  putch('l');
  putch('l');
  putch('o');
  puts("\n\rWorld!!");
  while (1);
}
void putch(u8 c)
{
  USART_SendData(USART1, c);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
void puts(u8 *s)
{
  while (*s != '\0')
  {
    putch(*s);
    s ++;
  }
}
