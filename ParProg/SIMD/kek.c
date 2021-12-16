#include <emmintrin.h>
#include <mmintrin.h>
#include <stdio.h>
#include <sys/types.h>
#include <tmmintrin.h>
#include <x86intrin.h>

int main()
{
    unsigned char src[8] = {0x57, 0x30, 0x33, 0x44, 0x17, 0x5c, 0x78, 0x23};
    unsigned char msk[8] = {0xF0, 0x00, 0x00, 0x0A, 0x0B, 0x0A, 0x01, 0xFF};
    __m64 x = _mm_set_pi8(src[7],src[6],src[5],src[4],src[3],src[2],src[1],src[0]);
    __m64 mask = _mm_set_pi8(msk[7],msk[6],msk[5],msk[4],msk[3],msk[2],msk[1],msk[0]);
    __m64 y =_mm_shuffle_pi8(x, mask);
    long long z = (long long) y;
    unsigned char * c = (unsigned char *) &z;
    for (size_t i = 0; i < sizeof(z); i++)
    {
        printf("%02X %02X %02X\n", src[i], msk[i], c[i]);
    }
    printf("\n");
    return 0;
}