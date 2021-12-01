#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    int l[1024];
    int arr[1024];
    int prev[1024];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i+1]);
        prev[i+1] = 0;
    }
    l[0] = 0;
    l[1] = 1;
    prev[0] = 0;
    for (int i = 2; i <= n; i++)
    {
        int tmpMax = 0;
        for (int j = 1; j < i; j++)
        {
            if ((arr[j] < arr[i]) && (tmpMax < l[j]))
            {
                tmpMax = l[j];
                prev[i] = j;
            }
        }
        l[i] = 1 + tmpMax;
        
    }
    int tmpMax = 0;
    for (int i = 1; i <= n; i++)
    {
        // printf("%d ", l[i]);
        if (l[tmpMax] <= l[i])
            tmpMax = i;
    }
    // printf("\n");
    int lmax = l[tmpMax];
    // printf("%d %d\n", tmpMax, lmax);
    for (int i = 0; i < lmax; i++)
    {
        l[i] = arr[tmpMax];
        tmpMax = prev[tmpMax];
    }
    for (int i = lmax - 1; i >= 0; i--)
    {
        printf("%d ", l[i]);
    }
    printf("\n");
    
    return 0;
}

/*
8
5 2 8 6 3 6 9 7

*/