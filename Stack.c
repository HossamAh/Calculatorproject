#include "Stack.h"
stack* init_stack()
{
    stack* s = (stack*)malloc(sizeof(stack));
    s->llist.head = NULL;
    s->count = 0;
    return s;
}
void push(stack* s,int data)
{
    append_node(&s->llist,data);
    s->count++;

}
void pop(stack* s)
{
    delete_node(&s->llist,(s->count)-1);
    s->llist.count--;
    s->count--;
}
int top(stack* s)
{
    //return get_node(&s->llist,s->llist->count-1)->data;
    return get_last(&s->llist)->data;
}

void destroy_stack(stack* s)
{
    destroy_list(&s->llist);
    s->llist.count=0;
    s->count=0;
}
unsigned int is_empty(stack* s)
{
    return s->count<=0?1:0;
}
