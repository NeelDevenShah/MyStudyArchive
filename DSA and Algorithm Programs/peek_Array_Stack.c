#include<stdio.h>
#include<stdlib.h>
//Stack follows LIFO(Last In First Out)
struct stack
{
    int size;
    int top;
    int *arr;
};
int isFull(struct stack *ptr)
{
    if(ptr->top==ptr->size-1)
    {
        return 1;
    }
    return 0;
}
int isEmpty(struct stack *ptr)
{
    if(ptr->top==-1)
    {
        return 1;
    }
    return 0;
}
void push(struct stack* ptr, int val)
{
    if(isFull(ptr))
    {
        printf("Stack overrflow cannot insert %d in the stack", val);
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top]=val;
    }
}
int pop(struct stack* ptr)
{
    if(isEmpty(ptr))
    {
        printf("Stack underflow cannot pop the value");
    }
    else
    {
        int val=ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}
int peek(struct stack* ptr, int i)
{
    //We will use the following format for finding the index number
    int arrayInd=ptr->top-i+1;
    if(arrayInd<0)
    {
        printf("Not a valid positon for the stack\n");
        return -1;
    }
    else
    {
        return ptr->arr[arrayInd];
    }
}
int main()
{
    struct stack* s=(struct stack *)malloc(sizeof(struct stack));
    s->size=50;
    s->top=-1;
    s->arr=(int*)malloc(s->size*sizeof(int));
    printf("Stack has been created successfully\n");
    printf("Before pushing, Full: %d\n", isFull(s));
    printf("Before pushing, Empty: %d\n", isEmpty(s));

    push(s, 1);
    push(s, 23);
    push(s, 56);
    push(s, 66);
    push(s, 2);
    push(s, 88);
    push(s, 99);
    push(s, 51);
    //printing values from the stack using the peek
    for(int j=1;j<=s->top+1;j++)
    {
        printf("value at position %d is %d\n", j, peek(s, j));
    }
}