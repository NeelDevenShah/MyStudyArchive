#include<stdio.h>
void printArray(int *A, int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void bubbleSort(int *A, int n)
{
    int temp;
    //And the passes are equal to the (n-1)
    for(int i=0;i<=n-1;i++)//For number of passes
    {
        printf("Working on pass number %d\n", i+1);
        for(int j=0;j<n-1;j++)//For comparision in each pass
        {
            if(A[j]>A[j+1])
            {
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }
}
void bubbleSortAdaptive(int *A, int n)
{
    int temp;
    int isSorted;
    for(int i=0;i<n-1;i++)
    {
        printf("Working on the pass %d\n", i+1);
        isSorted=1;
        for(int j=0;j<n-1;j++)
        {
            if(A[j]>A[j+1])
            {
                temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
                isSorted=0;
            }
        }
        if(isSorted)
        {
            return;
        }
    }
}
int main()
{
    // int A[]={12, 54, 65, 7, 23, 9};
    // int n=6;//Write the size of the array here
    // int A[]={1,2,5,6,12,54,625,7,23,9};
    // int n=10;//Write the size of the array here
    int A[]={1,2,3,4,5,6};
    int n=6;//Write the size of the array here
    printArray(A,n);
    // bubbleSort(A,n);
    bubbleSortAdaptive(A,n);
    printArray(A,n);
    return 0;
}