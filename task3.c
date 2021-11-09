// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdlib.h>

// A function that turns the non-zero valued bytes into FF = -1
void transform_map(int n, int **v, int *m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < *(m + i); ++j) {
			char *p = (char *)(*(v + i) + j); // in order to work on bytes.
			for (int k = 0; k < (int)sizeof(int); ++k)
				if (*(p + k))
					*(p + k) = -1;
		}
	}
}

// A function that marks a zero-valued byte, counts it and searches
// recursively for other zero-valued bytes.
void fill(int n, int **v, int *m, int i, int j, int k, int *count)
{
	char *p = ((char *)(*(v + i) + j)) + k; // Get a pointer to our byte.
	*p = 1; // Mark the byte
	(*count)++; // Count the zero-valued byte.

	// Case I: Search the byte from right (if it exists, and if it is zero).
	if (j < *(m + i) - 1 || k < 3)
		if (*(p + 1) == 0)
			fill(n, v, m, i, j + ((k + 1) / 4), (k + 1) % 4, count);

	// Case II: Search the byte under (if it exists, and if it is zero).
	if (i < n - 1) {
		if (j < *(m + i + 1)) {
			char *q = ((char *)(*(v + i + 1) + j)) + k;
			if (*q == 0)
				fill(n, v, m, i + 1, j, k, count);
		}
	}

	// Case III: Search the byte on (if it exists, and if it is zero).
	if (j > 0 || k > 0)
		if (*(p - 1) == 0)
			fill(n, v, m, i, j - 1 + ((k + 3) / 4), (k + 3) % 4, count);

	// Case IV: Search the byte from left (if it exists, and if it is zero).
	if (i > 0) {
		if (j < *(m + i - 1)) {
			char *r = ((char *)(*(v + i - 1) + j)) + k;
			if (*r == 0)
				fill(n, v, m, i - 1, j, k, count);
		}
	}
}

// A function that allocs dinamically three pointers / reallocs tree arrays.
void realloc_arrays(int num_holes, int **line, int **col, int **dimension)
{
	// Case I: The arrays are not yet allocated
	if (num_holes == 0) {
		*line = (int *)malloc(1 * sizeof(int));
		if (!*line)
			exit(1);
		*col = (int *)malloc(1 * sizeof(int));
		if (!*col)
			exit(1);
		*dimension = (int *)malloc(1 * sizeof(int));
		if (!*dimension)
			exit(1);
	} else { // Case II: The arrays are allocated, but are too small.
		*line = (int *)realloc(*line, (num_holes + 1) * sizeof(int));
		*col = (int *)realloc(*col, (num_holes + 1) * sizeof(int));
		*dimension = (int *)realloc(*dimension,
		(num_holes + 1) * sizeof(int));
		if (!*line)
			exit(1);
		if (!*col)
			exit(1);
		if (!*dimension)
			exit(1);
	}
}

int fill_map(int n, int **v, int *m, int **line, int **col, int **dimension)
{
	int num_holes = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < *(m + i); ++j) {
			char *p = (char *)(*(v + i) + j); //Get a pointer to our byte.
			for (int k = 0; k < (int)sizeof(int); ++k) {
				if (*(p + k) == 0) { // When zero, start the search.
					int count = 0;
					realloc_arrays(num_holes, line, col, dimension);
					fill(n, v, m, i, j, k, &count); // The search.
					*(*line + num_holes) = i;
					*(*col + num_holes) = (int)sizeof(int) * j + k;
					*(*dimension + num_holes) = count;
					num_holes++;
				}
			}
		}
	}
	return num_holes;
}

// Classical maximum algorithm with multiple criteria.
int max_black_hole(int num_holes, int *line, int *col, int *dimension)
{
	int kmax = 0;
	for (int i = 0; i < num_holes; ++i) {
		if (*(dimension + kmax) < *(dimension + i)) {
			kmax = i;
		} else if (*(dimension + kmax) == *(dimension + i)) {
			if (*(line + kmax) > *(line + i)) {
				kmax = i;
			} else if (*(line + kmax) == *(line + i)) {
				if (*(col + kmax) > *(col + i))
					kmax = i;
			}
		}
	}
	return kmax;
}
