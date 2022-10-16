#include<stdio.h>
#include<stdlib.h>
//array->Input array
//i->index of node
void swapNodes(int *array)
{
    
}
void maxHeapify(int *array,int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left< array.length() && array[left]>array[largest])
    {
        largest=left;
    }
    if(right<array.length() && array[right]>array[largest])
    {
        largest=right;
    }
    if(largest != i)
    {
        swapNodes(array);
        maxHeapify(array, largest);
    }
}
int main()
{

}