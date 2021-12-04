#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct namednum
{
    char * name;
    int number;
};

void fixupstrings(struct namednum *arr, size_t arrlen);

void print(struct namednum * arr, size_t arrlen)
{
    for (size_t i = 0; i < arrlen; i++)
    {
        if (arr[i].name == NULL)
            printf("NULL %d\n", arr[i].number);
        else
            printf("%s %d\n", arr[i].name, arr[i].number);
    }
}

int main()
{
    char s1[] = "kek1";
    char s2[] = "kek2";
    char s3[] = "kek1kek2";
    struct namednum arr[8];


    for (int i = 0; i < 8; i++) { arr[i].name = NULL; arr[i].number = i;}
    arr[0].name = (char*) malloc(sizeof(char) * (strlen(s1)+1));
    strcpy(arr[0].name, s1);
    arr[1].name = arr[0].name;
    arr[2].name = (char*) malloc(sizeof(char) * (strlen(s2)+1));
    strcpy(arr[2].name, s2);
    arr[3].name = (char*) malloc(sizeof(char) * (strlen(arr[2].name)+1));
    strcpy(arr[3].name, arr[2].name);
    arr[4].name = NULL;
    arr[5].name = NULL;
    arr[6].name = (char*) malloc(sizeof(char) * (strlen(s3)+1));
    strcpy(arr[6].name, s3);
    arr[7].name = arr[6].name;

    print(arr, 8); 

    fixupstrings(arr, 8);

    print(arr, 8);

    for (size_t i = 0; i < 8; i++) free(arr[i].name);

    // free(arr[0].name);
    // free(arr[2].name);
    // free(arr[3].name);
    // free(arr[6].name);
    return 0;
}

void fixupstrings(struct namednum *arr, size_t arrlen)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; i < arrlen; i++)
    {
        if (arr[i].name == NULL)
        {
            continue;
        }
        for (size_t j = i+1; j < arrlen; j++)
        {
            if (arr[j].name == NULL)
            {
                continue;
            }
            if (arr[i].name == arr[j].name)
            {
                char * tmp = malloc(sizeof(char) * (strlen(arr[j].name)+1));
                arr[j].name = tmp;
                strcpy(arr[j].name, arr[i].name);
            }
        }
    }
}

