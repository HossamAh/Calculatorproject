/*
 * LCD.c
 *
 * Created: 12/29/2021 2:28:47 AM
 *  Author: Hossam
 */ 
#include "LCD.h"
void LCD_sendCommand(uint8 command)
{
	#if MODE ==4
	LCD_CONTROL_PORT_PORT = 0;
	/*performing timing diagram of lcd writing instruction*/
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RS_PIN); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RW_PIN); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = (command&0xf0) | (LCD_DATA_PORT_PORT&0x0f); /* out the required command to the data bus D4 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = (command<<4)|(LCD_DATA_PORT_PORT&0x0f); /* out the required command to the data bus D4 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	#else
	/*performing timing diagram of lcd writing instruction*/
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RS_PIN); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RW_PIN); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	
	#endif
}
void LCD_init()
{
	/*Initialize control pins and data pins as Output pins*/
	LCD_CONTROL_PORT_DIR = (1<<LCD_RS_PIN)|(1<<LCD_RW_PIN)|(1<<LCD_E_PIN);
	#if MODE==8
	LCD_DATA_PORT_DIR = LCD_DATA_PINS;
	#else
	LCD_DATA_PORT_DIR = LCD_DATA_PINS |(LCD_CONTROL_PORT_DIR&0x0f);
	#endif
	
	/* Entry mode set*/
	LCD_sendCommand(return_cursor);
	
	LCD_sendCommand(entry_mode);
	/*set mode Command*/
	LCD_sendCommand(mode_set);
	/*clear display Command*/
	LCD_sendCommand(clear_display);
	/*Display_on Command*/
	LCD_sendCommand(Display_on);
}

void LCD_displayCharacter(uint8 character)
{
	#if MODE ==4

	/*performing timing diagram of lcd writing data*/
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_RS_PIN); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RW_PIN); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = (character&0xf0) | (LCD_DATA_PORT_PORT&0x0f); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = (character<<4)|(LCD_DATA_PORT_PORT&0x0f); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	#else
	/*performing timing diagram of lcd writing data*/
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_RS_PIN); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_RW_PIN); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	LCD_DATA_PORT_PORT = character; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CONTROL_PORT_PORT,LCD_E_PIN); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */	
	#endif
}
void LCD_displayString(uint8* str)
{
	uint8 string_itr=0;
	while(str[string_itr]!='\0')
	{
		LCD_displayCharacter(str[string_itr++]);
	}
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(str);
}
void LCD_display_num(uint32 num)
{
	
	char* str = (char*)malloc(sizeof(char));
	uint8 itr=0;
	while(num!=0)
	{
		str[itr++] = (num % 10)+'0';
		num /= 10;
		str = (char*)realloc(str,sizeof(char)*(itr+1));
	}
	str = (char*)realloc(str,sizeof(char)*(itr+1));
	str[itr] = '\0';
	uint8 i=0,j=itr-1;
	while(i<j)
	{
		uint8 temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	/*
	char str[16];
	uint8 itr =0;
	while(num!=0)
	{
		str[itr++] = (num % 10)+'0';
		num /= 10;
	}
	str[itr] = '\0';
	*/
	LCD_displayString(str);
	
}
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 address;
	/*0x(0|4)(col)*/
	switch(row)
	{
		case 0:
			address = col;
			break;
		case 1:
			address = 0x40+col;
			break;
	}
	LCD_sendCommand(address|SET_CURSOR_LOCATION);
}
void LCD_clearscreen(void)
{
	LCD_sendCommand(clear_display);
}