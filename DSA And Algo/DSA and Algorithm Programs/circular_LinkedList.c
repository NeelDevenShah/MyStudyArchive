#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
void linkedListTraversal(struct Node *head)
{
    struct Node *ptr=head;
    // //Here we cannot use the while(ptr !=head) as the first element would be the head and due to that the loop will not run 
    
    // do{
    //     printf("Element is %d\n", ptr->data);
    //     ptr=ptr->next;
    // }while(ptr!=head);
    //OR
    while(ptr->next !=head)
    {
        printf("Element is %d\n", ptr->data);
        ptr=ptr->next;
    }
    printf("Element is %d\n", ptr->data);
}
struct Node *insertAtFirst(struct Node *head, int data)
{
    struct Node *ptr=(struct Node *)malloc(sizeof(struct Node));
    ptr->data=data;

    struct Node *p=head->next;
    while(p->next != head)
    {
        p=p->next;
    }
    //At this point p points to the last node of the circular linked list
    p->next=ptr;
    ptr->next=head;
    head=ptr;
    return head;
}

int main()
{
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;

    //Allocate memory for nodes in the linked list in the heap
    head=(struct Node *)malloc(sizeof(struct Node));
    second=(struct Node *)malloc(sizeof(struct Node));
    third=(struct Node *)malloc(sizeof(struct Node));
    fourth=(struct Node *)malloc(sizeof(struct Node));

    //Link First And Second Nodes
    head->data=4;
    head->next=second;
    //Link Second And Third Nodes
    second->data=3;
    second->next=third;
    //Link Third And Fourth Nodes
    third->data=6;
    third->next=fourth;
    //Terminate The Fourth Node
    fourth->data=1;
    fourth->next=head;

    printf("Circular Linked List Before Insertion");
    linkedListTraversal(head);
    head=insertAtFirst(head, 54);
    head=insertAtFirst(head, 94);
    head=insertAtFirst(head, 33);
    head=insertAtFirst(head, 77);
    printf("Circular Linked List After Insertion\n");
    linkedListTraversal(head);
}