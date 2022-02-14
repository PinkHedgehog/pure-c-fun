#include <stdio.h>
#include <stdlib.h>
#include "nxjson.h"
#include "nfa.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <automaton.json>\n", argv[0]);
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    fseek(input, 0, SEEK_END);
    long inputSize = ftell(input);
    fseek(input, 0, SEEK_SET);
    char * code = (char *) calloc(inputSize + 1, sizeof(char));
    if (NULL == code)
    {
        fprintf(stderr, "Failed to allocate memory for buffer to read in\n");
        return 2;
    }
    fread(code, inputSize, sizeof(char), input);
    const nx_json * json = nx_json_parse(code, 0);
    if (json)
    {
        printf("json type: %d\n", json -> type);

        if (json -> type == NX_JSON_OBJECT)
        {
            nx_json * child = json -> children.first;
            for (int i = 0; i < json -> children.length; i++)
            {
                printf("child key: %s\n", child -> key);
                child = child->next;
            }
        }

        nx_json_free(json);
    }
    if (code)
    {
        free(code);
    }
    if (input)
        fclose(input);
    return 0;
}
