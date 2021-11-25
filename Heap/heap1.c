#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
//heap with property of minimum
struct Heap
{
	int * arr;
	int heap_size;
	int reserved_space;
};

int parent(int i)
{
	return (i-1) / 2;
}

int left(int i)
{
	return 2*i + 1;
}

int right(int i)
{
	return 2*i + 2;
}

void swap(int * a, int * b)
{
	int a1 = *a;
	int b1 = *b;
	*b = a1;
	*a = b1;
}

void Heap_swap(struct Heap * A, int i, int k)
{
    swap(&(A -> arr[i]), &(A -> arr[k]));
}

struct Heap * Heap_sift_up(struct Heap * A, int i)
{
	if ((A == NULL) || (i < 0))
		return NULL;
	if (i == 0)
		return A;
	int p = A -> arr[parent(i)];
	if (A -> arr[i] < p)
	{
        Heap_swap(A, i, parent(i));
		return Heap_sift_up(A, parent(i));
	}
	else
		return A;
}

struct Heap * Heap_sift_down(struct Heap * A, int i)
{
    if ((A == NULL) || (i < 0) )
        return NULL;
    if (i >= (A -> heap_size / 2))
    {
        return A;
    }
    int l = left(i);
    int r = right(i);
    int Al = A -> arr[l];
    int Ar = A -> arr[r];
    int Ai = A -> arr[i];
    if (Ai > Al)
    {
        if (Al > Ar)
        {
            Heap_swap(A, i, r);
            return Heap_sift_down(A, r);
        }
        else
        {
            Heap_swap(A, i, l);
            return Heap_sift_down(A, l);
        }
    }
    if (Ai > Ar)
    {
        if (Al < Ar)
        {
            Heap_swap(A, i, l);
            return Heap_sift_down(A, l);
        }
        else
        {
            Heap_swap(A, i, r);
            return Heap_sift_down(A, r);
        }
    }
    return A;
    
}

struct Heap * Heap_remove(struct Heap * A, int i)
{
    if (A == NULL)
        return NULL;
    int last = A -> heap_size - 1;
    Heap_swap(A, i, last);
    A -> heap_size--;
    Heap_sift_down(A, i);
    return A;
}

int Heap_get_min(struct Heap * A)
{
    if (A == NULL)
    {
        return INT_MAX;
    }
    else
    {
        return A -> arr[0];
    }
}

int Heap_extract_min(struct Heap * A)
{
    int tmp = Heap_get_min(A);
    Heap_remove(A, 0);
    //Heap_sift_down(A, 0);
    return tmp;
}

struct Heap * Heap_insert(struct Heap * A, int k)
{
	if (A == NULL)
	{
		A = (struct Heap *)malloc(sizeof(struct Heap));
		if (A == NULL)
			return NULL;
		A -> arr = (int*)malloc(sizeof(int));
		if (A -> arr == NULL)
			return NULL;
		A -> heap_size = 1;
		A -> reserved_space = 1;
		A -> arr[0] = k;
		return A;
	}
	int size = A -> heap_size;
	int space = A -> reserved_space;
	if (size == space)
	{
		A -> arr = (int*)realloc(A -> arr, space * 2*sizeof(int));
		if (A -> arr == NULL)
			return NULL;
		A -> reserved_space = 2*space;
	}
	A -> arr[size] = k;
	A -> heap_size++;
	return Heap_sift_up(A, size);
}

void Heap_free(struct Heap * A)
{
	if (A == NULL)
		return;
	A -> heap_size = 0;
	A -> reserved_space = 0;
	free(A -> arr);
	free(A);
}

int Heap_traverse(struct Heap * A, int (*func)(const char*,...))
{
	if (A == NULL)
    {
        printf("\n");
		return 0;
    }
	for (int i = 0; i < A -> heap_size; i++)
	{
		func("%d ", A -> arr[i]);
	}
	return func("\n");
}

int Heap_is_empty(struct Heap * A)
{
    if ((A == NULL) || (A -> heap_size > 0))
        return 0;
    else
        return 1;
}

struct Heap * Heap_sort(struct Heap * A, int flags)
{
    if (A == NULL)
        return A;
    if (flags & 1)
    {
        struct Heap * tmp = (struct Heap *)malloc(sizeof(struct Heap));
        if (tmp == NULL)
        {
            printf("New heap allocation failed, contunuing with in-line sorting\n");
            return Heap_sort(A, 0);
        }
        tmp -> reserved_space = A -> reserved_space;
        tmp -> heap_size = 0;
        tmp -> arr = (int*)malloc((A -> heap_size)*sizeof(struct Heap));
        if (tmp -> arr == NULL)
        {
            printf("New heap allocation failed on array, contunuing with in-line sorting\n");
            return Heap_sort(A, 0);
        }
        
        for (;A -> heap_size > 0;)
        {
            tmp -> arr[tmp -> heap_size++] = Heap_extract_min(A);
        }
        if (flags & 2)
            Heap_free(A);
        return tmp;
    }
    else
    {
        int size = A -> heap_size;
        int last = size-1;
        int tmp;
        for (;last >= 0;last--)
        {
            tmp = Heap_extract_min(A);
            A -> arr[last] = tmp;
        }
        A -> heap_size = size;
        for (int i = 0; i < size / 2; i++)
        {
            Heap_swap(A, i, size - 1 - i);
        }
        return A;
    }
}
