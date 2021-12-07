#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    size_t i;
    size_t size = 16;
    unsigned char highest;
    unsigned char lowest;
    #pragma omp parallel for shared(out, in, n) private(i)
        for (i = 0; i < n; i += size)
        {

            out[4*i] = '\\';
            out[4*i+1] = 'x';
            highest = in[i] >> 4;
            lowest = in[i] & 0x0F; 
            out[4*i+2] = highest + (highest > 10 ? 'a' - 10 : '0');
            out[4*i+3] = lowest + (lowest > 10 ? 'a' - 10 : '0');
        }
}