#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Step
{
    int next[26];
};



struct Step steps[60];
char alphabet[26];
//int terminalStates[64];

int nextState(struct Step * sts, int cur, char c)
{
    return sts[cur].next[(int)(c - 'a')];
}

int main()
{
    int A, N, M, T, K;
    scanf("%d %d %d", &A, &N, &M);
    int x;
    int * terminals = (int*) calloc(N, sizeof(int));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= A; j++)
        {
            steps[i].next[j] = -1;
        }
    }
    int src, dest;
    char c;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %c", &src, &dest, &c);
        steps[src].next[(int)(c - 'a')] = dest;
    }

    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &x);
        terminals[x] = 1;
    }

    scanf("%d", &K);
    char * input = NULL;
    for (int i = 0; i < K; i++)
    {
        int scanfRes = scanf("%ms", &input);
        int curState = 0;
        if ((T == 0) || (M == 0) || (N == 0) || (input == NULL))
        {
            printf("0 ");
            continue;
        }
        if (scanfRes <= 0)
        {
            printf("%d ", terminals[curState]);
            continue;
        }
        int len = strlen(input);
        int j = 0;
        for (; j < len; j++)
        {
            c = input[j];
            int step = nextState(steps, curState, c);
            if ((step < 0) || ((int)(c - 'a') > A))
            {
                break;
            }
            curState = step;
        }
        if ((j == len) && (terminals[curState]))
            printf("1 ");
        else
            printf("0 ");
        free(input);

    }
    printf("\n");
    free(terminals);
    return 0;
}