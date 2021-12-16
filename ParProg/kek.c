#include <stdio.h>

int main()
{
    unsigned char c[4] = {'\\', 'x', 'a', 'b'};
    int x = * (int*)c;
    for (int i = 0; i < 4; i++)
    {
        printf("%02x ", c[i]);
    }
    printf("\n");
    printf("%d %08x\n", x, x);
    unsigned int m = 0xabcdef22;
    unsigned char * s = (unsigned char*) (&m);
    for (int i = 0; i < 4; i++)
    {
        printf("%02x ", s[i]);
    }
    int y = 0x000000ab;
    y *= 0x101;
    printf("%08x\n", y);
    s = (unsigned char *) "0123456789ABCDEFabcdef\\x";
    for (int i = 0; i < 24; i++)
    {
        printf("%02x %hhu %c\n", s[i], s[i], s[i]);
    }
    printf("\n");
    return 0;
}
