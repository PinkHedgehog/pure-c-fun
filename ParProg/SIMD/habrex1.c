#include <emmintrin.h>
#include <stdio.h>
#include <sys/types.h>
#include <tmmintrin.h>
#include <x86intrin.h>
u_int64_t countScalar(u_int16_t * arr, size_t ARR_SIZE, u_int16_t v)
{
    u_int64_t cnt = 0;
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        if (arr[i] == v) cnt++;
    }
    return cnt;
}

u_int64_t countScalar2(u_int16_t * arr, size_t ARR_SIZE, u_int16_t v)
{
    int64_t cnt = 0;
    __m128i sseVal = _mm_set1_epi16(v);
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        __m128i sseArr = _mm_set_epi16(arr[i + 7], arr[i + 6], arr[i + 5], 
            arr[i + 4], arr[i + 3], arr[i + 2], arr[i + 1], arr[i]);
        cnt += _popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi16(sseVal, sseArr)));
        //_mm_shuffle_pi8()
    }
    return cnt / 2;
}

int main()
{
    ushort a[8] = {1, 5, 2, 4, 4, 1, 1, 3};
    u_int64_t x = countScalar(a, 8, 1);
    //u_int64_t y = countScalar2(a, 8, 1);
    printf("%lu %lu\n", x, x);
    return 0;
}
