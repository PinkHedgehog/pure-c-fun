#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*****************************************************************************/
/* Declararion                                                               */
/*****************************************************************************/
struct Node
{
    int key;
    unsigned int height;
    struct Node * left;
    struct Node * right;
};
/*****************************************************************************/



/*****************************************************************************/
/* UTILS                                                                     */
/*****************************************************************************/
unsigned int height(struct Node * node)
{
    return (NULL != node) ? node -> height : 0;
}
/*****************************************************************************/
int bFactor(struct Node * node)
{
    return height(node -> right) - height(node -> left);
}
/*****************************************************************************/
void fixHeight(struct Node * node)
{
	unsigned int hl = height(node -> left);
	unsigned int hr = height(node -> right);
	node -> height = (hl > hr ? hl : hr) + 1;
}
/*****************************************************************************/



/*****************************************************************************/
/* ROTATIONS & BALANCING                                                     */
/*****************************************************************************/
struct Node * rotateRight(struct Node * p) // правый поворот вокруг p
{
	struct Node * q = p -> left;
	p -> left = q -> right;
	q -> right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}
/*****************************************************************************/
struct Node * rotateLeft(struct Node * p) // правый поворот вокруг p
{
	struct Node * q = p -> right;
	p -> right = q -> left;
	q -> left = p;
	fixHeight(q);
	fixHeight(p);
	return q;
}
/*****************************************************************************/
struct Node * balance(struct Node * p) // балансировка узла p
{
	fixHeight(p);
	if (bFactor(p) == 2)
	{
		if (bFactor(p -> right) < 0)
			p -> right = rotateRight(p -> right);
		return rotateLeft(p);
	}
	if (bFactor(p) == -2)
	{
		if (bFactor(p -> left) > 0)
			p -> left = rotateLeft(p -> left);
		return rotateRight(p);
	}
	return p; // балансировка не нужна
}
/*****************************************************************************/



/*****************************************************************************/
/* TREE OPERATIONS                                                           */
/*****************************************************************************/
struct Node * insert(struct Node * tree, int k)
{
    if (NULL == tree)
    {
        tree = (struct Node *) malloc(sizeof(struct Node));
        tree -> left = NULL;
        tree -> right = NULL;
        tree -> key = k;
        tree -> height = 1;
    }
    else
    {
        if (k < tree -> key)
        {
            tree -> left = insert(tree -> left, k);
        }
        else
        {
            if (tree -> key < k)
            {
                tree -> right = insert(tree -> right, k);
            } 
        }
    }
    return balance(tree);
}
/*****************************************************************************/
struct Node * findMin(struct Node * p) // поиск узла с минимальным ключом в дереве p 
{
	return p -> left ? findMin(p -> left) : p;
}
/*****************************************************************************/
struct Node * removeMin(struct Node * p) // удаление узла с минимальным ключом из дерева p
{
	if (p -> left == 0 )
		return p -> right;
	p -> left = removeMin(p -> left);
	return balance(p);
}
/*****************************************************************************/
struct Node * removeKey(struct Node * p, int k) // удаление ключа k из дерева p
{
	if(NULL ==  p) 
        return 0;
	if (k < p -> key)
		p -> left = removeKey(p -> left, k);
	else 
    {
        if (k > p -> key)
		    p -> right = removeKey(p -> right, k);
        else //  k == p->key 
        {
            struct Node * q = p->left;
            struct Node * r = p->right;
            free(p);
            if (NULL == r) return q;
            struct Node * min = findMin(r);
            min -> right = removeMin(r);
            min -> left = q;
            return balance(min);
        }
    }
    return balance(p);
}
/*****************************************************************************/



/*****************************************************************************/
/* TRAVERSE                                                                  */
/*****************************************************************************/
void inOrder(struct Node * tree)
{
    if (NULL == tree)
    {
        return;
    }
    else
    {
        inOrder(tree -> left);
        printf("%d ", tree -> key);
        inOrder(tree -> right);
    }
}
/*****************************************************************************/
void preOrder(struct Node * tree)
{
    if (NULL == tree)
    {
        return;
    }
    else
    {
        printf("%d ", tree -> key);
        preOrder(tree -> left);
        preOrder(tree -> right);
    }
}
/*****************************************************************************/
void postOrder(struct Node * tree)
{
    if (NULL == tree)
    {
        return;
    }
    else
    {
        postOrder(tree -> left);
        postOrder(tree -> right);
        printf("%d ", tree -> key);
    }
}
/*****************************************************************************/
void clearTree(struct Node * tree)
{
    if (NULL == tree)
    {
        return;
    }
    else
    {
        clearTree(tree -> left);
        clearTree(tree -> right);
        free(tree);
    }
}
/*****************************************************************************/


/*
 *****************************************************************************
 *                                                                           *
 *                   m       m        a        iii    n    n                 *
 *                   m m   m m       a a        i     nn   n                 *
 *                   m  m m  m      a   a       i     n n  n                 *
 *                   m   m   m     aaaaaaa      i     n  n n                 *
 *                   m       m    a       a     i     n   nn                 *
 *                   m       m   a         a   iii    n    n                 *
 *                                                                           *
 *****************************************************************************
*/
int main()
{
    struct Node * tree = NULL;

    int n;
    scanf("%d", &n);
    for (; n > 0; scanf("%d", &n))
    {
        tree = insert(tree, n);
    }
    printf("\n=== PREORDER WALK ===\n");
    preOrder(tree);
    printf("\n=====================\n");
    printf("\n=== INORDER WALK ===\n");
    inOrder(tree);
    printf("\n====================\n");
    printf("\n=== POSTORDER WALK ===\n");
    postOrder(tree);
    printf("\n======================\n");
    printf("\n");

    clearTree(tree);
    return 0;

}
/*****************************************************************************/


/* useful links
https://habr.com/ru/post/150732/
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
https://ru.wikipedia.org/wiki/%D0%90%D0%92%D0%9B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
https://www.youtube.com/watch?v=jDM6_TnYIqE
*/
