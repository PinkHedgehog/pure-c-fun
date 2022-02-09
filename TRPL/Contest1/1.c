#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack
{
    int * values;
    int top;
    int size;
};

struct Stack stack = { NULL, 0, 0 };

void push(struct Stack * s, int x)
{
    if (s -> size == 0)
    {
        s -> size = 1;
        s -> values = (int *) malloc(sizeof(int) * 1024);
        s -> values[s -> top++] = x;
        return;
    }
    if (s -> top >= s -> size)
    {
        
        int * newValues = (int*) malloc(2 * sizeof(int) * (s -> size));
        memmove(newValues, s -> values, sizeof(int) * (s -> size));
        s -> size *= 2;
        int * oldValues = s -> values;
        s -> values = newValues;
        free(oldValues);
        s -> values[s -> top++] = x;
        return;
    }
    s -> values[s -> top++] = x;
}

int pop(struct Stack * s)
{
    if (s -> size <= 0)
    {
        free(s -> values);
        exit(1);
    }
    if (s -> top < 0)
    {
        free(s -> values);
        exit(1);
    }
    return s -> values[--(s -> top)];
}

void printStack(struct Stack s)
{
    printf("=== Size: %d | ", s.size);
    for (int i = 0; i < s.top; i++)
    {
        printf("%d ", s.values[i]);
    }
    printf("\n\n");
}

int main()
{
    int x, y;
    char * input = NULL;
    char c;
    for (; scanf("%m[0-9+*/-]s", &input) > 0;)
    {
        if (sscanf(input, "%d", &x) > 0)
        {
            push(&stack, x);
        }
        else
        {
            if (sscanf(input, "%c", &c) > 0)
            {
                x = pop(&stack);
                y = pop(&stack);
                switch(c)
                {
                    case '*':
                        push(&stack, y * x);
                        break;
                    case '+':
                        push(&stack, y + x);
                        break;
                    case '-':
                        push(&stack, y - x);
                        break;
                    case '/':
                        push(&stack, y / x);
                        break;
                    default:
                        break;
                }
            }
        }
        free(input);
        scanf("%m[^0-9+*/-]s", &input);
        free(input);
    }
    //printf("\n*** %d ***\n", stack.values[stack.top-1]);
    printf("%d\n", stack.values[stack.top-1]);
    free(stack.values);
    return 0;
}
