#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Node*top=NULL;
void linkedListTraversal(struct Node* ptr)
{
    while(ptr !=NULL)
    {
        printf("Element: %d\n", ptr->data);
        ptr=ptr->next;
    }
}
int isEmpty(struct Node* top)
{
    if(top==NULL)
    {
        return 1;
    }
    return 0;
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
struct Node *push(struct Node* top, int val)
{
    if(isFull(top))
    {
        printf("Stack Overflow\n");
    }
    else
    {
        struct Node* n=(struct Node *)malloc(sizeof(struct Node));
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
        printf("Stack Overflow");
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
    //Note here the declaration of the struct top is made outside of the main, so that it can be accessable to all the function, it is speacially done for the pop function
    top=push(top, 78);
    top=push(top, 7);
    top=push(top, 8);
    top=push(top, 55);

    //linked List Traversal
    int element=pop(top);
    printf("Popped element is %d\n", element);
    linkedListTraversal(top);
    return 0;
}