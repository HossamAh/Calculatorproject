#ifndef __EXPRESSION_EVALUATION_H_
#define __EXPRESSION_EVALUATION_H_

#include "Stack.h"

unsigned int operator_precedency(char op);
int perform_operation(int val1,int val2,char op);
int evalaute(char[] );

#endif // __EXPRESSION_EVALUATION_H_
