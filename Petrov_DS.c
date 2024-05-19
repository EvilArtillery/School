#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int i, n;
	double s = 0, avg, disp, e = 0, tmp;
	char input[16];

	printf("Enter the number of elements: ");
	if(! scanf("%16s", input)){
		printf("Input error!\n");
		return -1;
	}

	if(1 != sscanf(input, "%i", &n)){
		printf("Input error!\n");
		return -1;
	}

	if(0 >= n){
		printf("Hell r u doin'?\n");
		return 1;
	}

	double* a = malloc(n * sizeof(*a));
	if(NULL == a){
		printf("Memory allocation error!\n");
		return -1;
	}

	for(i = 0; i < n; i++){
		printf("Enter element number %i: ", i+1);
		if(! scanf("%16s", input)){
			printf("Input error!\n");
			return -1;
		}
		if(! sscanf(input, "%lf", a+i)){	
			printf("Input error!\n");
			free(a);
			return -1;
		}
	}


	for(i = 0; i < n; i++){
		s += *(a+i);
	}

	avg = s/n;
	printf("Average is %lf\n", avg);

	//D[X] = E[(pow(X - E[X], 2))]
	for(i = 0; i < n; i++){
		tmp = pow(*(a+i) - avg, 2);
		e += tmp;
	}
	disp = e/n;
	printf("Dispersion is %lf\n", disp);
	

	free(a);
}
