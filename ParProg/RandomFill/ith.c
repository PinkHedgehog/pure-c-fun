/*
* `x` is seed, `a` is amplifier, `c` is some constant
*/
#include <sys/types.h>
u_int64_t u_int64_t_pow(u_int64_t a, size_t n)
{
    u_int64_t res = 1;
    for (;n > 0; n >>= 1)
    {
        if (n & 1) res *= a;
        a *= a;
    }
    return  res;
}

void randomfill(u_int64_t *out, size_t n, u_int64_t x, u_int64_t a, u_int64_t c)
{
    for (size_t i = 0; i < n; i++)
    {
        u_int64_t tmp = u_int64_t_pow(a, i+1);
        out[i] = x * tmp + c * (tmp - 1) / (a - 1);
    }
}

