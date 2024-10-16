#include <stdio.h>
#include <math.h>

int isPrime(int a){
	if(2 == a) return 1;
	int i;
	double b = a, c;
	c = sqrt(b);
	for(i = 2; i < c + 1; i++){
		if(a/i == b/i){
			return 0;
		}
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
