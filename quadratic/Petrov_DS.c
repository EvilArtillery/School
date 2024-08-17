#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	double arg[3];

	for(int i = 0; i < 3; i++){
		printf("Enter the argument number %i: ", i+1);
		if(! scanf("%lf", arg + i)){
			perror("Input error");
			return -1;
		}
	}

	if(!arg[0]){
		printf("Not a quadratic equation\n");
		return 0;
	}

	double d;

	d = (arg[1] * arg[1]) - (4 * arg[0] * arg[2]);

	if(d < -1e-14){
		printf("Discriminant is less than 0\n");
		return 0;
	}

	if(fabs(d) <= 1e-14){
		printf("Discriminant is 0.\n");
		printf("The only answer is %lf\n", sqrt(arg[1]));
		return 1;
	}

	d = sqrt(d);
	double answer1 = -(arg[1] + d)/(2 * arg[0]);
	double answer2 = (d - arg[1])/(2 * arg[0]);

	printf("Discriminant is more than 0.\n");
	printf("The answers are %lf and %lf\n", answer1, answer2);
	return 1;
}
