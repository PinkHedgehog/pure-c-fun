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
int inc (int x);
int dec (int x);
int dbl (int x);


int
main ()
{
    /***************************************************************/

  List list = NULL;
  list = cons (7, list);
  list = cons (5, list);
  list = cons (3, list);
  list = cons (2, list);
  printList (list, "LIST");

    /***************************************************************/

  List list2 = copy (list);
  printList (list2, "COPY");

    /***************************************************************/

  List list3 = reverse (list);
  printList (list3, "REVERSE");

    /***************************************************************/

  /* list1 \--> list4 */
  List list4 = reverseI (list);
  printList (list4, "IN-PLACE");
  /* cannot be used anymore */

    /***************************************************************/

  List h4 = head (list4);	/* to be freed */
  List h3 = headI (list3);	/* will be freed by list3 */
  List kek1 = indexList (3, list3);
  List kek2 = indexListI (2, list2);
  List list6 = NULL;
  list6 = cons (h4->value, list6);
  list6 = cons (h3->value, list6);
  list6 = cons (kek1->value, list6);
  list6 = cons (kek2->value, list6);
  printList (list6, "ELEMENTS FROM OTHER LISTS");

    /***************************************************************/

  List list5 = reverseI (copy (tailI (list2)));
  printList (list5, "REVERSE OF TAIL OF LIST2");

    /***************************************************************/

  List t1 = tailI (list2);
  List h1 = headI (list2);
  List r1 = reverseIP (t1, h1);
  List t2 = tailI (r1);
  List h2 = headI (r1);
  List r2 = reverseIP (t2, h2);
  List kek3 = r2;
  kek3 = reverseI (cons (9, reverseI (copy (kek3))));
  printList (kek3, "KEK3");

    /***************************************************************/

  List merged = merge (kek3, reverseI (list5));
  printList (merged, "MERGED");
  printList (list2, "AFTER KEK3");

    /***************************************************************/

  printf ("\nKEK3 LENGTH: %d\n", length (kek3));

    /***************************************************************/

  list = NULL;
  list = cons (1, list);
  list = cons (5, list);
  list = cons (2, list);
  list = cons (4, list);
  list = cons (3, list);
  printList (list, "NEW LIST");

    /***************************************************************/

  deleteList (list2);
  list2 = take (2, list);
  printList (list2, "TAKE 2 FROM LIST");

    /***************************************************************/

  List sortedList = sortI (copy (list));
  printList (sortedList, "SORTED LIST");

    /***************************************************************/

  List incList = mapIntI (list, inc);
  List decList = mapInt (incList, dec);
  printList (incList, "INCREMENTED LIST");
  printList (decList, "DECREMENTED LIST");
  printList (list, "CHANGED LIST");
  printList (mapIntI (list, dbl), "DOUBLED LIST");
  deleteList (decList);
  deleteList (incList);

    /***************************************************************/

  deleteList (list3);
  deleteList (list4);
  deleteList (list2);
  deleteList (list6);
  deleteList (h4);
  deleteList (kek1);
  deleteList (merged);
  deleteList (sortedList);

  list = NULL;
  list = cons (24, list);
  list = cons (16, list);
  list = cons (8, list);
  list = cons (5, list);
  list = cons (1, list);
  printList (list, "LIST");
  //printf("=== LIST LENGTH %d ===\n", length(list));
  list2 = NULL;
  list2 = cons (5, list2);
  list2 = cons (4, list2);
  list2 = cons (3, list2);
  list2 = cons (2, list2);
  printList (list2, "LIST2");
  list3 = NULL;
  list3 = cons (8, list3);
  list3 = cons (4, list3);
  list3 = cons (2, list3);
  list3 = cons (1, list3);
  printList (list3, "LIST3");
  //list4 = NULL;
  //List arr[5] = {list, list2, NULL, list3, list4};
  List arr[3] = { list, list2, list3 };
  List answ = mergelists (arr, 3);
  printList (answ, "MERGELISTS");
  deleteList (answ);






  return 0;
}

/*************/
int
inc (int x)
{
  return x + 1;
}

/*************/

/*************/
int
dec (int x)
{
  return x - 1;
}

/*************/

/****************/
int
dbl (int x)
{
  return x << 1;
}

/****************/
