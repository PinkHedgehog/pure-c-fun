#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
 * Postfix I means "in-place" or something similar, when it's possible
 * Postfix P in *reverseIP* means saving previous items order, when they
 * are given 
 */


/****************************************************/
List
cons(int x, List list)
{
    List            node = (List) malloc(sizeof(Node));

    if (NULL == node) {
	perror("\n*** MEMORY ALLOCATION ERROR ***\n");
	return list;
    }

    node->value = x;
    node->next = list;
    // list = node;

    return node;
}
/****************************************************/

/************************************************************/
List
copy(List list)
{
    if (NULL == list) {
	return NULL;
    }

    List            node = NULL;
    List            i1 = NULL;
    List            i2 = list;

    int             isFirst = 1;

    for (; i2; i2 = i2->next) {
	if (isFirst) {
	    i1 = (List) malloc(sizeof(Node));
	    if (NULL == i1) {
		perror("\n*** MEMORY ALLOCATION ERROR ***\n");
		return NULL;
	    }
	    i1->value = i2->value;
	    i1->next = NULL;
	    node = i1;
	    isFirst = 0;
	} else {
	    List            tmp = (List) malloc(sizeof(Node));
	    if (NULL == tmp) {
		perror("\n*** MEMORY ALLOCATION ERROR ***\n");
		return NULL;
	    }
	    tmp->value = i2->value;
	    tmp->next = NULL;
	    i1->next = tmp;
	    i1 = i1->next;
	}
    }

    return node;
}
/************************************************************/

/****************************************************/
List
head(List list)
{
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }
    List            node = (List) malloc(sizeof(Node));
    if (NULL == node) {
	perror("\n*** MEMORY ALLOCATION ERROR ***\n");
	return NULL;
    }
    node->value = list->value;
    node->next = NULL;
    return node;
}
/****************************************************/

/***************************************/
List
headI(List list)
{
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }
    return list;
}
/***************************************/

/***************************************/
List
deleteFirst(List list)
{
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }

    List            tmp = list;
    list = list->next;
    free(tmp);
    return list;
}
/***************************************/

/***************************************/
List
tail(List list)
{
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }
    return copy(list->next);
}
/***************************************/


/***************************************/
List
tailI(List list)
{
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }
    return list->next;
}
/***************************************/



/**************************/
void
deleteList(List list)
{
    for (; list;) {
	List            tmp = list;
	list = list->next;
	free(tmp);
    }
}
/**************************/

/*************************************/
List
reverse(List list)
{
    List            rev = NULL;
    for (; list; list = list->next) {
	rev = cons(list->value, rev);
    }
    return rev;
}
/*************************************/

/******************************/
List
reverseI(List list)
{
    List            rev = NULL;
    for (; list;) {
	List            tmp = list->next;
	list->next = rev;
	rev = list;
	list = tmp;
    }
    return rev;
}
/******************************/

/**********************************/
List
reverseIP(List list, List prev)
{
    List            rev = NULL;
    for (; list;) {
	List            tmp = list->next;
	list->next = rev;
	rev = list;
	list = tmp;
    }
    if (prev) {
	prev->next = rev;
    }
    return rev;
}
/**********************************/

/*****************************************/
void
printList(List list, const char *msg)
{
    printf("\n=== %s ===\n", msg);
    List            node = list;

    for (; node; node = node->next)
	printf("%d ", node->value);

    printf("\n");
    int             len = strlen(msg);
    for (int i = 0; i < len + 8; i++)
	printf("=");
    printf("\n");
}
/*****************************************/

/*******************************************************/
List
indexListI(int idx, List list)
{
    List            iter = list;
    for (; idx > 0; idx--, iter = iter->next) {
	if (NULL == iter) {
	    perror("\n*** INDEX IS OUT OF BOUNDS ***\n");
	    return NULL;
	}
    }
    return iter;
}
/*******************************************************/

/*******************************************************/
List
indexList(int idx, List list)
{
    List            iter = list;
    if (NULL == list) {
	perror("\n*** EMPTY LIST ***\n");
	return NULL;
    }
    for (; idx > 0; idx--, iter = iter->next) {
	if (NULL == iter) {
	    perror("\n*** INDEX IS OUT OF BOUNDS ***\n");
	    return NULL;
	}
    }
    List            tmp = (List) malloc(sizeof(Node));
    if (NULL == tmp) {
	perror("\n*** MEMORY ALLOCATION ERROR ***\n");
	return NULL;
    }
    tmp->value = iter->value;
    tmp->next = NULL;
    return tmp;
}
/*******************************************************/

/***********************************************/
int
length(List list)
{
    int             l;
    for (l = 0; list; list = list->next, l++);
    return l;
}
/***********************************************/

/*******************************************/
List
merge(List list1, List list2)
{
    if (NULL == list1) {
	return list2;
    }
    if (NULL == list2) {
	return list1;
    }

    List            merged = NULL;

    if (list1->value <= list2->value) {
	merged = list1;
	list1 = list1->next;
    } else {
	merged = list2;
	list2 = list2->next;
    }
    List            iter = merged;

    for (; 1;) {
	if (NULL == list1) {
	    iter->next = list2;
	    break;
	}
	if (NULL == list2) {
	    iter->next = list1;
	    break;
	}
	if (list1->value <= list2->value) {
	    iter->next = list1;
	    list1 = list1->next;

	} else {
	    iter->next = list2;
	    list2 = list2->next;
	}
	iter = iter->next;
    }
    return merged;
}
/*******************************************/

/*********************************************/
List
mapIntI(List list, int (*mapFunc)(int x))
{
    List            tmp = list;
    for (; list; list = list->next) {
	list->value = mapFunc(list->value);
    }
    return tmp;
}
/*********************************************/

/*************************************************************/
List
mapInt(List list, int (*mapFunc)(int x))
{
    List            list2 = copy(list);
    list2 = mapIntI(list2, mapFunc);
    return list2;
}
/*************************************************************/

/****************************************************/
List
takeI(int n, List list)
{
    /*
     * caller must save items from n to last 
     */
    List            node = list;
    for (int i = 0; i < n - 1; i++) {
	if (NULL == list) {
	    perror("\n*** INSUFFICIENT ITEMS ***\n");
	    return NULL;
	}
	list = list->next;
    }
    if (NULL == list) {
	perror("\n*** INSUFFICIENT ITEMS ***\n");
	return NULL;
    }
    list->next = NULL;
    return node;
}
/****************************************************/

/****************************************************/
List
take(int n, List list)
{
    List            tmp = NULL;
    for (int i = 0; i < n; i++) {
	if (NULL == list) {
	    perror("\n*** INSUFFICIENT ITEMS ***\n");
	    return NULL;
	}
	tmp = cons(list->value, tmp);
	list = list->next;
    }
    tmp = reverseI(tmp);
    return tmp;
}
/****************************************************/

/**********************************************/
List
sortI(List list)
{
    if (NULL == list) {
	return NULL;
    }
    if (NULL == list->next) {
	return list;
    }
    int             len = length(list);
    len = (len + 1) / 2;
    List            right = indexListI(len, list);
    List            left = takeI(len, list);
    return merge(sortI(left), sortI(right));
}
/**********************************************/

/*******************************************/
List
sort(List list)
{
    return sortI(copy(list));
}
/******************************************/

List
mergelists(List * arr, int arrlen)
{
    List            merged = NULL;
    List            result = merged;
    for (int i = 0; i < arrlen; i++) {

	if (NULL == arr[i])
	    continue;
	List            list1 = merged;
	List            list2 = arr[i];
	if (NULL == list1) {
	    merged = list2;
	    continue;
	}
	if (list1->value <= list2->value) {
	    merged = list1;
	    list1 = list1->next;
	} else {
	    merged = list2;
	    list2 = list2->next;
	}
	List            iter = merged;

	for (; 1;) {
	    if (NULL == list1) {
		iter->next = list2;
		break;
	    }
	    if (NULL == list2) {
		iter->next = list1;
		break;
	    }
	    if (list1->value <= list2->value) {
		iter->next = list1;
		list1 = list1->next;

	    } else {
		iter->next = list2;
		list2 = list2->next;
	    }
	    iter = iter->next;
	}
	result = merged;

    }

    return result;
}
