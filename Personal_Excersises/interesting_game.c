/*
https://www.hackerrank.com/challenges/an-interesting-game-1/problem?h_r=profile
Sample Input:

2
5
1 3 5 7 9
5
7 4 6 5 9

Sample Output 1

BOB
ANDY

*/
#include <stdlib.h>
#include <stdio.h>

int PlayGame(long* arr, long n)
{
    if(n<=0)
        return 0001;
    else if (n==1)
        return 1;


    int winner = 0;
    
    while(n>0)
    {
        if(winner == 0)
            winner = 1;
        else 
            winner = (winner==1) ?  2 :  1;


        long largest_val_pos = 0;
        long i = 1;
        while(i<n)
        {
            largest_val_pos = (arr[i]>arr[largest_val_pos]) ? i : largest_val_pos;
            i++;
        }
        n = largest_val_pos;
    }
    return winner;
}
int main()
{

    int g;
    scanf("%d",&g);
    while(g>0)
    {
        long n;
        scanf("%ld",&n);
        long* arr = (long*)malloc(sizeof(long)*n);
        for(long i =0; i<n;i++)
            scanf("%ld", &arr[i]);

        int i_win = PlayGame(arr,n);
        switch(i_win)
        {          
            case 1:
                printf("BOB\n");
                break;
            case 2:
                printf("ANDY\n");
                break;
            default:
                printf("ERROR: %d", i_win);
            break;
        } 
        free(arr);           
        g--;
    }

    return 0;
}