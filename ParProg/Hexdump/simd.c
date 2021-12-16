#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    
    int x = 0x0000785c;
    for (size_t i = 0; i < n; i++)
    {
        int t = x | 
        memcpy(&out[4*i], &t, 4);
    }
    
}
