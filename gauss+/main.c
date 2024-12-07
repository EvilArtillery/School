#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lib.h"

int main(int argc,char *argv[]){
	if (argc > 5 || argc < 4){
		printf("Некорректный ввод данных\n");
	  	return -1;
	}

	int n, m, k;

 	if (sscanf(argv[1], "%d", &n) != 1){
		printf("Error in n\n");
		return -1;
	}
	
	if (sscanf(argv[2], "%d", &m) != 1){
		printf("Error in m\n");
		return -1;
	}

	if(m > n){
		printf("\x1b[91mError! You can't set m more than n!\x1b[0m\n");
		return 0;
	}
	
	if (sscanf(argv[3], "%d", &k) != 1){
		printf("Error in k\n");
		return -1;	
	}
	
	double *a = malloc(n*n*sizeof(*a));
	if (a == NULL){
		printf("Error in a\n");
		return -1;
	}
	
	if (k == 0){
        if (argc == 4){
			printf("Error in k\n");
		    free(a);
	        return -1;
		}
	    if (get_matrix(argv[4], a, n) < 0){
			printf("Error in file\n");
			free(a);
	       	return -1;
		}
	}
	
	else {
		if (calculate_matrix(k, a, n) < 0){
			free(a);       
			printf("Error in calc\n");
			return -1;
		}
	}
	
	double *b = malloc(n*sizeof(*b)), *x = malloc(n*sizeof(*x));
	if (NULL == b) {
		printf("Error in b\n");
		return -1;
	}
	if (NULL == x) {
        	printf("Error in x\n");
        	return -1;
    	}
	fill_B(b, a, n);
	double* b_copy = malloc(n * sizeof(double));
	memcpy(b_copy, b, (n * sizeof(double)));
	double* a_copy = malloc(n * n * sizeof(double));
	memcpy(a_copy, a, (n * n * sizeof(double)));

	
//	print_matrix(a,b,n);
	if (solve(n, a_copy, b_copy, x)< 0) {
		for (int i = 0; i < n; i++) printf("%lf ", a[i*n]);
		printf("%lf \n", b[0]);
		printf("Error in solve\n");
		return -1;
	}
	for(int i = 0; i < m; i++) printf("x[%d] =  %lf\n", i,  x[i]);
	printf("\v");
	nevyazka(a, b, x, n);
	free(a);
	free(a_copy);
	free(b);
	free(b_copy);
	free(x);
	return 1;
}

