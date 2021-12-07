#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        
        out[4*i] = '\\';
        out[4*i+1] = 'x';
        unsigned char highest = in[i] >> 4;
        unsigned char lowest = in[i] & 0x0F; 
        out[4*i+2] = highest + (highest > 10 ? 'a' - 10 : '0');
        out[4*i+3] = lowest + (lowest > 10 ? 'a' - 10 : '0');
    }
}
