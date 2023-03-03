#include "Expression_evaluation.h"

unsigned int operator_precedency(char op)
{
    if(op=='*' || op =='/')
        return 2;
    if(op=='+'||op=='-')
        return 1;
    return 0;
}
int perform_operation(int val1,int val2,char op)
{
    int res;
    switch(op)
    {
        case '+':
            res = val1+val2;
            break;
        case '-':
            res = val1-val2;
            break;
        case '*':
            res = val1*val2;
            break;
        case '/':
            res = val1/val2;
            break;
        default:
            break;
    }
    return res;
}
int evalaute(char expression[])
{
    /* initialize values and operators stacks*/
    stack* values = init_stack();
    stack* operators = init_stack();
    /* Initialize string characters iterator*/
    int i=0;

    /* Iterate over the expression*/
    while(expression[i]!='\0')
    {
        /*empty space hanlde*/
        if(expression[i]==' ')
            {i++; continue;}
        /* numerical values handler*/
        else if(expression[i] >='0' && expression[i] <='9')
        {
            int value=0;/* Initialize value variable*/
            /*Iterate over all number's digits*/
            while(expression[i] >='0' && expression[i] <='9')
            {
                value=value*10 + (expression[i]-'0');
                i++;
            }
            /*decrease characters iterator to start the next cycle with the first character after the number
            * because there is increment statement after the whole cycle.
            */
            i--;
            /*push value to values stack*/
            push(values,value);
        }
        else if(expression[i] =='(')/* open bracket handler*/
        {
            /*Push open bracket to indicate start of operations inside braces*/
            push(operators,expression[i]);
        }
        else if(expression[i]==')')/*closed bracket handler*/
        {
            /* Start evaluate operations inside the brackes from the closed bracket back to the open bracket*/
            while((is_empty(operators)==0) && top(operators)!='(')
            {
                int val1 = top(values);
                pop(values);
                int val2 = top(values);
                pop(values);
                char op = top(operators);
                pop(operators);
                push(values,perform_operation(val2,val1,op));
            }
            /* pop the open bracket*/
            if(is_empty(operators)==0)
                pop(operators);
        }
        else /*Operator handler*/
        {
            /*if the operator on the top of stack has higher precednecy then it has to be evalauted before psuh operands of anthor operator with lower precedency*/
            if((is_empty(operators)==0) && (operator_precedency(top(operators)) >= operator_precedency(expression[i])))
            {
                /*evalaute the higher precedency operation*/
                int val1 = top(values);
                pop(values);
                int val2 = top(values);
                pop(values);
                char op = top(operators);
                pop(operators);
                push(values,perform_operation(val2,val1,op));
            }
            else
            {
                /* operator doesn't have priority to be evalauted now*/
                push(operators,expression[i]);
            }
        }
        /* Increase iterator*/
        i++;
    }
    /* the whole expression has converted to values and operators in the values and operators stack without any braces and precedency issues*/
    /* Evaluating the expression*/
    while(is_empty(operators)==0)
    {
        int val1 = top(values);
        pop(values);
        int val2 = top(values);
        pop(values);
        char op = top(operators);
        pop(operators);
        push(values,perform_operation(val2,val1,op));
    }
    int result = top(values);
    destroy_stack(values);
    destroy_stack(operators);
    return result;
}
