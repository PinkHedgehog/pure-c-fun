#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    size_t i;
    size_t size = 16;
    char buf[5] = "";
    #pragma omp parallel for shared(out, in, n) private(buf)
    {
        for (i = 0; i < n; i += size)
        {

            sprintf(buf, "\\x%02x", in[i]);
            memcpy(&out[4*i], buf, 4);
        }
    }

}