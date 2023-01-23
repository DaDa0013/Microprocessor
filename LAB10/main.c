// 1) 프로그램에 필요한 헤더 선언
#include "stm32f10x_lib.h"
#include"system_func.h"
#include "lcd.h"

void lcdInitHW(void);
void lcdBusyWait(void);
void lcdControlWrite(u8 data);
u8 lcdControlRead(void);
void lcdDataWrite(u8 data);
u8 lcdDataRead(void);
void lcdInit();
void lcdHome(void);
void lcdClear(void);
void lcdGotoXY(u8 x, u8 y);
void lcdPrintData(char* data, u8 nBytes);

int main(void)
{
  Init_STM32F103();
  
  lcdInit();
  
  lcdDataWrite('H');
  lcdDataWrite('e');
  lcdDataWrite('l');
  lcdDataWrite('l');
  lcdDataWrite('o');
  
  lcdGotoXY(7, 1);
  
  lcdPrintData("STM32!!", 7);
  
  while (1);
}

void lcdInitHW(void)
{
  RCC_APB2PeriphClockCmd(LCD_CTRL_PORT_CLK, ENABLE);
  GPIO_LCD.GPIO_Pin = LCD_CTRL_RS | LCD_CTRL_RW | LCD_CTRL_E;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_CTRL_PORT, &GPIO_LCD);
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS | LCD_CTRL_RW |LCD_CTRL_E );
  //초기 0
  
  RCC_APB2PeriphClockCmd(LCD_DATA_CLK, ENABLE);
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  GPIO_SetBits(LCD_DATA, 0x00FF ); //초기 풀업
}

void lcdBusyWait(void)
{
  // wait until LCD busy bit goes to zero
  // do a read from control register
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "control"
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); //초기 풀업
  
  // set R/W to "read"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RW | LCD_CTRL_E);
  
  LCD_DELAY; // wait
  
  while((GPIO_ReadInputDataBit(LCD_DATA, 1<<LCD_BUSY))) {
    GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
    LCD_DELAY; // wait
    LCD_DELAY; // wait
    GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
    LCD_DELAY; // wait
    LCD_DELAY; // wait
  }
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E);// clear "E" line
}

void lcdControlWrite(u8 data)
{
  // write the control byte to the display controller
  lcdBusyWait(); // wait until LCD not busy
  
  // set RS to "control"
  // set R/W to "write“
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS | LCD_CTRL_RW);
  
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_ResetBits(LCD_DATA, 0x00FF);
  GPIO_SetBits(LCD_DATA, data); // output data, 8bits
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E);// clear "E" line
  LCD_DELAY; // wait
  LCD_DELAY; // wait
}

u8 lcdControlRead(void)
{
  // read the control byte from the display controller
  u8 data;
  
  lcdBusyWait(); // wait until LCD not busy
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); //초기 풀업
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "control"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RW); // set R/W to "read"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  data = (GPIO_ReadInputData(LCD_DATA)); // input data, 8bits
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
  
  return data;
}

void lcdDataWrite(u8 data)
{
  // write a data byte to the display
  lcdBusyWait(); // wait until LCD not busy
  
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RS); // set RS to "data"
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_RW); // set R/W to "write"
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_ResetBits(LCD_DATA,0x00FF);
  GPIO_SetBits(LCD_DATA, data&0xFF);
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
}

u8 lcdDataRead(void)
{
  // read a data byte from the display
  u8 data;
  lcdBusyWait(); // wait until LCD not busy
  
  GPIO_LCD.GPIO_Pin = 0x00FF;
  GPIO_LCD.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_LCD.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LCD_DATA, &GPIO_LCD);
  
  GPIO_SetBits(LCD_DATA, 0x00FF ); //초기 풀업
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_RS | LCD_CTRL_RW);// set RS to “data”
  GPIO_SetBits(LCD_CTRL_PORT, LCD_CTRL_E); // set "E" line
  
  LCD_DELAY; // wait
  LCD_DELAY; // wait
  
  data = GPIO_ReadInputData(LCD_DATA);
  GPIO_ResetBits(LCD_CTRL_PORT, LCD_CTRL_E); // clear "E" line
  
  return data;
}

void lcdInit()
{
  // 하드웨어 초기화
  lcdInitHW();
  // LCD function set
  lcdControlWrite(LCD_FUNCTION_DEFAULT);
  /// clear LCD
  lcdControlWrite(1<<LCD_CLR);
  // set entry mode
  lcdControlWrite(1<<LCD_ENTRY_MODE | 1<<LCD_ENTRY_INC);
  // set display to on
  lcdControlWrite(1<<LCD_ON_CTRL | 1<<LCD_ON_DISPLAY |
                  1<<LCD_ON_CURSOR | 1<<LCD_ON_BLINK);
  // move cursor to home
  lcdControlWrite(1<<LCD_HOME);
  // set data address to 0
  lcdControlWrite(1<<LCD_DDRAM | 0x00);
}

void lcdHome(void)
{
  // move cursor to home
  lcdControlWrite(1<<LCD_HOME);
}

void lcdClear(void)
  {
  // clear LCD
  lcdControlWrite(1<<LCD_CLR);
}
void lcdGotoXY(u8 x, u8 y)
{
  u8 DDRAMAddr = x;
  
  // remap lines into proper order
  switch(y){
    case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
    case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
    case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
    case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
    default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
  }
  
  // set data address
  lcdControlWrite((1<<LCD_DDRAM) | DDRAMAddr);
}

void lcdPrintData(char* data, u8 nBytes)
{
  u8 i;
  
  // check to make sure we have a good pointer
  if (!data)
    return;
  
  // print data
  for(i=0; i<nBytes; i++) {
    lcdDataWrite(data[i]);
  }
}