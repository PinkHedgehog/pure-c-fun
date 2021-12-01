#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    scanf("%d", &x);
    int * arr = (int*) malloc((x + 1) * sizeof(int));
    arr[0] = 1;
    arr[1] = 1;
    for (int i = 2; i <= x; i++)
    {
        arr[i] = arr[i - 1];
        if (i % 3 == 0)
            arr[i] += arr[i / 3]; 
    }
    printf("%d\n", arr[x]);
    free(arr);
    return 0;
}