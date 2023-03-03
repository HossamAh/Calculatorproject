/*
 * Calculator.c
 *
 * Created: 12/31/2021 12:03:54 PM
 *  Author: Hossam
 */ 
#include "LCD.h"
#include "keypad.h" 
#include "Expression_evaluation.h"
#include "Calculator.h"
void calculator_init(void)
{
	/*clear screen*/
	LCD_clearscreen();
	/*start at row 0 and col 0*/
	LCD_goToRowColumn(0,0);
	
}
void perform_calculation(void)
{
	/*display enter the expression message*/
	uint8 msg[] = "enter expression";
	LCD_displayString(msg);
	_delay_ms(500);
	LCD_clearscreen();
	/*initialize expression string*/
	uint8 expression[EXPRESSION_LENGTH_LIMIT];
	uint8 itr=0;
	uint8 char_pos = 0;
	uint8 character;
	expression[itr]='\0';
	/* enter expression till = sign and while iterator less than length limit l */
	while((character = get_key_pressed())!='=' && itr<EXPRESSION_LENGTH_LIMIT-1)
	{
		/*delete symbol is #*/
		if(itr>0 && character=='#')
		{
			itr--;
			LCD_goToRowColumn(0,char_pos);
			LCD_displayCharacter(' ');
			char_pos--;
			_delay_ms(500);
			continue;
		}
		/*shift screen if expression greater than 16 character*/
		char_pos = (char_pos==16?16:char_pos+1);
		bool first_check = 1;
		if(char_pos==16&&first_check)
		{
			first_check = 0;
			LCD_sendCommand(shift_screen_left);
		}
		else if(char_pos==16&& (!first_check))
		{
			first_check = 1;
			LCD_sendCommand(shift_screen_right);
		}
		LCD_displayCharacter(character);
		expression[itr++] = character;
		_delay_ms(500);
	}
	expression[itr] = '\0';
	LCD_goToRowColumn(1,0);
	LCD_displayCharacter('=');
	LCD_goToRowColumn(1,4);
	LCD_display_num(calculator_eval(expression));
}
static int calculator_eval(char* expression)
{
	return evalaute(expression);
}
