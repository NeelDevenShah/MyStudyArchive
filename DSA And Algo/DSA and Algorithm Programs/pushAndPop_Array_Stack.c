#include<stdio.h>
#include<stdlib.h>

struct stack
{
    int size;
    int top;
    int *arr;
};
int isEmpty(struct stack *ptr)
{
    if(ptr->top==-1)
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
void push(struct stack *ptr, int val)
{
    if(isFull(ptr))
    {
        printf("Stackoverflow cannot push %d", val);
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top]=val; 
    }
}
int pop(struct stack *ptr)
{
    if(isEmpty(ptr))
    {
        printf("Stack underflow cannot pop the element");
    }
    else
    {
        int val=ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

int main()
{
    struct stack* s=(struct stack*)malloc(sizeof(struct stack));
    s->size=50;
    s->top=-1;
    s->arr=(int *)malloc(s->size*sizeof(int));
    printf("Stack has been created successfully\n");

    //Now lets check that is everything fine
    printf("Before pushing full= %d\n", isFull(s));
    printf("Before pushing empty= %d\n", isEmpty(s));

    //Pushing element in stack
    push(s, 1);
    push(s, 23);
    push(s, 99);
    push(s, 75);
    push(s, 3);
    push(s, 64);
    push(s, 57);
    push(s, 46);
    push(s, 89);
    push(s, 6);

    printf("After pushing full=%d\n", isFull(s));
    printf("After pushing empty=%d\n", isEmpty(s));

    //Poping out the elements
    //last in first out
    printf("Popped %d from the stack\n", pop(s));
    printf("Popped %d from the stack\n", pop(s));
    printf("Popped %d from the stack\n", pop(s));

    return 0;
}