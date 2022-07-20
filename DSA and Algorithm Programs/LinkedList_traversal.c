#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
void linkedListTraversal(struct Node *ptr)
{
    while(ptr != NULL)
    {
        printf("Element: %d\n", ptr->data);
        ptr=ptr->next;
    }
};
int main()
{
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;

    //Allocate memory for the node of linked list in the heap
    head=(struct Node*)malloc(sizeof(struct Node));
    second=(struct Node*)malloc(sizeof(struct Node));
    third=(struct Node*)malloc(sizeof(struct Node));
    fourth=(struct Node*)malloc(sizeof(struct Node));

    //Link First And Second Nodes
    head->data=7;
    head->next=second;

    //Link Second And Third Nodes
    second->data=11;
    second->next=third;

    //Link Third And Fourth Nodes
    third -> data=41;
    third -> next=fourth;

    //Terminate The List At Fourth Node
    fourth->data=66;
    fourth->next=NULL;

    linkedListTraversal(head);
    return 0;
}