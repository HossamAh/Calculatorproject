/*
 * Calculator.h
 *
 * Created: 12/31/2021 12:03:41 PM
 *  Author: Hossam
 */ 


#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#define EXPRESSION_LENGTH_LIMIT 100
#include "LCD.h"
#include "keypad.h"
#include "Expression_evaluation.h"
void calculator_init(void);
void perform_calculation(void);
static int calculator_eval(char* expression);



#endif /* CALCULATOR_H_ */