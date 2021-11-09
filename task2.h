// Buzea Alexandru-Mihai-Iulian 311CAb

#ifndef TASK2_H_
#define TASK2_H_

void *pointer(char dim, int line, int index, int **v, int *m);
void swap_values(char *p, char *q);
void modify(char dim, int line, int index, int newval, int **v, int *m);
void delete(char dim, int line, int index, int **v, int *m);
void swap(char dim, int line, int index, int **v, int *m);
void print_map(int n, int **v, int *m);

#endif
