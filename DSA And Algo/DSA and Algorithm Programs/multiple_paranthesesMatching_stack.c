#include<stdio.h>
#include<stdlib.h>
struct stack
{
    int size;
    int top;
    char *arr;
};
int isEmpty(struct stack *ptr)
{
    if(ptr->top==NULL)
    {
        return 1;
    }
    return 0;
}
int isFull(struct stack *ptr)
{
    if(ptr->top==ptr->size-1)
    {
        return 1;
    }
    return 0;
}
void push(struct stack *ptr, char val)
{
    if(isFull(ptr))
    {
        printf("Stack Overflow");
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top]=val;
    }
}
char pop(struct stack *ptr)
{
    if(isEmpty(ptr))
    {
        printf("Stack Underflow");
    }
    else
    {
        int val=ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}
int match(char a, char b)
{
    if((a=='{' && b=='}') || (a=='(' && b==')') || (a=='[' && b==']') || (a=='<' && b=='>'))
    {
        return 1;
    }
    return 0;
}
int Parenthesis(char *exp)
{
    //Create And Intialize Stack
    struct stack *sp=(struct stack *)malloc(sizeof(struct stack));
    sp->size=100;
    sp->top=-1;
    sp->arr=(char *)malloc(sp->size*sizeof(char));
    char popped_ch;
    
    for(int i=0;exp[i] !='\0';i++)
    {
        if(exp[i]=='{' || exp[i]=='(' || exp[i]=='[' || exp[i]=='<')
        {
            push(sp, exp[i]);
        }
        else if(exp[i]=='}' || exp[i]==')' || exp[i]==']' || exp[i]=='>')
        {
            if(isEmpty(sp))
            {
                return 0;
            }
            popped_ch=pop(sp);
            if(!match(popped_ch, exp[i]))
            {
                return 0;
            }
        }
    
    }
    if(isEmpty(sp))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char *exp="[4]-6((8){(9-8)})";
    if(Parenthesis(exp))
    {
        printf("The paranthesis is balanced");
    }
    else
    {
        printf("The paranthesis is not balanced");
    }
    return 0;
}