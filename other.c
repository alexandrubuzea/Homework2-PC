// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>

// A function that allocs our map (array of pointers + multiple arrays
// representing lines in the matrix).
int **alloc_read_map(int n, int *m)
{
	int **v = (int **)malloc(n * sizeof(int *));
	if (!v)
		exit(1);
	for (int i = 0; i < n; ++i) {
		scanf("%d", m + i);
		*(v + i) = (int *)malloc(*(m + i) * sizeof(int));
		if (!*(v + i))
			exit(1);
		for (int j = 0; j < *(m + i); ++j)
			scanf("%X", *(v + i) + j);
	}
	return v;
}

// A function that frees our map and our array of sizes.
void free_map(int n, int ***v, int **m)
{
	free(*m);
	for (int i = 0; i < n; ++i)
		free(*(*v + i));
	free(*v);
}
