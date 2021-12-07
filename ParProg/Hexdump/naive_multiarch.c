#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    char buf[5] = "";
    for (size_t i = 0; i < n; i++)
    {
        
        sprintf(buf, "\\x%02x", in[i]);
        memcpy(&out[4*i], buf, 4);
    }
}
