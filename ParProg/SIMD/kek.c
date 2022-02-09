#include <emmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <stdio.h>
#include <sys/types.h>
#include <tmmintrin.h>
#include <x86intrin.h>

int main()
{
    unsigned char src[8] = {0x57, 0x30, 0x33, 0x44, 0x17, 0x5c, 0x78, 0x23};
    unsigned char msk[8] = {0xF0, 0x00, 0x30, 0x70, 0x0B, 0x03, 0x01, 0xDF};
    __m64 x = _mm_set_pi8(src[7],src[6],src[5],src[4],src[3],src[2],src[1],src[0]);
    __m64 mask = _mm_set_pi8(msk[7],msk[6],msk[5],msk[4],msk[3],msk[2],msk[1],msk[0]);
    __m64 y =_mm_shuffle_pi8(x, mask);
    __m128i_u W = _mm_set_epi8(
        0xFF, 0xFA, 0xAF, 0xAA,
        0x0B, 0xB0, 0x00, 0x51,
        0x0B, 0xB3, 0x30, 0x04,
        0x0B, 0x77, 0x11, 0x01
    );
    __m128i_u A = _mm_set1_epi8(0
        // 0xFF, 0xFA, 0xAF, 0xAA,
        // 0x0B, 0xB0, 0x00, 0x51,
        // 0x0B, 0xB3, 0x30, 0x04,
        // 0x0B, 0x77, 0x11, 0x01
    );
    __m128i_u B = _mm_set1_epi8(2
        // 0xFF, 0xFA, 0xAF, 0xAA,
        // 0x0B, 0xB0, 0x00, 0x51,
        // 0x0B, 0xB3, 0x30, 0x04,
        // 0x0B, 0x77, 0x11, 0x01
    );
    __mmask16 x2 = 0;

    long long z = (long long) y;
    unsigned char * c = (unsigned char *) &z;
    for (size_t i = 0; i < sizeof(z); i++)
    {
        printf("%02X %02X %02X\n", src[i], msk[i], c[i]);
    }

    W = _mm_mask_add_epi8(W, 0xF0F0, A, B);
    unsigned char res[16];
    _mm_store_epi64(res, W);
    printf("\n=== KEK ===\n");
    for (size_t i = 0; i < 16; i++)
    {
        printf("%02X\n", res[i]);
    }
    
    printf("\n");
    return 0;
}
