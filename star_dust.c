// Buzea Alexandru-Mihai-Iulian 311CAb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "other.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(void)
{
	int n;
	scanf("%d", &n);
	int *m = (int *)malloc(n * sizeof(int));
	int **map = alloc_read_map(n, m);
	printf("task 1\n");
	printf("%.8lf\n", shield_charge(n, m, map));

	printf("task 2\n");
	int k;
	scanf("%d", &k);
	for (int i = 0; i < k; ++i) {
		char op, dim;
		scanf(" %c %c", &op, &dim);
		int line, index;
		scanf("%d%d", &line, &index);
		if (op == 'M') {
			int newval;
			scanf("%X", &newval);
			modify(dim, line, index, newval, map, m);
		} else if (op == 'D') {
			delete(dim, line, index, map, m);
		} else {
			swap(dim, line, index, map, m);
		}
	}
	print_map(n, map, m);

	printf("task 3\n");
	transform_map(n, map, m);
	int *line;
	int *col;
	int *dimension;
	int num_holes = fill_map(n, map, m, &line, &col, &dimension);
	int kmax = max_black_hole(num_holes, line, col, dimension);
	printf("%d %d %d\n", *(line + kmax), *(col + kmax), *(dimension + kmax));

	free_map(n, &map, &m);
	free(col);
	free(line);
	free(dimension);
	return 0;
}
