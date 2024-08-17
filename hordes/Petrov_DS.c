#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES

int sign(double x){
	if(x < 0) return -1;
	return 1;

}

double horde(double a, double b, double d, double f(double x)) {
	double x0 = a;
	double x1 = b;
	if((fabs(f(x0) - f(x1)) < 1e-14) && (fabs(f(x0)) > 1e-14)){
		perror("No roots");
		return 0;
	}
	while(fabs(x0 - x1) > d) {
		x0 = x0 - (x1 - x0) * f(x0) / (f(x1) - f(x0));
		x1 = x1 - (x0 - x1) * f(x1) / (f(x0) - f(x1));
	}
	return x1;
}

double bisection(double a, double b, double delta, double f(double x)){
	double x0 = a;
	double x1 = b;
	double x2 = (a + b)/2.;
	while(fabs(x0 - x1) > delta){
		if(fabs(f(x2)) < delta) return x2;
		if(sign(f(x0)) == sign(f(x1))){
			perror("No roots at specified location");
			return 0;
		}
		if(sign(f(x2)) == sign(f(x0))){
			x0 = x2;
		}
		if(sign(f(x2)) == sign(f(x1))){
			x1 = x2;
		}
		x2 = (x0 + x1)/2.;
	}
	return x2;
}

int main(){
	double n2;
	int n, i;
	double temp = 0;

	printf("Enter the highest power of x in your function: ");
	if(! scanf("%lf", &n2)){
		perror("scanf failed");
		return -1;
	}

	if(n2 < 1){
		perror("Not a function");
	       	return -1;
	}

	n = n2 + 1;
	double* args = (double*) malloc(n * sizeof(double));

	if(NULL == args){
		perror("Memory allocation error");
		return -2;
	}

	for(i = 0; i < n; i++){
		printf("Enter the argument of x^%i: ", n-i-1);
		if(! scanf("%lf", args+i)){
			perror("scanf failed");
			return -1;
		}
	}
	
	double f(double x){
		double result = 0;
		for(i = 0; i < n; i++){
			temp = pow(x, n-i-1) * args[i];
			result += temp;
		}
		return result;
	}

/*
	double f(double x){
		double result = 0;
		result = pow(x, 2) + sin(x);
		return result;
	}
*/
	printf("Choose method: Horde([0]), Bisection(1)\n");
	if(! scanf("%lf", &temp)){
		perror("scanf failed");
		return -1;
	}

	double x0 = 0, x1 = 0, eps = 1;
	printf("Enter x0: ");
	if(! scanf("%lf", &x0)){
		perror("scanf failed");
		return -1;
	}
	printf("Enter x1: ");
	if(! scanf("%lf", &x1)){
		perror("scanf failed");
		return -1;
	}
	printf("Enter Delta: ");
	if(! scanf("%lf", &eps)){
		perror("scanf failed");
		return -1;
	}

	if(1 == temp) printf("%.2lf\n", bisection(x0, x1, eps, f));
	else printf("%.2lf\n", horde(x0, x1, eps, f));
	

	free(args);
	return 1;
}
