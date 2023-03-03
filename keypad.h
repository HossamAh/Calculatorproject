/*
 * keypad.h
 *
 * Created: 12/29/2021 2:28:10 AM
 *  Author: Hossam
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define N_COLS 4
#define N_ROWS 4
#define KEYPAD_PORT A
#if(KEYPAD_PORT == A)
#define KEYPAD_PORT_DDR DDRA
#define KEYPAD_PORT_PIN PINA
#define KEYPAD_PORT_PORT PORTA
#elif(KEYPAD_PORT == B)
#define KEYPAD_PORT_DDR DDRB
#define KEYPAD_PORT_PIN PINB
#define KEYPAD_PORT_PORT PORTB
#elif(KEYPAD_PORT == C)
#define KEYPAD_PORT_DDR DDRC
#define KEYPAD_PORT_PIN PINC
#define KEYPAD_PORT_PORT PORTC
#else
#define KEYPAD_PORT_DDR DDRD
#define KEYPAD_PORT_PIN PIND
#define KEYPAD_PORT_PORT PORTD
#endif
uint8 get_key_pressed();

#endif /* KEYPAD_H_ */