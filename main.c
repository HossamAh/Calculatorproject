/*
 * main.c
 *
 * Created: 12/29/2021 2:22:00 AM
 *  Author: Hossam
 */ 
#include "Calculator.h"
int main(void)
{
	LCD_init();
	char str[] = "Hello";
	LCD_displayString(str);
	_delay_ms(1000);
	calculator_init();
 	while(1)
    {
		while(get_key_pressed()!='#');
		LCD_clearscreen();
		perform_calculation();
		_delay_ms(1000); 
    }
}