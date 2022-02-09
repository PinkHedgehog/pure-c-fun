#include <stdio.h>
#include <stdlib.h>

union data
{
    char s[sizeof(int)];
    int x;
};

int main()
{
    char s1[] = {0x55, 0x61, 0x30, 0x28};
    printf("s1: ");
    for (size_t i = 0; i < sizeof(s1); i++)
    {
        printf("%02x ", s1[i]);
    }
    printf("\n");
    int x1 = *(int *) s1;
    printf("x1: %x\n", x1);
    union data d;
    d.x = x1;
    for (size_t i = 0; i < sizeof(int); i++)
    {
        printf("%02x ", d.s[i]);
    }
    printf("\n");
    return 0;
}
