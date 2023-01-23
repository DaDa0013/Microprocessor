// 1) 프로그램에 필요한 헤더 선언
#include "stm32f10x_lib.h"
#include"system_func.h"
// 2) USART1으로 한 문자를 전송하는 함수
void putch(u8 c);
// 3) USART1으로 문자열을 전송하는 함수
void puts(u8 *s);
int main(void)
{
  Init_STM32F103();
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
// 4) 포트A(USART1)와 USART1의 클럭 설정
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
  RCC_APB2Periph_USART1, ENABLE);
// 5) Tx핀은 Alternate function Push-Pull 으로, Rx핀은 input floating 으로 설정.
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
/* 6) PC의 시리얼 통신와 규격을 맞추기 위해,
보우레이트 9600bps, 데이타 길이 8비트, 스톱비트 1, 패리티 없음,
흐름제어 없음, 송수신설정, SCLK핀 disable, 비동기식 방법으로 통
신하기 위해 CPOL은 0, CPHA는 1로 설정. Last bit에 따른 SCLK핀 출력도
disable으로 설정. */
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
// 7) USART1을 Enable 한다.
  USART_Cmd(USART1, ENABLE);
// 8) 한문자씩 Hello 를 출력하고, Wolrd!! 문자열을 출력한다.
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
