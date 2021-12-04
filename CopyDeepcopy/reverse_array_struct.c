#include <stdlib.h>
#include <stdio.h>

struct Test { int x; double y; };
enum { ARRLEN = 4 };


void reverse(void *arr, int size, int n)
{
    for (int i = 0; i < n/2; i++)
    {
        int last = n - 1 - i;
        for (int j = 0; j < size; j++)
        {
            ((char*) arr)[i*size + j] ^= ((char*) arr)[last*size + j];
            ((char*) arr)[last*size + j] ^= ((char*) arr)[i*size + j];
            ((char*) arr)[i*size + j] ^= ((char*) arr)[last*size + j];
        }
    }
}

void test() {
  int i;
  struct Test arr[ARRLEN] = {{1, 1.0}, {2, 2.0}, {3, 3.0}, {4, 4.0}};
  struct Test answ[ARRLEN] = {{4, 4.0}, {3, 3.0}, {2, 2.0}, {1, 1.0}};
  reverse(arr, sizeof(struct Test), ARRLEN);
  for (i = 0; i < ARRLEN; ++i) {
    if (arr[i].x != answ[i].x)
      abort();
    if (arr[i].y != answ[i].y)
      abort();
  }
}

int main()
{
    test();
    return 0;
}
