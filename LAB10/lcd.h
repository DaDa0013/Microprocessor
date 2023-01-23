// port and pins you will use for control lines
#define LCD_CTRL_PORT_CLK RCC_APB2Periph_GPIOC
#define LCD_CTRL_PORT GPIOC
#define LCD_CTRL_RS GPIO_Pin_0
#define LCD_CTRL_RW GPIO_Pin_1
#define LCD_CTRL_E GPIO_Pin_2
// port you will use for data lines
#define LCD_DATA GPIOA
#define LCD_DATA_CLK RCC_APB2Periph_GPIOA
// LCD display geometry
// change these definitions to adapt settings
#define LCD_LINES 2 // visible lines
#define LCD_LINE_LENGTH 16 // line length (in characters)
// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR 0x00
#define LCD_LINE1_DDRAMADDR 0x40
#define LCD_LINE2_DDRAMADDR 0x14
#define LCD_LINE3_DDRAMADDR 0x54
// LCD delay
#define LCD_DELAY asm ("nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n");
// writing:
#define LCD_CLR 0 // DB0: clear display
#define LCD_HOME 1 // DB1: return to home position
#define LCD_ENTRY_MODE 2 // DB2: set entry mode
#define LCD_ENTRY_INC 1 // DB1: increment
#define LCD_ENTRY_SHIFT 0 // DB2: shift
#define LCD_ON_CTRL 3 // DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY 2 // DB2: turn display on
#define LCD_ON_CURSOR 1 // DB1: turn cursor on
#define LCD_ON_BLINK 0 // DB0: blinking cursor
#define LCD_MOVE 4 // DB4: move cursor/display
#define LCD_MOVE_DISP 3 // DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT 2 // DB2: move right (0-> left)
#define LCD_FUNCTION 5 // DB5: function set
#define LCD_FUNCTION_8BIT 4 // DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3 // DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2 // DB2: 5x10 font (0->5x7 font)
#define LCD_CGRAM 6 // DB6: set CG RAM address
#define LCD_DDRAM 7 // DB7: set DD RAM address
// reading:
#define LCD_BUSY 7 // DB7: LCD is busy
// Default LCD setup
// this default setup is loaded on LCD initialization
#ifdef LCD_DATA_4BIT
#define LCD_FDEF_1 (0<<LCD_FUNCTION_8BIT)
#else
#define LCD_FDEF_1 (1<<LCD_FUNCTION_8BIT)
#endif
#define LCD_FDEF_2 (1<<LCD_FUNCTION_2LINES)
#define LCD_FUNCTION_DEFAULT ((1<<LCD_FUNCTION) | LCD_FDEF_1 | LCD_FDEF_2)
#define LCD_MODE_DEFAULT ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC))
GPIO_InitTypeDef GPIO_LCD;