#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#   -- start of the string
$   -- end of the string
@   -- concatenation
*   -- iteration
|   -- alternative
a-z -- chars
()  -- brackets
-   -- error
*/

//insert '@' 5 $! insert '|' 4 $! insert '(' 0 $! empty


struct Queue
{
    //int first;
    int last;
    int count;
    int * elements;
};

struct Stack
{
    int top;
    char * elements;
    int size;
};

void push(struct Stack * s, char c)
{
    if (s -> size == 0)
    {
        s -> size = 64;
        s -> elements = calloc(s -> size, sizeof(char));
    }
    else
    {
        if ((s -> size) <= (s -> top))
        {
            s -> size *= 2;
            char * newMemory = calloc(s -> size, sizeof(char));
            memmove(newMemory, s -> elements, sizeof(char) * (s -> top));
            char * tmp = s -> elements;
            s -> elements = newMemory;
            free(tmp);
        }
    }
    s -> elements[s -> top++] = c;
}

char pop(struct Stack * s)
{
    if ((s -> size == 0) || (s -> top <= 0))
    {
        return '-';
    } 
    else
    {
        s -> top--;
        return s -> elements[s -> top];
    }
}


int getPriority(char c)
{
    int result = 0;
    switch (c) 
    {
        case '@':
            result = 5;
            break;
        case '|':
            result = 4;
            break;
        case '(':
            result = 0;
            break;
    }
    return result;
}

char * rpn(const char * input)
{
    char lastUsed = '#';
    for 
}