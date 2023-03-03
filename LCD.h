/*
 * LCD.h
 *
 * Created: 12/29/2021 2:29:00 AM
 *  Author: Hossam
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
/*Control PINS*/
#define LCD_CONTROL_PORT_DIR DDRC
#define LCD_CONTROL_PORT_PORT PORTC
#define LCD_RW_PIN 0
#define LCD_RS_PIN 1
#define LCD_E_PIN 2

/*Data PINS*/
#define MODE 4
#if MODE==4
#define LCD_DATA_PORT_DIR DDRC
#define LCD_DATA_PORT_PORT PORTC
#define LCD_DATA_PINS 0xf0
#else
#define LCD_DATA_PORT_DIR DDRD
#define LCD_DATA_PORT_PORT PORTD
#define LCD_DATA_PINS 0xff
#endif

/*Commands codes*/
#define clear_display 0x01
#define return_cursor 0x02 /*reset cursor position*/
#define shift_screen_left 0x18
#define shift_screen_right 0x1C
#define shifiting_cursor_left 0x10 /*cursor moving direction left*/
#define shifiting_cursor_right 0x14 /*cursor moving direction right*/
#define Display_on 0x0C /*On display with neither cursor nor blinking */
#define entry_mode 0x06
#if (MODE==4)
#define mode_set 0x28 /*4-bit mode*/
#else
#define mode_set 0x38 /*8-bit mode*/
#endif
#define SET_CURSOR_LOCATION 0x80 

void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(uint8* str);
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* str);
void LCD_display_num(uint32 num);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_clearscreen(void);


#endif /* LCD_H_ */