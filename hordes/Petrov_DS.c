#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double bisec(double a, double b, double error, double (*func)(double)) { //метод деления отрезка пополам(бисекции)
	double c;
	if (fabs(func(a)) < (1e-14 + error)) return a;
	if (fabs(func(b)) < (1e-14 + error)) return b;
	if (func(a) * func(b) > 1e-14) return -1;
	c = (a + b) * 0.5;
	if (func(a) * func(c) < 0) b = c;
	else a = c;
	return bisec(a,b,error,func);
}

double secant(double a, double b, double error, double (*func)(double)){
	if (fabs(func(a)) < (1e-14 + error)) return a;
	if (fabs(func(b)) < (1e-14 + error)) return b;
	if (fabs(a - b) < error) return a;
	double c;
	c = a - (func(a) * (b - a) / (func(b) - func(a)));
	return secant(b, c, error, func);
}

double f1 (double x){
	return pow(x, 3) - 2 * pow(x, 2) + 3 * x - 4;
}

double f2 (double x){
	return exp(x) - 152 * pow(x, 2) + 34 * x;
}

double f3 (double x){
	return exp(x) - M_PI;
}

int main(){
	int selected1, selected2;
	double a, b, error;
	double answer;

	printf("Functions:\n1. x^3 - 2 x^2 + 3x - 4\n2. exp(x) - 152 x^2 + 34x\n3. cbrt(x + 15) - 4\nChoose function from the list above: ");
	if(1 != scanf("%i", &selected1)){
		perror("Scanf failed");
		return -1;
	}

	printf("Methods:\n1. Bisection method\n2. Secant method\nChoose method from the list above: ");
	if(1 != scanf("%i", &selected2)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter one of the end points of your interval: ");
	if(1 != scanf("%lf", &a)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter the other end point of your interval: ");
	if(1 != scanf("%lf", &b)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter acceptable margin: ");
	if(1 != scanf("%lf", &error)){
		perror("Scanf failed");
		return -1;
	}

	selected1 += selected2 * 3;
	selected1 -= 3;
	if (1 == selected1) answer = bisec(a, b, error, f1);
	else if (2 == selected1) answer = bisec(a, b, error, f2);
	else if (3 == selected1) answer = bisec(a, b, error, f3);
	else if (4 == selected1) answer = secant(a, b, error, f1);
	else if (5 == selected1) answer = secant(a, b, error, f2);
	else if (6 == selected1) answer = secant(a, b, error, f3);
	else{
		printf("Error! Unknown function/method!\n");
		return 0;
	}

	printf("Answer is \x1b[31m%lf\x1b[0m\n", answer);
	return 1;
}
