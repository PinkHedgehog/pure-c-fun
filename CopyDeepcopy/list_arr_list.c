#include <stdlib.h>
#include <stdio.h>

struct node
{
    struct node *next;
    int n;
};

struct node * mergelists(struct node **arr, int arrlen)
{
    typedef struct node * List;
    List merged = NULL;
    List result = merged;
    for (int i = 0; i < arrlen; i++)
    {
        
        if (NULL == arr[i])
            continue;
        List list1 = merged;
        List list2 = arr[i];
        if (NULL == list1)
        {
            merged = list2;
            continue;
        }
        if (list1 -> n <= list2 -> n)
        {
            merged = list1;
            list1 = list1 -> next;
        }
        else
        {
            merged = list2;
            list2 = list2 -> next;
        }
        List iter = merged;

        for (;1;)
        {
            if (NULL == list1)
            {
                iter -> next = list2;
                break;
            }
            if (NULL == list2)
            {
                iter -> next = list1;
                break;
            }
            if (list1 -> n <= list2 -> n)
            {
                iter -> next = list1;
                list1 = list1 -> next;
                
            }
            else
            {
                iter -> next = list2;
                list2 = list2 -> next;
            }
            iter = iter -> next;
        }
        result = merged;

    }
    return result;
}
