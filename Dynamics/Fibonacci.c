#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const ushort size = (ushort) -1;
ushort arr[size];

ushort fib_rec(ushort n)
{
    if (n <= 1)
        return n;
    else
        return fib_rec(n-1) + fib_rec(n-2);
}

ushort fib_arr(ushort n)
{
    
    arr[0] = 0;
    arr[1] = 1;
    for (ushort i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n];
}

ushort fib_tail(ushort n, ushort i, ushort cur, ushort pre)
{
    if ((n == cur) || (n == pre))
        return n;
    if (i == n)
        return cur;
    return fib_tail(n, i + 1, cur + pre, cur);
}

ushort fib_iter(ushort n)
{
    if (n <= 1)
        return n;
    else
    {
        ushort a = 0;
        ushort b = 1;
        for (ushort i = 2; i <= n; i++)
        {
            ushort c = a + b;
            a = b;
            b = c;

        }
        return b;
    }
}

int main()
{
    ushort x;
    scanf("%hu", &x);
    printf("Fibonacci-recursive: %hu\n", fib_rec(x));
    printf("Fibonacci-array: %hu\n", fib_arr(x));
    printf("Fibonacci-recursive-tail: %hu\n", fib_tail(x, 1, 1, 0));
    printf("Fibonacci-iterative: %hu\n", fib_iter(x));
    return 0;
}