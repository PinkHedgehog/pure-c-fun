#include <stdio.h>
#include <stdlib.h>
#include "heapsort.c"

int main(int argc, char * argv[])
{
	int n;
	scanf("%d", &n);/*
	struct Heap * a = (struct Heap*)malloc(sizeof(struct Heap));
	if (a == NULL) return 1;
	a -> arr = (int*)malloc((n+1)*sizeof(int));
	if (a -> arr == NULL) return 2;
	a -> heap_size = n;
	a -> arr[0] = n;
	*/

	int * a = (int *)malloc(n*sizeof(int));
	if (a == NULL)
		return 1;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	//Heap_build(a);
	Heap_sort_arr(a, n);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	//Heap_traverse(a, printf);
	free(a);
	return 0;
}

