#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lib.h"

#define FREE \
{\
if(a) free(a);\
if(b) free(b);\
if(x) free(x);\
}

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
	if(1 > n){
		printf("\x1b[91mError! The smallest possible matrix is 1 by 1!\x1b[0m\n");
		return 0;
	}
	
	if (sscanf(argv[2], "%d", &m) != 1){
		printf("Error in m\n");
		return -1;
	}

	if(m > n){
		printf("\x1b[93mYou can't set m more than n!\x1b[0m\n");
		m = n;
	}
	
	if (sscanf(argv[3], "%d", &k) != 1){
		printf("Error in k\n");
		return -1;	
	}
	
	double *a, *b, *x;
	a = malloc(n*n*sizeof(*a));
	b = malloc(n*sizeof(*b));
	x = malloc(n*sizeof(double));
	if (!a || !b || !x) {
       	printf("Error in allocating memory\n");
		FREE;
       	return -1;
    }
	
	if (k == 0){
        if (argc == 4){
			printf("Error in k\n");
			FREE;
	        return -1;
		}
	    if (get_matrix(argv[4], a, n) < 0){
			printf("Error in file\n");
			FREE;
	       	return -1;
		}
	}
	
	else {
		if (calculate_matrix(k, a, n) < 0){
			FREE;
			printf("Error in calc\n");
			return -1;
		}
	}

	fill_B(b, a, n);

	// print_matrix(a, b, n);

	//finding a norm
	double min = a[0], min1;
	for (int i = 0; i < n; i++){
		min1 = 0;
		for(int j = 0; j <n; j++){
			min1 += a[i*n + j];
		}
		if(min1 < min) min = min1;
	}

	if (solve(n, a, b, x, min)< 0) {
		printf("Error in solve\n");
		FREE;
		return -1;
	}
	print_matrix_part(a, b, n, m);
	printf("\v");

	//returning a to the original state
	if(0 == k){
		if(0 > get_matrix(argv[4], a, n)){
			printf("Error in file\n");
			FREE;
	       	return -1;
		}
	}
	else {
		if (calculate_matrix(k, a, n) < 0){
			FREE;
			printf("Error in calc\n");
			return -1;
		}
	}

	//returning b to the original state
	fill_B(b, a, n);

	difference(x, n);
	nevyazka(a, b, x, n);
	FREE;
	return 1;
}

