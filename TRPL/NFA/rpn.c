#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define isOperator(c) (((c) == '*') || ((c) == '|') || ((c) == '@'))
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
    int first;
    int last;
    char * elements;
    int size;
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
        s -> elements = (char *) calloc(s -> size, sizeof(char));
    }
    else
    {
        if ((s -> size) <= (s -> top))
        {
            s -> size *= 173;
            s -> size /= 100;
            s -> size++;
            char * newMemory = (char *) calloc(s -> size, sizeof(char));
            memmove(newMemory, s -> elements, sizeof(char) * (s -> top));
            char * tmp = s -> elements;
            s -> elements = newMemory;
            free(tmp);
        }
    }
    s -> elements[s -> top++] = c;
}

//

char pop(struct Stack * s)
{
    if ((s -> size <= 0) || (s -> top <= 0))
    {
        return '-';
    } 
    else
    {
        s -> top--;
        return s -> elements[s -> top];
    }
}

char peek(struct Stack s)
{
    if ((s.top > 0) && (s.size > 0))
        return s.elements[s.top-1];
    else
        return '-';
}

void initQueue(struct Queue * q)
{
    q -> size = 0;
    q -> last = 0;
    q -> first = -1;
    q -> elements = NULL;
}

void initStack(struct Stack * s)
{
    s -> size = 0;
    s -> top = 0;
    s -> elements = NULL;
}

int deleteQueue(struct Queue * q)
{
    if (q && q -> elements)
    {
        free(q -> elements);
        return 1;
    }
    else
        return 0;
    
}

int deleteStack(struct Stack * q)
{
        if (q && q -> elements)
        {
            free(q -> elements);
            return 1;
        }
        else
            return 0;
}

void enqueue(struct Queue * q, char c)
{
    if (q -> size <= 0)
    {
        q -> size = 64;
        q -> elements = (char *) calloc(q -> size, sizeof(char));
    }
    else
    {
        if (q -> last >= q -> size)
        {
            q -> size *= 5 / 4 + 1;
            q -> elements = (char *) realloc(q -> elements, q -> size);
        }
    }
    q -> elements[q -> last++] = c;

}

int getPriority(char c)
{
    int result = 0;
    switch (c) 
    {
        case '*':
            result = 6;
            break;
        case '@':
            result = 5;
            break;
        case '|':
            result = 4;
            break;
        default:
            break;
    }
    return result;
}

char * insertConcatSign(const char * input)
{
    char lastUsed;
    int n = strlen(input);
    char * result = (char *) calloc(2 * n + 1, sizeof(char));
    int top = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            result[top++] = input[i];
            lastUsed = input[i];
            continue;
        }
        if (isspace(input[i]))
        {
            continue;
        }
        if ((isalnum(input[i]) || (input[i] == '(')) && (isalnum(lastUsed) || (lastUsed == ')') || (lastUsed == '*')))
        {
            result[top++] = '@';
            result[top++] = input[i];
            lastUsed = input[i];
            continue;
        }
        result[top++] = input[i];
        lastUsed = input[i];
    }
    result[top++] = 0;
    return result;
}

char * rpn(const char * input_0)
{
    //char lastUsed = '#';
    struct Queue q;
    initQueue(&q);
    struct Stack s;
    initStack(&s);
    char * input = insertConcatSign(input_0);
    int inputLength = strlen(input);
    //printf("=== INPUT %s %d ===\n", input, inputLength);
    for (int i = 0; i < inputLength; i++)
    {
        if (isalnum(input[i]) || (input[i] == '*'))
        {
            enqueue(&q, input[i]);
            continue;
        }
        if (isOperator(input[i]))
        {
            

            //printf("\n=== outer operator %c ===\n", input[i]);
            char o1 = input[i];
            for (;isOperator(peek(s));)
            {
                if (getPriority(peek(s)) >= getPriority(o1))
                {
                    enqueue(&q, pop(&s));
                }
                else break;
            }        
            push(&s, input[i]);
            //printf("\n=== stack at the end of operator branch %c ===\n", peek(s));
            continue;
        }
        if (input[i] == '(')
        {
            //printf("\n=== stack at ( branch %c ===\n", peek(s));
            push(&s, '(');
            continue;
        }
        if (input[i] == ')')
        {
            for(;(peek(s) != '-') && (peek(s) != '(');)
            {
                enqueue(&q, pop(&s));
            }
            //printf("\n=== stack at ) branch %c ===\n", peek(s));
            if (peek(s) == '(')
            {
                pop(&s);
                // char t = pop(&s);
                // if (t == '-')
                // {
                //     printf("\n*** something went wrong :( ***\n");
                // }
            }
            continue;
        }
    }
    for (char c = pop(&s); c != '-'; c = pop(&s))
    {
        enqueue(&q, c);
    }
    char * output = (char *) calloc(q.last + 2, sizeof(char));
    memmove(output, q.elements, q.last);
    output[q.last + 1] = 0;
    deleteQueue(&q);
    deleteStack(&s);
    free(input);
    return output;

}
