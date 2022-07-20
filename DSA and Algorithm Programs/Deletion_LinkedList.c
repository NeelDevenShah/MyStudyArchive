#include<stdio.h>
#include<stdlib.h>

//The deletion in the linked list can be done by the four ways
struct Node
{
    struct Node *next;
    int data;
};
void linkedListTraversal(struct Node *ptr)
{
    while(ptr !=NULL)
    {
        printf("\nElement: %d", ptr->data);
        ptr=ptr->next;
    }
}
//CASE 1:Deleting the first element from linked list
struct Node* deleteFirst(struct Node* head)
{
    struct Node *ptr=head;
    head=head->next;
    free(ptr);
    return head;
}
//CASE 2:Deleting the element at given index in linked list
struct Node* deleteAtIndex(struct Node* head, int index)
{
    struct Node *p=head;
    struct Node *q=head->next;
    for(int i=0;i<index-1;i++)
    {
        p=p->next;
        q=q->next;
    }
    p->next=q->next;
    free(q);
    return head;
}
//CASE 3:Deleting the last element from linked list
struct Node* deleteAtLast(struct Node* head)
{
    struct Node *p=head;
    struct Node *q=head->next;
    while(q->next !=NULL)
    {
        p=p->next;
        q=q->next;
    }
    p->next=NULL;
    free(q);
    return head;
}
//CASE 4:Deleting the element with given value from linked list
struct Node* deleteByValue(struct Node* head, int value)
{
    struct Node *p=head;
    struct Node *q=head->next;
    while(q->data !=value && q->data !=NULL)
    {
        p=p->next;
        q=q->next;
    }
    if(q->data==value)
    {
        p->next=q->next;
        free(q);
    }
    return head;
}
int main()
{
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;

    //Allocating the memory to the each node of the linked list
    head=(struct Node *)malloc(sizeof(struct Node));
    second=(struct Node *)malloc(sizeof(struct Node));
    third=(struct Node *)malloc(sizeof(struct Node));
    fourth=(struct Node *)malloc(sizeof(struct Node));

    //Link First and Second nodes
    head->data=4;
    head->next=second;
    //Link Second and Third nodes
    second->data=3;
    second->next=third;
    //Link Third and Fourth nodes
    third->data=8;
    third->next=fourth;
    //Terminate Fourth node
    fourth->data=1;
    fourth->next=NULL;

    printf("Linked List list before deletion");
    linkedListTraversal(head);

    // head=deleteFirst(head);
    head=deleteAtIndex(head, 2);
    //head=deleteAtLast(head);
    //head=deleteByValue(head, 8);
    printf("Linked list after deletion");
    linkedListTraversal(head);
    return 0;
}