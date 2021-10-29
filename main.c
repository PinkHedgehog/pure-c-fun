#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
 *********************************************
 *                                           *
 *  *       *        *        ***    *    *  *
 *  * *   * *       * *        *     **   *  *
 *  *  * *  *      *   *       *     * *  *  *
 *  *   *   *     *******      *     *  * *  *
 *  *       *    *       *     *     *   **  *
 *  *       *   *         *   ***    *    *  *
 *                                           *
 *********************************************
*/
int inc(int x);
int dec(int x);
int dbl(int x);


int main()
{
    /***************************************************************/

    struct Node * list = NULL;
    list = cons(7, list);
    list = cons(5, list);
    list = cons(3, list);
    list = cons(2, list);
    printList(list, "LIST");

    /***************************************************************/

    struct Node * list2 = copy(list);
    printList(list2, "COPY");

    /***************************************************************/

    struct Node * list3 = reverse(list);
    printList(list3, "REVERSE");

    /***************************************************************/

    /* list1 \--> list4 */
    struct Node * list4 = reverseI(list);
    printList(list4, "IN-PLACE");
    /* cannot be used anymore */

    /***************************************************************/

    struct Node * h4 = head(list4); /* to be freed */
    struct Node * h3 = headI(list3); /* will be freed by list3 */
    struct Node * kek1 = indexList(3, list3); 
    struct Node * kek2 = indexListI(2, list2);
    struct Node * list6 = NULL;
    list6 = cons(h4 -> value, list6);
    list6 = cons(h3 -> value, list6);
    list6 = cons(kek1 -> value, list6);
    list6 = cons(kek2 -> value, list6);
    printList(list6, "ELEMENTS FROM OTHER LISTS");

    /***************************************************************/

    struct Node * list5 = reverseI(copy(tailI(list2)));
    printList(list5, "REVERSE OF TAIL OF LIST2");

    /***************************************************************/

    struct Node * t1 = tailI(list2);
    struct Node * h1 = headI(list2);
    struct Node * r1 = reverseIP(t1, h1);
    struct Node * t2 = tailI(r1);
    struct Node * h2 = headI(r1);
    struct Node * r2 = reverseIP(t2, h2);
    struct Node * kek3 = r2;
    kek3 = reverseI(cons(9, reverseI(copy(kek3))));
    printList(kek3, "KEK3");

    /***************************************************************/

    struct Node * merged = merge(kek3, reverseI(list5));
    printList(merged, "MERGED");
    printList(list2, "AFTER KEK3");

    /***************************************************************/

    printf("\nKEK3 LENGTH: %d\n", length(kek3));

    /***************************************************************/

    list = NULL;
    list = cons(1, list);
    list = cons(5, list);
    list = cons(2, list);
    list = cons(4, list);
    list = cons(3, list);
    printList(list, "NEW LIST");
    
    /***************************************************************/

    deleteList(list2);
    list2 = take(2, list);
    printList(list2, "TAKE 2 FROM LIST");

    /***************************************************************/

    struct Node * sortedList = sortI(copy(list));
    printList(sortedList, "SORTED LIST");

    /***************************************************************/

    struct Node * incList = mapIntI(list, inc);
    struct Node * decList = mapInt(incList, dec);
    printList(incList, "INCREMENTED LIST");
    printList(decList, "DECREMENTED LIST");
    printList(list, "CHANGED LIST");
    printList(mapIntI(list, dbl), "DOUBLED LIST");
    deleteList(decList);
    deleteList(incList);

    /***************************************************************/
    
    deleteList(list3);
    deleteList(list4);
    deleteList(list2);
    deleteList(list6);
    deleteList(h4);
    deleteList(kek1);
    deleteList(merged);
    deleteList(sortedList);

    

    return 0;
}

/*************/
int inc(int x)
{
    return x+1;
}
/*************/

/*************/
int dec(int x)
{
    return x-1;
}
/*************/

/****************/
int dbl(int x)
{
    return x << 1;
}
/****************/

