#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "linkedlist.h"
struct stack
{
    linked_list llist;
    int count;
};
typedef struct stack stack;

stack* init_stack();
void push(stack* s,int data);
void pop(stack* s);
int top(stack* s);
void destroy_stack(stack* s);
unsigned int is_empty(stack* s);


#endif // STACK_H_INCLUDED
