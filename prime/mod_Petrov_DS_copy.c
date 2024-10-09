#include <stdio.h>
#include <math.h>

int isPrime(long long a){
	if(2 == a) return 1;
	if(0 == a%2) return 0;
	for(long long i = 3; i * i < a+1; i += 2){
		if(0 == a%i) return 0;
	}
	return 1;
}

int main(){
	int count;
	long long n;
	printf("Enter a number: ");
	if(!(scanf("%lli", &n))){
		printf("Input error!\n");
		return -1;
	}

	if(n <= 0){
		printf("We don't do that here\n");
		return -1;
	}

	count = isPrime(n);
	printf("%i\n", count);
}
