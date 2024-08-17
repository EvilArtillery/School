#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	double a[3][3], b[3];

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			printf("Enter the argument number %i in line %i: ", j+1, i+1);
			if(! scanf("%lf", &a[i][j])){
				perror("Input error");
				return -1;
			}
		}
		printf("Enter the result of equation number %i: ", i+1);
		if(! scanf("%lf", &b[i])){
			perror("Input error");
			return -1;
		}
	}

	int step, mark, i, j;
	double tmp;
	//SOLVING
	for(step = 0; step < 2; step++){	
		mark = -1;
		tmp = 0;
		for(i = step; i < 3; i++){
			if(fabs(a[i][step]) > 1e-14){
				mark = i;
				break;
			}
		}

		if(-1 == mark){
			printf("Error!\n");
		}

		if(0 != mark){
			for(i = step; i < 3; i++){
				tmp = a[step][i];
				a[step][i] = a[mark][i];
				a[mark][i] = tmp;
			}
			tmp = b[step];
			b[step] = b[mark];
			b[mark] = tmp;
		}

		for(i = step+1; i < 3; i++){
			tmp = a[i][step] / a[step][step];
			for(j = step; j < 3; j++){
				a[i][j] -= tmp * a[step][j];
			}
			b[i] -= tmp * b[step];
		}

		//At this moment, we have a subsystem.
	}

	//Actually ANSWER
	double x[3];
	int line;

	for(step = 0; step < 3; step++){
		line = 2 - step;
		x[line] = b[line] / a[line][line];
		for(i = 0; i < line; i++){
			b[i] -= a[i][line] * x[line];
		}
	}

	printf("The answers are %lf, %lf, and %lf\n", x[0], x[1], x[2]);
	return 1;
}

