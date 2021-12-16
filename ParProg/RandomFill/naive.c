#include <stdlib.h>

/*
* `x` is seed, `a` is amplifier, `c` is some constant
*/
void randomfill(u_int64_t *out, size_t n, u_int64_t x, u_int64_t a, u_int64_t c)
{
    for (; n; n--)
    {
        x = x * a + c;
        *out++ = x;
    }
}