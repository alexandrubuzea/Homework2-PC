// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A function that returns a pointer to void to a specific place in map.
void *pointer(char dim, int line, int index, int **v, int *m)
{
	// Step I: translating index in terms of numbers of bytes for each type.
	if (dim == 'C') {
		index *= (int)sizeof(char);
		index -= (int)sizeof(char);
		++index;
	} else if (dim == 'S') {
		index *= (int)sizeof(short);
		index -= (int)sizeof(short);
		++index;
	} else {
		index *= (int)sizeof(int);
		index -= (int)sizeof(int);
		++index;
	}

	// Step 2: Translating index in terms of numbers of integers (4 bytes).
	int j = (index - 1) / ((int)sizeof(int));
	int k = (index - 1) % ((int)sizeof(int));

	// Step 3: Treating situation where the given index is not in the map.
	if (j >= *(m + line)) {
		*(v + line) = (int *)realloc(*(v + line), (j + 1) * sizeof(int));
		if (!*(v + line))
			exit(1);
		for (int i = *(m + line); i <= j; ++i)
			*(*(v + line) + i) = 0;
		*(m + line) = j + 1;
	}

	// Step 4: In order to use the function on all datatypes, we need to
	// cast the pointer into void *.
	void *p = (void *)((char *)((*(v + line) + j)) + k);
	return p;
}

// Classic swap function with pointers
void swap_values(char *p, char *q)
{
	char tmp = *p;
	*p = *q;
	*q = tmp;
}

// Modify function: a function that uses the previous-defined function in
// order to modify a memory zone.
void modify(char dim, int line, int index, int newval, int **v, int *m)
{
	if (dim == 'C') {
		char *p = (char *)pointer(dim, line, index, v, m);
		*p = (char)newval;
	} else if (dim == 'S') {
		short *p = (short *)pointer(dim, line, index, v, m);
		*p = (short)newval;
	} else {
		int *p = (int *)pointer(dim, line, index, v, m);
		*p = newval;
	}
}

// Delete function: similar to modify function.
void delete(char dim, int line, int index, int **v, int *m)
{
	if (dim == 'C') {
		char *p = (char *)pointer(dim, line, index, v, m);
		*p = 0;
	} else if (dim == 'S') {
		short *p = (short *)pointer(dim, line, index, v, m);
		*p = 0;
	} else {
		int *p = (int *)pointer(dim, line, index, v, m);
		*p = 0;
	}
}

// Swap function: swaps the values of bytes. For char it doesn't make
// any sense to swap bytes since it's only one byte.
void swap(char dim, int line, int index, int **v, int *m)
{
	if (dim == 'S') {
		char *p = (char *)pointer(dim, line, index + 1, v, m);
		for (int i = 0; i < (int)sizeof(short) / 2; ++i)
			swap_values(p + i, p + (int)sizeof(short) - 1 - i);
	} else if (dim == 'I') {
		char *p = (char *)pointer(dim, line, index + 1, v, m);
		for (int i = 0; i < (int)sizeof(int) / 2; ++i)
			swap_values(p + i, p + (int)sizeof(int) - 1 - i);
	}
}

// Classic function that prints a matrix with variable row length.
void print_map(int n, int **v, int *m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < *(m + i); ++j)
			printf("%08X ", *(*(v + i) + j));
		printf("\n");
	}
}
