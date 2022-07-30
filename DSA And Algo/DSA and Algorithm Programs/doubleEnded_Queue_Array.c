#include<stdio.h>
#include<stdlib.h>
struct Dequeue
{
    int size;
    int f;
    int r;
    int *arr;
};
int isFull(struct Dequeue *q)
{
    if(q->r == q->size-1)
    {
        return 1;
    }
    return 0;
}
int isEmpty(struct Dequeue *q)
{
    if(q->f == q->r)
    {
        return 1;
    }
    return 0;
}
void EnQueueR(struct Dequeue *q, int val)
{
    if(isFull(q))
    {
        printf("Queue has no space for inserion");
    }
    else
    {
        q->r++;
        q->arr[q->r]=val;
        printf("Successfully inserted element at rear\n");
    }
}
void EnQueueF(struct Dequeue *q, int val)
{
    if(q->f==-1)
    {
        printf("Queue has no space for insertion on front side\n");
    }
    else
    {
        q->arr[q->f]=val;
        q->f--;
        printf("Successfully inserted element at front\n");
    }
}
int DequeueR(struct Dequeue *q)
{
    if(isEmpty(q))
    {
        printf("There is no element in the queue\n");
        return -1;
    }
    else
    {
        int val=q->arr[q->r];
        q->r--;
        return val;
    }
}
int DequeueF(struct Dequeue *q)
{
    if(isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
    {
        q->f++;
        int val=q->arr[q->f];
        return val;
    }
}
void display(struct Dequeue *q)
{
    int i=0;
    while(i<=(q->r))
    {
        printf("Element: %d\n", q->arr[i]);
        i++;
    }
}
int main()
{
    struct Dequeue *q=(struct Dequeue *)malloc(sizeof(struct Dequeue));
    q->size=3;
    q->f=q->r=-1;
    q->arr=(int *)malloc(q->size*sizeof(int));
    EnQueueF(q, 15);
    EnQueueR(q, 95);
    display(q);
    EnQueueR(q, 59);
    display(q);
    printf("Element is dequeued at the front: %d", DequeueF(q));
    EnQueueF(q, 1);
    display(q);

    printf("Element is dequeued at the rear: %d", DequeueR(q));\
    display(q);
    return 0;
}