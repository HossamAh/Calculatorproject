/*
 * keypadCFile1.c
 *
 * Created: 12/29/2021 2:28:24 AM
 *  Author: Hossam
 */ 
#include "keypad.h"

uint8 get_key_pressed()
{
	/*
	* COLs pins in LOWER nibble
	* ROWs pins in HIGHER nibble 
	*/
	
	#if (N_COLS == 3)
	uint8 keys[N_ROWS][N_COLS] ={
	{'7','8','9'},
	{'4','5','6'},
	{'1','2','3'}};
	#else
	uint8 keys[N_ROWS][N_COLS] ={
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'#','0','=','+'}};
	#endif 
	uint8 row=0,col=0;
	while(TRUE)
	{	
		for(col=0;col<N_COLS;col++)
		{
			/* make the col pin OUTPUT and low */
			SET_BIT(KEYPAD_PORT_DDR,col);
			CLEAR_BIT(KEYPAD_PORT_PORT,col);
			for(row=0;row<N_ROWS;row++)
			{
				/*Enable internal pull-up in row pins */
				CLEAR_BIT(KEYPAD_PORT_DDR,N_COLS+row);
				SET_BIT(KEYPAD_PORT_PORT,N_COLS+row);
				if(BIT_IS_CLEAR(KEYPAD_PORT_PIN,N_COLS+row))
				{
					/*key pressed*/
					return keys[row][col];
				}
			}
			CLEAR_BIT(KEYPAD_PORT_DDR,col);/*HIGH Impedance*/
		}	
	}
}