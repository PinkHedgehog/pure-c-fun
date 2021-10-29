#ifndef LIST_H_
#define LIST_H_


struct Node
{
    int value;
    struct Node * next;
};

typedef struct Node * List;

List cons(int x, List list);
List copy(List list);
List head(List list);
List headI(List list);
List deleteFirst(List list);
List tail(List list);
List tailI(List list);
void deleteList(List list);
List reverse(List list);
List reverseI(List list);
List reverseIP(List list, List prev);
void printList(List list, const char * msg);
List indexListI(int idx, List list);
List indexList(int idx, List list);
int length(List list);
List merge(List list1, List list2);
List mapIntI(List list, int (*mapFunc)(int x));
List mapInt(List list, int (*mapFunc)(int x));
List takeI(int n, List list);
List take(int n, List list);
List sortI(List list);



#endif
