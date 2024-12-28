#ifndef LIB_H
#define LIB_H

#include<stdio.h>

void fill_B(double *b, double *a, int n);
int get_matrix(char *filename, double *a, int n);
int calculate_matrix(int k, double *a, int n);

int solve(int n, double *a, double *b, double *x);
void nevyazka(double *a, double *b, double *x, int n);
void difference(double* x, int n);
void print_matrix(double *a, double *b, int n);

#endif //LIB_H