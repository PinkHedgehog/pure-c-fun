#include <x86intrin.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n)
{
    __m128i_u char_char = _mm_set_epi8(
        102, 101, 100, 99,
        98, 97, 57, 56,
        55, 54, 53, 52,
        51, 50, 49, 48
    );
    __m128i_u fixed = _mm_set_epi8(
        0, 0, 0x78, 0x5c,
        0, 0, 0x78, 0x5c,
        0, 0, 0x78, 0x5c,
        0, 0, 0x78, 0x5c
    );
    __m128i_u lt10 = _mm_set1_epi8(48);
    __m128i_u gt10 = _mm_set1_epi8(87);

    size_t i = 0;
    for (; i + 4 < n; i += 4)
    {
        __m128i_u src1 = _mm_set_epi8(
            in[i + 3] & 0x0F, (in[i + 3] >> 4), 0xFF, 0xFF, 
            in[i + 2] & 0x0F, (in[i + 2] >> 4), 0xFF, 0xFF,
            in[i + 1] & 0x0F, (in[i + 1] >> 4), 0xFF, 0xFF,
            in[i + 0] & 0x0F, (in[i + 0] >> 4), 0xFF, 0xFF
        );
        __m128i out_reg = _mm_set1_epi8(0);
        __m128i_u flags1 = _mm_and_si128(
            _mm_cmpgt_epi8(src1, _mm_set1_epi8(47)),
            _mm_cmplt_epi8(src1, _mm_set1_epi8(58))
         );
         __m128i_u flags2 = _mm_and_si128(
            _mm_cmpgt_epi8(src1, _mm_set1_epi8(96)),
            _mm_cmplt_epi8(src1, _mm_set1_epi8(103))
         );
        __m128i_u lt10_ = _mm_and_si128(lt10, flags1);
        __m128i_u gt10_ = _mm_and_si128(gt10, flags2);
        src1 = _mm_sub_epi8(src1, lt10_);
        src1 = _mm_sub_epi8(src1, gt10_);
        out_reg = _mm_add_epi8(fixed, _mm_shuffle_epi8(char_char, src1));
        _mm_storeu_si128((__m128i_u *) out, out_reg);
        out += 16;

    }
}
// 30 48 0
// 31 49 1
// 32 50 2
// 33 51 3
// 34 52 4
// 35 53 5
// 36 54 6
// 37 55 7
// 38 56 8
// 39 57 9
// 41 65 A
// 42 66 B
// 43 67 C
// 44 68 D
// 45 69 E
// 46 70 F
// 61 97 a
// 62 98 b
// 63 99 c
// 64 100 d
// 65 101 e
// 66 102 f
// 5c 92 \
// 78 120 x
//
