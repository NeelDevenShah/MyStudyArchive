#include<stdio.h>
void printArray(int *A, int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
int partitation(int A[], int low, int high)
{
    int pivot=A[low];
    int i=low+1;
    int j=high;
    int temp;
    do
    {
        while(A[i]<pivot)
        {
            i++;
        }
        while(A[j]>pivot)
        {
            j--;
        }
        if(i<j)
        {
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
    }
    while(i<j);
    //The index of the i must be equal or more than j for changing the values

    //And than after we have to swap the smallest and the pivot
    //Here the A[low] is the pivot
    temp=A[low];
    A[low]=A[j];
    A[j]=temp;
    return j;
}
void quickSort(int A[], int low, int high)
{
    int partitionIndex;
    if(low<high)
    {
        partitionIndex=partitation(A, low, high);
        quickSort(A, low, partitionIndex-1);//Sort left one
        quickSort(A, partitionIndex+1, high);//Sort right one
    }
}
int main()
{
    // int A[]={3,5,2,13,12,3,2,13,45};
    int A[]={9,4,4,8,7,5,6};
    int n=7;
    int low=0;
    int high=n-1;
    printArray(A,n);
    quickSort(A, low, high);
    printArray(A, n);
    return 0;
}