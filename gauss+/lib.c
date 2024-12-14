#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"

static double f1(int n, int i, int j){
	return (i > j? n - i + 1: n - j + 1);
}
static double f2(int n, int i, int j){
	return (i >= j? i:j);
	n = n;
}
static double f3(int n, int i, int j){
	return abs(i - j);
	n = n;
}
static double f4(int n, int i, int j){
	return 1./(i + j - 1);
	n = n;
}

void fill_B (double *b, double *a, int n){
	memset(b, 0, n*n);
	for (int j = 0; j < n; j++) {
		for(int i = 0; i <= (n+1)/2; i++) {
			printf("a[%d,%d] %10.3f\n",j,2*i,a[j*n + 2*i]);
			b[j] += a[j*n + 2*i];
		}

		printf("b[%d] %10.3f\n", j, b[j]);
		printf("\n");
	}
}	

int get_matrix(char* filename, double *a, int n){
	FILE *file  = NULL;
	file = fopen(filename, "r");
	if (file == NULL) return -1;
	for (int i = 0; i < n*n; i++){
		if (fscanf(file, "%lf", a + i) == EOF) {
			printf("\x1b[91m Недостаточно данных в файле\x1b[0m\n");
			return -1;
		}
	}
	return 1;
}

int calculate_matrix(int k, double *a, int n){
	double (*func)(int n, int i, int j);
	if (k > 4 || k < 0) return -1;
	if (k == 1) func = f1;
	if (k == 2) func = f2;
	if (k == 3) func = f3;
	if (k == 4) func = f4;
	for (int i = 0; i < n*n; i++) a[i] = func(n, i/n, i);
	return 1;	
}

void nevyazka(double *a, double *b, double *x, int n){
	double na = 0, nb = 0, ntot = 0;

	for (int j = 0; j < n; j++){
		na = 0;
		for (int i = 0; i < n; i++){
			na += a[j*n+i] * x[i];	
		}
		na -= b[j];
		nb += fabs(b[j]);
		ntot += fabs(na);
    	}
	printf("nevyazka: %e\n", ntot/nb);
	return;
}

void print_matrix (double *a, double *b, int n){
	printf("\x1b[95m");
	printf("\n");

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) printf(" %10.3e", a[i*n +j]);
		printf("\x1b[96m");
		printf(" %10.3e",b[i]); 
		printf("\n\x1b[95m");
	}

	printf("\x1b[0m");
	printf("\n\n");
}
