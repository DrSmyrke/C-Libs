/*
** lcd.h
**
** LCD 5110 driver
** Target: ATMEGA :: AVR-GCC
**
** Written by DrSmyrke - 2012
*/

/* Lcd screen size */
#define LCD_X_RES 84
#define LCD_Y_RES 48
#define LCD_CACHE_SIZE ((LCD_X_RES * LCD_Y_RES) / 8)
#define LCD_TOTAL_PIXEL_COLUMNS (LCD_X_RES * 6) //<6> means 6 lines on LCD.

/* Pinout for LCD */
#define LCD_RST_PIN 	(1<<PD7)
#define LCD_SCE_PIN		(1<<PD6)
#define LCD_DC_PIN 		(1<<PD5)
#define LCD_DATA_PIN 	(1<<PD4)
#define LCD_CLK_PIN 	(1<<PD3)

#define LCD_PORT		PORTD
#define LCD_DDR			DDRD

/* Special Chars */
/*
#define ARROW_RIGHT	ICON(0)
#define ARROW_LEFT 	ICON(1)
#define ARROW_UP 	ICON(2)
#define ARROW_DOWN 	ICON(3)
#define STOP 		ICON(4)
#define PLAY	 	ICON(5)
*/
/* Function for my special characters */
#define	ICON(x)		'z'+1+x

void lcd_init(void);
void lcd_contrast(unsigned char contrast);
void lcd_clear(void);
void lcd_goto_xy(unsigned char x, unsigned char y);
void lcd_goto_xy_exact(unsigned char x, unsigned char y);
void lcd_chr(char chr);
void lcd_str(char* str);
void lcd_printBattery(unsigned char x,unsigned char y,unsigned char val);
void lcd_printAntena(unsigned char x,unsigned char y,unsigned char val);
void lcd_printCard(unsigned char x,unsigned char y,unsigned char val);
void lcd_chrNum(char chr,unsigned char x,unsigned char y);
void lcd_chrWD(char chr,unsigned char x,unsigned char y);



