#include <stdio.h>
#include <stdlib.h>

int main()
{
    //int arr[10] = {11,66,33,42,234,7,85,12,5,43};
    int size = 20;
    int* arr = (int*)malloc(sizeof(int)*size);
    for(int i = 0; i <size; i++)
    {
        arr[size-i-1] = i; 
    }
    printf("Before-----\nArr[%d] : ",size);
    for(int i =0; i<size; i++)
        printf("%d ", arr[i]);
    int pass = 0; 
    int aCount = 0;
    int mCount = 0;

    while(pass == 0)
    {   
        pass = 1;
        for(int i = 0; i <size-1;i++)    
        {
            aCount++;
            if(arr[i]>arr[i+1])
            {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                pass = 0;
                mCount++;
            }
        }
    }
    printf("\nAfter-----\nArr[%d] : ",size);

    for(int i =0; i<size; i++)
        printf("%d ", arr[i]);
    
    printf("\nAccess Count: %d ", aCount);
    printf("\nModify Count: %d ", mCount);



    return 0;
}