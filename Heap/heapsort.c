#include <stdlib.h>

struct Heap
{
	int * arr;
	int heap_size;
};

int parent(int i)
{
	return i / 2;
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return 2*i + 1;
}

void Heap_max_heapify(struct Heap * A, int i)
{
	if (A == NULL)
		return;
	if (i < 0)
		return;
	int l = left(i);
	int r = right(i);
	int largest;
	if ((l <= A -> heap_size) && (A -> arr[l] > A -> arr[i]))
	{
		largest = l;
	}
	else
		largest = i;
	if ((r <= A -> heap_size) && (A -> arr[r] > A -> arr[largest]))
		largest = r;
	if (largest != i)
	{
		int t = A -> arr[i];
		A -> arr[i] = A -> arr[largest];
		A -> arr[largest] = t;
		Heap_max_heapify(A, largest);
	}
}

void Heap_free(struct Heap * A)
{
	if (A == NULL)
		return;
	A -> heap_size = 0;
	free(A -> arr);
	free(A);
}

int Heap_traverse(struct Heap * A, int (*func)(const char*,...))
{
	if (A == NULL)
		return 1;
	int i;
	for (i = 1; i <= A -> heap_size; i++)
	{
		func("%d ", A -> arr[i]);
	}
	func("\n");
    return 0;
}

int Heap_build(struct Heap * A)
{
	if (A == NULL)
		return 1;
	A -> heap_size = A -> arr[0];
	for (int i = A -> heap_size / 2 ; i >= 1; i--)
	{
		Heap_max_heapify(A, i);
	}
	return 0;
}

int Heap_sort(struct Heap * A)
{
	if (A == NULL)
		return 1;
	for (int i = A -> arr[0]; i >= 2; i--)
	{
		int t = A -> arr[1];
		A -> arr[1] = A -> arr[i];
		A -> arr[i] = t;
		A -> heap_size--;
		Heap_max_heapify(A, 1);
	}
    return 0;
	//A -> heap_size = A -> arr[0];
}

int Heap_length(struct Heap * A)
{
	if (A == NULL)
		return -1;
	return A -> arr[0];
}

struct Heap * Heap_create(int n)
{
	struct Heap * t = (struct Heap *)malloc(sizeof(struct Heap));
	if (t == NULL)
		return NULL;
	t -> arr = (int*)malloc((n+1)*sizeof(int));
	if (t -> arr == NULL)
		return NULL;
	t -> arr[0] = n;
	for (int i = 1; i <= n; i++)
	{
		t -> arr[i] = 0;
	}
	t -> heap_size = n;
	//Heap_build(t);
	return t;
}

void Heap_sort_arr(int * a, int n)
{
	struct Heap * t = Heap_create(n);
	if (t == NULL)
		return;
	for (int i = 0; i < n; i++)
	{
		t -> arr[1+i] = a[i];
	}
	Heap_build(t);
	Heap_sort(t);
	//printf("TRAVERSE\n");
	//Heap_traverse(t, printf);
	//printf("TRAVERSE\n");
	for (int i = 0; i < n; i++)
		a[i] = t -> arr[i+1];
	Heap_free(t);

}
