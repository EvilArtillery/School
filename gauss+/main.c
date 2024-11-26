#include<stdio.h>
#include<stdlib.h>
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
	
	if (solve(n, a, b, x)< 0) {
		for (int i = 0; i < n; i++) printf("%lf ", a[i*n]);
		printf("%lf \n", b[0]);
		printf("Error in solve\n");
		return -1;
	}
	for(int i = 0; i < m; i++) printf("%lf\n", x[i]);
	nevyazka(a, b, x, n);
	free(a);
	free(b);
	free(x);
	return 1;
}

