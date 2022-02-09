#include <stdio.h>
#include <stdlib.h>

struct Pair
{
    int state;
    char nuc;
};

struct Step
{
    struct Pair source;
    struct Pair dest;
};

int main()
{
    int n;
    scanf("%d", &n);
    int srcState, destState;
    char srcNuc, destNuc;
    struct Step * step = (struct Step *) malloc(sizeof(struct Step) * 4 * n);
    for (int i = 0; i < 4*n; i++)
    {
        scanf("%d %c %d %c", &srcState, &srcNuc, &destState, &destNuc);
        struct Step s = {{srcState, srcNuc}, {destState, destNuc}};
        step[i] =  s;
    }
    int curState = 1;
    char c;
    for(; scanf("%c", &c) > 0;)
    {
        for (int j = 4 * (curState - 1); j < 4 * curState; j++)
        {
            if ((step[j].source.state == curState) && (step[j].dest.nuc == c))
            {
                
                //printf("%c", step[j].dest.nuc);
                //printf("%d %c | %d %c %d %c\n", curState, c, step[j].source.state, step[j].source.nuc, step[j].dest.state, step[j].dest.nuc);
                curState = step[j].dest.state;
                printf("%c", step[j].source.nuc);
                break;
            }
        }
    }
    free(step);
    printf("\n");
    return 0;
}
