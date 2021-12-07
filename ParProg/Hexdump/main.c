#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexdump(char *restrict out, unsigned char *restrict in, size_t n);

char out[16777216];
unsigned char in[4194304];

int main()
{
    //unsigned char in[] = "jlajg aghgjahgha jgajgh ajghahnbaa \x11 \xaa jfjfa \xff \xfa \xcd \xa0 \xb3 fafahf a faf apiq,.q,z[qm?`~";
    //size_t n = strlen((char *)in);
    FILE * steam = fopen("steam_latest.deb", "rb");
    size_t n_read = fread(in, sizeof(unsigned char), 3401766, steam);
    hexdump(out, in, n_read);
    //    hexdump(out, in, n);
        //for (size_t i = 0; i < 4*n; i++)
        //{
        //    printf("%c", out[i]);
        //}
    //}
    fclose(steam);
    out[4*n_read-1] = 0;
    printf("%s\n", out);
    return 0;
}
