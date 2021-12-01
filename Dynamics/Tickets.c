#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    long long arr[5002];
    for (int i = 0; i < n+2; i++)
        arr[i] = -1;
    int a, b, c;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        if (i == 0)
        {
            arr[0] = a;
            arr[1] = b;
            arr[2] = c;
        }
        else
        {
            if ((a + arr[i-1] <= arr[i]) || (arr[i] == -1))
                arr[i] = a + arr[i-1];
            if ((b + arr[i-1] <= arr[i+1]) || (arr[i+1] == -1))
                arr[i+1] = b + arr[i-1];
            if ((c + arr[i-1] <= arr[i+2]) || (arr[i+2] == -1))
                arr[i+2] = c + arr[i-1];
        }
    }
    printf("%lld\n", arr[n-1]);
    return 0;
}
