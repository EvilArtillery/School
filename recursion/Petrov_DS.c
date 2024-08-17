#include <stdio.h>
#include <math.h>


int Factorial(int a){
	if(a < 2) return 1;
	return (Factorial(a-1) * a);
}

int PowFact(int a){
	if(a < 2) return 1;
	return (pow(a, PowFact(a-1)));
}

int Fib(int a){
	if(a < 3) return 1;
	return (Fib(a-1) + Fib(a-2));
}


int main(){
	int n, a;
	printf("Enter a function number (1 - factorial, 2 - power factorial, 3 - Fibonacci numbers): ");
	if(! scanf("%i", &n)){
		printf("Input error!\n");
		return -1;
	}
	printf("Enter an argument for chosen function: ");
	if(! scanf("%i", &a)){
		printf("Input error!\n");
		return -1;
	}

	if(1 == n){
		printf("Factorial of %i equals to %i\n", a, Factorial(a));
		return 1;
	}
	if(2 == n){
		printf("Power factorial of %i equals to %i\n", a, PowFact(a));
		return 1;
	}
	if(3 == n){
		printf("Fibonacci number number %i is %i\n", a, Fib(a));
		return 1;
	}
	printf("Sorry, that's unacceptable argument number 1\n");
	return 0;
}
