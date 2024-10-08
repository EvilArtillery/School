#include <stdio.h>
#include <math.h>

int isPrime(int a){
	if(2 == a) return 1;
	if(0 == a%2) return 0;
	for(int i = 3; i * i < a+1; i += 2){
		if(0 == a%i) return 0;
	}
	return 1;
}

int main(){
	int n, count;
	printf("Enter a number: ");
	if(!(scanf("%i", &n))){
		printf("Input error!\n");
		return -1;
	}

	if(n <= 0){
		printf("We don't do that here\n");
		return -1;
	}

	for(count = 2; count < n+1; count++){
		if(isPrime(count)){
			printf("%i\n", count);
		}
	}
}
