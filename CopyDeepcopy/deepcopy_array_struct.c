#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

enum { ARRLEN = 4 };
struct namednum
{
    char * name;
    int number;
};

void namednumcpy(struct namednum *dst, const struct namednum *src, int srclen)
{
    for (int i = 0; i < srclen; i++)
    {
        if (src[i].name == NULL)
            dst[i].name = NULL;
        else
        {
            dst[i].name = (char*) malloc(sizeof(char)*(strlen(src[i].name)+1));
            strcpy(dst[i].name, src[i].name);
        }
        dst[i].number = src[i].number;
    }
}

char *alstr(const char *orig) {
    int len;
    char *ret;
    assert(orig);
    len = strlen(orig);
    ret = calloc(len + 1, sizeof(char));
    strcpy(ret, orig);
    return ret;
}

void test() {
    int i;
    struct namednum arr[ARRLEN] = { 
      {alstr("abc"), 1}, {alstr("def"), 2}, 
      {alstr("ghi"), 3}, {alstr("klm"), 4} 
    };
    struct namednum answ[ARRLEN];
    
    // вызов namednumcpy
    namednumcpy(answ, arr, ARRLEN);
    
    for (i = 0; i < ARRLEN; ++i)
      arr[i].name[0] = '\0';

    assert(0 == strcmp(answ[0].name, "abc"));
    assert(0 == strcmp(answ[1].name, "def"));
    assert(0 == strcmp(answ[2].name, "ghi"));
    assert(0 == strcmp(answ[3].name, "klm"));

    for (i = 0; i < ARRLEN; ++i) {
      free(arr[i].name);
      free(answ[i].name);
    }
}
int main()
{
    test();
    return 0;
}
