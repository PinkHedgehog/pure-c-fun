#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char transitionsE[64][64];


int transitions[64][32][64];

int terminals[64];

int A, N, M, T, K;

int epsTransitions;

struct States
{
    //int * states;
    int states[64];
    int count;
};

struct States epsclosure(struct States s);

int equal(struct States s1, struct States s2)
{
    if (s1.count != s2.count)
        return 0;
    for (int i = 0; i < s1.count; i++)
    {
        if (s1.states[i] != s2.states[i])
        {
            return 0;
        }
    }
    return 1;
}

struct States availableStatesE(struct States statesList)
{
    struct States available;
    available.count = 0;
    int * candidates = (int*) calloc(N, sizeof(int));
    for (int i = 0; i < statesList.count; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (transitions[statesList.states[i]][26][j])
            {
                candidates[j] = 1;
                //available.states[available.count++] = j;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (candidates[i])
        {
            available.states[available.count++] = i;
        }
    }
    free(candidates);
    return available;
}

void showStates(struct States s)
{
    printf("=== { ");
    for (int i = 0; i < s.count - 1; i++)
    {
        printf("%d, ", s.states[i]);
    }
    if (s.count > 0)
        printf("%d ", s.states[s.count-1]);
    printf("} ===\n");
}

struct States concatStates(struct States s1, struct States s2)
{
    struct States s3;
    s3.count = 0;
    int * candidates = (int*) calloc(N, sizeof(int));
    if (NULL == candidates)
    {
        return s3;
    }
    for (int i = 0; i < s1.count; i++)
    {
        candidates[s1.states[i]] = 1;
    }
    for (int i = 0; i < s2.count; i++)
    {
        candidates[s2.states[i]] = 1;
    }
    for (int i = 0; i < N; i++)
    {
        if (candidates[i])
        {
            s3.states[s3.count++] = i;
        }
    }
    free(candidates);
    return s3;
    
}

struct States availableStates(struct States statesList, char c)
{
    struct States available;
    available.count = 0;
    int * candidates = (int*) calloc(N, sizeof(int));
    statesList = epsclosure(statesList);
    for (int i = 0; i < statesList.count; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //|| (transitions[statesList.states[i]][26][j])
            if ((transitions[statesList.states[i]][(int)(c - 'a')][j]))// || (transitions[statesList.states[i]][26][j]))
            {
                candidates[j] = 1;
                //available.states[available.count++] = j;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (candidates[i])
        {
            available.states[available.count++] = i;
        }
    }
    free(candidates);
    return available;
}

struct States epsclosure(struct States s)
{
    //struct States closure = concatStates(s, availableStatesE(s));
    
    for (int i = 0; i < epsTransitions; i++)
    {
        s = concatStates(s, availableStatesE(s));

    }
    return s;
}

int checkStates(struct States statesList)
{
    for (int i = 0; i < statesList.count; i++)
    {
        if (terminals[statesList.states[i]])
            return 1;
    }
    return 0;
}

void showTransitions()
{
    printf("source\tdest\tchar\n");
    for (int i = 0; i < N; i++)
    {
        for (int c = 0; c <= A; c++)
        {
            for (int j = 0; j < N; j++)
            {
                if (transitions[i][c][j])
                    printf("%d\t%d\t%c\n", i, j, 'a' + c);
            }
        }
        for (int j = 0; j < N; j++)
        {
            if (transitions[i][26][j])
                printf("%d\t%d\t%c\n", i, j, 'E');
        }
    }
}


int main()
{
    A = N = M = T = K = epsTransitions = 0;
    scanf("%d %d %d", &A, &N, &M);
    int x;
    

    //init transitions matrix with default value 'N' -- no transition

    for (int i = 0; i <= N + 1; i++)
    {
        for (int j = 0; j <= A + 2; j++)
        {
            for (int h = 0; h <= N + 1; h++)
            {
                transitions[i][j][h] = 0;
            }
        }
    }

    //enter transitions matrix
    int src, dest;
    char c;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %c", &src, &dest, &c);
        //if ((c <= 'a' + A) && (c >= 'a'))
            
        if (c == 'E')
        {
            transitions[src][26][dest] = 1;
            epsTransitions++;
        }
        else
            transitions[src][(int)(c - 'a')][dest] = 1;;
    }

    //init and enter terminal states
    scanf("%d", &T);
    for (int i = 0; i < N; i++)
    {
        terminals[i] = 0;
    }
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &x);
        terminals[x] = 1;
    }


    //check strings
    scanf("%d", &K);
    char * input = NULL;
    for (int i = 0; i < K; i++)
    {
        int scanfRes = scanf("%ms", &input);
        
        if ((T == 0) || (M == 0) || (N == 0) || (input == NULL))
        {
            printf("0 ");
            continue;
        }
        struct States curState = {{0}, 1};
        curState = epsclosure(curState);
        if ((scanfRes <= 0) || (*input == 0))
        {
            curState = epsclosure(curState);
            
            printf("%d ", checkStates(curState));
            free(input);
            continue;
        }
        // printf("\n*** initial eps-closure ***\n");
        // showStates(curState);
        int len = strlen(input);
        int j = 0;
        for (; j < len; j++)
        {
            c = input[j];
            curState = epsclosure(curState);
            curState = availableStates(curState, c);
            curState = epsclosure(curState);
            // printf("\n*** available states on char %c ***\n", c);
            // showStates(curState);
            //curState = epsclosure(curState);
            if ((curState.count == 0) || ((int)(c - 'a') > A))
            {
                break;
            }
            
            //curState = step;
        }
        curState = epsclosure(curState);
        if ((j == len) && (checkStates(curState)))
            printf("1 ");
        else
            printf("0 ");
        free(input);

    }
    
    printf("\n");
    // showTransitions();
    return 0;
}
