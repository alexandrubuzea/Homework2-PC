// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef TASK3_H_
#define TASK3_H_

void transform_map(int n, int **v, int *m);
void fill(int n, int **v, int *m, int i, int j, int k, int *count);
int fill_map(int n, int **v, int *m, int **line, int **col, int **dimension);
int max_black_hole(int num_holes, int *line, int *col, int *dimension);

#endif
