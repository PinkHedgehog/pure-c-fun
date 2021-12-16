#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    List list = NULL;
    list = cons(24, list);
    list = cons(16, list);
    list = cons(8, list);
    list = cons(5, list);
    list = cons(1, list);
    printList(list, "LIST");
    //printf("=== LIST LENGTH %d ===\n", length(list));
    List list2 = NULL;
    list2 = cons(5, list2);
    list2 = cons(4, list2);
    list2 = cons(3, list2);
    list2 = cons(2, list2);
    printList(list2, "LIST2");
    List list3 = NULL;
    list3 = cons(8, list3);
    list3 = cons(4, list3);
    list3 = cons(2, list3);
    list3 = cons(1, list3);
    printList(list3, "LIST3");
    //list4 = NULL;
    //List arr[5] = {list, list2, NULL, list3, list4};
    List arr[3] = {list, list2, list3};
    List answ = mergelists(arr, 3);
    printList(answ, "MERGELISTS");
    deleteList(answ);
    return 0;
}
