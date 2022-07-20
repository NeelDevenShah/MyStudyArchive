#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node* next;
};
struct Node* top=NULL;

int isEmpty(struct Node* top)
{
    if(top==NULL)
    {
        return 0;
    }
    return 1;
}
int isFull(struct Node* top)
{
    struct Node* p=(struct Node*)malloc(sizeof(struct Node));
    if(p==NULL)
    {
        return 1;
    }
    return 0;
}
void linkedListTraversal(struct Node* ptr)
{
    while(ptr != NULL)
    {
        printf("Element: %d\n", ptr->data);
        ptr=ptr->next;
    }
}
int peek(int pos)
{
    struct Node* ptr=top;
    for(int i=0;(i<pos-1 && ptr!=NULL);i++)
    {
        ptr=ptr->next;
    }
    if(ptr!=NULL)
    {
        return ptr->data;
    }
    else{
        return -1;
    }
}
struct Node* push(struct Node* top, int val)
{
    if(isFull(top))
    {
        printf("Stack Overflow");
    }
    else
    {
        struct Node* n=(struct Node*)malloc(sizeof(struct Node));
        n->data=val;
        n->next=top;
        top=n;
        return top;
    }
}
int pop(struct Node* tp)
{
    if(isEmpty(tp))
    {
        printf("Stack Underflow");
    }
    else
    {
        struct Node* n=tp;
        top=(tp)->next;
        int x=n->data;
        free(n);
        return x;
    }
}

int main()
{
    top=push(top, 28);
    top=push(top, 18);
    top=push(top, 15);
    top=push(top, 7);

    linkedListTraversal(top);
    for(int i=1;i<=4;i++)
    {
        printf("Value at position %d is %d", i, peek(i));
    }
    return 0;
}