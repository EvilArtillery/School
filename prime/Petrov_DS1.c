#include <stdio.h>
#include <math.h>

int isPrime(int a){
	int i;
	double b = a, c;
	c = sqrt(b);
	for(i = 2; i < c; i++){
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
	for(count = 2; count < n+1; count++){
		if(isPrime(count)){
			printf("%i\n", count);
		}
	}
}
