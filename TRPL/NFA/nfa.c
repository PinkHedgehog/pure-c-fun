#include <stdio.h>
#include <stdlib.h>
#include "rpn.c"



// struct AutomatonChar
// {
//     int id;
//     char c;
//     int qStart;
//     int qEnd;
// };

// struct AutomatonAlter
// {
//     int id;
//     // char left;
//     // char right;
//     int qStart;
//     int qEnd;
    
// };

// struct AutomatonConcat
// {
//     int id;
//     int qStart;

//     int qEnd;
// };

// struct AutomatonIter
// {
//     int id;
//     int qStart;
    
//     int qEnd;
// };

struct SingleStep
{
    int src;
    char c;
    int dest;
};

typedef struct SingleStep Step;

Step step(int src, char c, int dest)
{
    Step s;
    s.src = src;
    s.c = c;
    s.dest = dest;
    return s;
}



struct Transitions
{
    Step * tSteps;
    int last;
    int size;
};

struct Transitions * addStep(struct Transitions * trans, Step step)
{
    if (trans -> size == 0)
    {
        trans -> size = 1;
        trans -> tSteps = (Step *) realloc(trans -> tSteps, (trans -> size) * sizeof(Step));
    }
    if (trans -> last >= trans -> size)
    {
        trans -> size *= 2;
        trans -> tSteps = (Step *) realloc(trans -> tSteps, (trans -> size) * sizeof(Step));
    }
    trans -> tSteps[trans -> last++] = step;
    return trans;
}

struct Automaton
{
    int id;
    char type[8];
    int qStart;
    int qEnd;
    union
    {
        struct 
        {
            int qLeftStart;
            int qLeftEnd;
            int qRightStart;
            int qRightEnd;
        } AutomatonAlter;
        struct 
        {
            int qInnerEnd;
            int qInnerStart;
        } AutomatonIter;
        struct
        {
            char c;
        } AutomatonChar;
        struct
        {
            int qLeftEnd;
            int qRightStart;
        } AutomatonConcat;
    };
};

typedef struct Automaton * Automata;



struct Automaton charToAutomaton(char c, int * lastId, int * lastState)
{
    struct Automaton a;
    (*lastId)++;
    a.id = *lastId;
    a.AutomatonChar.c = c;
    a.qStart = *lastState + 1;
    a.qEnd = *lastState + 2;
    strcpy(a.type, "Char");
    (*lastState) += 2;

    //struct Transitions * tChar = (struct Transitions *) calloc(1, sizeof(struct Transitions));
    // tChar -> length = 1;
    // tChar -> t = (struct SingleStep *) calloc(1, sizeof(struct SingleStep));
    // tChar -> t[0].c = c;
    // tChar -> t[0].src = *lastState - 2;
    // tChar -> t[0].dst =;
    return a;
}



struct Automaton alterAutomaton(struct Automaton a1, struct Automaton a2, int * lastId, int * lastState)
{
    struct Automaton a;
    (*lastId)++;
    a.id = *lastId;
    a.qStart = *lastState + 1;
    a.qEnd = *lastState + 2;
    (*lastState) += 2;
    a.AutomatonAlter.qLeftStart = a1.qStart;
    a.AutomatonAlter.qLeftEnd = a1.qEnd;
    a.AutomatonAlter.qRightStart = a2.qStart;
    a.AutomatonAlter.qRightEnd = a2.qEnd;
    strcpy(a.type, "Alter");
    return a;
}

struct Automaton concatAutomaton(struct Automaton a1, struct Automaton a2, int * lastId)
{
    struct Automaton a;
    (*lastId)++;
    a.id = *lastId;
    a.qStart = a1.qStart;
    a.qEnd = a2.qEnd;
    //(*lastState) += 2;
    a.AutomatonConcat.qLeftEnd = a1.qEnd;
    a.AutomatonConcat.qRightStart = a2.qStart;
    strcpy(a.type, "Concat");
    return a;
}

struct Automaton iterAutomaton(struct Automaton a1, int * lastId, int * lastState)
{
    struct Automaton a;
    (*lastId)++;
    a.id = *lastId;
    a.qStart = (*lastState) + 1;
    a.qEnd = (*lastState) + 2;
    a.AutomatonIter.qInnerStart = a1.qStart;
    a.AutomatonIter.qInnerEnd = a1.qEnd;
    (*lastState) += 2;
    strcpy(a.type, "Iter");
    return a;
}

struct AutomataCount
{
    Automata automata;
    char alphabet[32];
    int count;
    int states;
    struct Transitions trans;
    int qInit;
    int qFinal;
};

struct AutomataCount automatonFromRPN(char * rpn)
{
    int n = strlen(rpn);
    Automata automata = (Automata) calloc(n + 1, sizeof(struct Automaton));
    char alphabet[32];
    for (int i = 0; i < 32; i++)
        alphabet[i] = 0;
    int * automataStack = (int *) calloc(n + 1, sizeof(int));
    int lastId = -1;
    int lastState = -1;
    int stackTop = 0;
    struct AutomataCount ac;
    ac.trans.size = 0;
    ac.trans.last = 0;
    ac.trans.tSteps = NULL;
    ac.qInit = 0;

    for (int i = 0; i < n; i++)
    {
        struct Automaton a;
        if (isalnum(rpn[i]))
        {
            a = charToAutomaton(rpn[i], &lastId, &lastState);
            if ((rpn[i] >= 'a') && (rpn[i] <= 'z'))
            {
                alphabet[rpn[i] - 'a'] = 1;
            }
            if (rpn[i] == 'E')
                alphabet[30] = 1;
            printf("\n=== char: %c, lastId: %d, lastState: %d ===\n", rpn[i], lastId, lastState);
            addStep(&ac.trans, step(a.qStart, rpn[i], a.qEnd));
            
        }
        if (rpn[i] == '@')
        {
            struct Automaton a2 = automata[automataStack[--stackTop]];
            struct Automaton a1 = automata[automataStack[--stackTop]];
            a = concatAutomaton(a1, a2, &lastId);

            addStep(&ac.trans, step(a.AutomatonConcat.qLeftEnd, 'E', a.AutomatonConcat.qRightStart));

            printf("\n=== concat, lastId: %d, lastState: %d ===\n", lastId, lastState);
        }
        if (rpn[i] == '|')
        {
            struct Automaton a2 = automata[automataStack[--stackTop]];
            struct Automaton a1 = automata[automataStack[--stackTop]];
            a = alterAutomaton(a1, a2, &lastId, &lastState);

            addStep(&ac.trans, step(a.qStart, 'E', a.AutomatonAlter.qLeftStart));
            addStep(&ac.trans, step(a.qStart, 'E', a.AutomatonAlter.qRightStart));
            addStep(&ac.trans, step(a.AutomatonAlter.qRightEnd, 'E', a.qEnd));
            addStep(&ac.trans, step(a.AutomatonAlter.qLeftEnd, 'E', a.qEnd));


            
            printf("\n=== alter, lastId: %d, lastState: %d ===\n", lastId, lastState);
        }
        if (rpn[i] == '*')
        {
            struct Automaton a1 = automata[automataStack[--stackTop]];
            a = iterAutomaton(a1, &lastId, &lastState);

            addStep(&ac.trans, step(a.AutomatonIter.qInnerEnd, 'E', a.AutomatonIter.qInnerStart));
            addStep(&ac.trans, step(a.qStart, 'E', a.qEnd));

            printf("\n=== iter, lastId: %d, lastState: %d ===\n", lastId, lastState);
        }
        
        automata[lastId] = a;
        automataStack[stackTop++] = lastId;
    }
    
    ac.count = lastId + 1;
    ac.states = lastState + 1;
    ac.automata = automata;

    int j = 0;
    for (int i = 0; i <= 25; i++)
    {
        if (alphabet[i] == 1)
            ac.alphabet[j++] = 'a' + i;
    }
    if (alphabet[30] == 1)
        ac.alphabet[j++] = 'E';
    ac.alphabet[j] = 0;
    ac.qFinal = automata[lastId].qEnd;
    free(automataStack);
    return ac;
}




char * saveAsJson(struct AutomataCount ac)
{
    printf("{\n");
    //
    printf("    \"states\":[\n");
    for (int i = 0; i < ac.states; i++)
    {
        printf("        \"Q%d\"\n", i);
    }
    printf("    ],\n");
    //
    printf("    \"letters\":[\n");
    int n = strlen(ac.alphabet);
    for (int i = 0; i < n; i++)
    {
        printf("        \"%c\"\n", ac.alphabet[i]);
    }
    printf("        \"E\"\n");
    printf("    ],\n");
    //
    printf("    \"transition_function\":[\n");
    for (int i = 0; i < ac.trans.last; i++)
    {
        printf("        [\n");
        printf("            \"Q%d\",\n", ac.trans.tSteps[i].src);
        printf("            \"%c\",\n", ac.trans.tSteps[i].c);
        printf("            \"Q%d\",\n", ac.trans.tSteps[i].dest);
        printf("        ]\n");
    }
    printf("    ],\n");
    //printf("\n=== trans len %d ===\n", ac.trans.last);
    printf("    \"start_states\":[\n");
    printf("        \"Q%d\"\n", ac.qInit);
    printf("    ],\n");
    //
    printf("    \"final_states\":[\n");
    printf("        \"Q%d\"\n", ac.qFinal);
    printf("    ]\n");
    printf("}\n");
    return NULL;
}


int main(int argc, char * argv[])
{
    char * s;
    scanf("%ms", &s);
    char * t = rpn(s);
    printf("%s\n", t);

    struct AutomataCount ac = automatonFromRPN(t);

    saveAsJson(ac);

    free(ac.automata);
    free(ac.trans.tSteps);
    free(s);
    free(t);
    // if (argc != 2)
    // {
    //     fprintf(stderr, "Usage: %s <automaton.json>\n", argv[0]);
    //     return 1;
    // }
    // FILE * input = fopen(argv[1], "r");
    // fseek(input, 0, SEEK_END);
    // long inputSize = ftell(input);
    // fseek(input, 0, SEEK_SET);
    // char * code = (char *) calloc(inputSize + 1, sizeof(char));
    // if (NULL == code)
    // {
    //     fprintf(stderr, "Failed to allocate memory for buffer to read in\n");
    //     return 2;
    // }
    // fread(code, inputSize, sizeof(char), input);
    // const nx_json * json = nx_json_parse(code, 0);
    // if (json)
    // {
    //     printf("json type: %d\n", json -> type);

    //     if (json -> type == NX_JSON_OBJECT)
    //     {
    //         nx_json * child = json -> children.first;
    //         for (int i = 0; i < json -> children.length; i++)
    //         {
    //             printf("child key: %s\n", child -> key);
    //             child = child->next;
    //         }
    //     }

    //     nx_json_free(json);
    // }
    // if (code)
    // {
    //     free(code);
    // }
    // if (input)
    //     fclose(input);
    return 0;
}
