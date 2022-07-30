#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void printArray(int *A, int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }
    printf("\n");
}
int maximum(int A[], int n)
{
    int max=INT_MIN;
    //Here the INT_Min is an method of the c/c++ compiler which sets the lowest possible value of that variable
    for(int i=0;i<n;i++)
    {
        if(max<A[i])
        {
            max=A[i];
        }
    }
    return max;
}
void countSort(int *A, int n)
{
    int i, j;
    //Find the maximum element in A
    int max=maximum(A, n);

    //Create the count Array
    int *count=(int *)malloc((max+1)*sizeof(int));

    //Initialize the array element to 0
    for(int i=0;i<max+1;i++)
    {
        count[i]=0;
    }
    
    //Increment the corresponding index in the count array
    //Here in the for loop we are doing the two works together, So getting the value at the ith index in array and making increment of that index in the count array
    for(int i=0;i<n;i++)
    {
        count[A[i]]=count[A[i]]+1;
    }

    i=0;//Counter for count array
    j=0;//Counter for given array A

    while(i<=max)
    {
        if(count[i]>0)
        {
            A[j]=i;
            j++;
            count[i]=count[i]-1;
        }
        else
        {
            i++;
        }
    }
}
int main()
{
    int A[]={9,1,4,14,4,15,6};
    int n=7;
    printArray(A, n);
    countSort(A, n);
    printArray(A, n);
    return 0;
}