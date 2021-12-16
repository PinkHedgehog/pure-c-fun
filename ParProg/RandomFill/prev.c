#include <sys/types.h>
void randomfill(u_int64_t *out, size_t n, u_int64_t x, u_int64_t a, u_int64_t c)
{
    out[0] = x * a + c;
    for (size_t i = 1; i < n; i++)
    {
        out[i] = out[i-1] * a + c;
    }
}