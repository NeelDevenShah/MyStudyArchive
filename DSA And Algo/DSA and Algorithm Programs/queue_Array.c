#include<stdio.h>
#include<stdlib.h>
//Queue follows FIFO(First In First Out)
struct queue
{
    int size;
    int f;
    int r;
    int *arr;
};
int isEmpty(struct queue *q)
{
    if(q->f==q->r)
    {
        return 1;
    }
    return 0;
}
int isFull(struct queue *q)
{
    if(q->r==q->size-1)
    {
        return 1;
    }
    return 0;
}
void enqueue(struct queue *q, int val)
{
    if(isFull(q))
    {
        printf("The queue is full\n");
    }
    else
    {
        //The array starts from the next index from that of the pointer's
        q->r++;
        q->arr[q->r]=val;
        printf("Enqueued element: %d\n", val);
    }
}
int dequeue(struct queue *q)
{
    int a=-1;
    if(isEmpty(q))
    {
        printf("The queue is empty\n");
    }
    else
    {
        q->f++;
        a=q->arr[q->f];
    }
    return a;
}
int main()
{
    struct queue *q=(struct queue*)malloc(sizeof(struct queue));
    q->size=4;
    q->f=q->r=-1;
    q->arr=(int *)malloc(q->size*sizeof(int));

    //Enqueue few elements
    enqueue(q, 12);
    enqueue(q, 15);
    enqueue(q, 1);
    printf("Dequeing element: %d\n", dequeue(q));
    printf("Dequeing element: %d\n", dequeue(q));
    printf("Dequeing element: %d\n", dequeue(q));
    enqueue(q, 45);
    enqueue(q, 75);
    enqueue(q, 15);

    if(isEmpty(q))
    {
        printf("Queue is empty\n");
    }
     if(isFull(q))
    {
        printf("Queue is full\n");
    }
    return 0;
}