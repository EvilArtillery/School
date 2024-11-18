#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"lib.h"

static double* pro_m(double *a, double *x, int n){
	double *tmp = malloc(n*sizeof(*tmp));
	if (NULL == tmp) return NULL;
	for (int i = 0; i < n; i++) tmp[i] = 0;
	for (int j = 0; j < n; j++){
		for (int i = 0; i < n; i++) tmp[j] += x[i]*a[j*n + i];
	}
	return tmp;
}	

static double f1(int n, int i, int j){
	return (i > j? n - i: n - j);
}
static double f2(int n, int i, int j){
	return(i > j? i:j) + n - n;
}
static double f3(int n, int i, int j){
	return fabs(i - j) + n - n;
}
static double f4(int n, int i, int j){
	return 1./(i + j + 1) + n - n;
}
void fill_B (double *b, double *a, int n){
	for (int i = 0; i < n; i++) b[i] = 0;
	for (int j = 0; j < n; j++) for(int i = 0; i < n; i++) b[j] += a[j*n + i];
}

int get_matrix(char* filename, double *a, int n){
	FILE *file  = NULL;
	file = fopen( filename, "r");
	if (file == NULL) return -1;
	for (int i = 0; i < n*n; i++){
		if (fscanf(file, "%lf", a + i) == EOF) {
			printf("Недостаточно данных в файле\n");
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
	for (int i = 0; i < n*n; i++) a[i] = func(n, i/n, i - (i/n)*n);
	return 1;	
}

void nevyazka(double *a, double *b, double *x, int n){
	double *tmp = pro_m(a, x, n), na = 0, nb = 0;
	if (NULL == tmp) return;

	for (int j = 0; j < n; j++){
		printf("%lf\n", tmp[j]);
	    	na += fabs(tmp[j] - b[j]);
		nb += fabs(b[j]);
        }
	printf("nevyazka: %lf\n", na/nb);
	return;
}
