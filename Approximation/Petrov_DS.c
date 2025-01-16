#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct dot {
    double x;
    double y;
} dot;

double cmod(dot a){
	double b;
	b = a.x * a.x + (a.y * a.y);
	return sqrt(b);
}

double argc(dot a){
	double ar = 0;
	double mod = cmod(a);
	if(a.y > 1e-14) ar = acos(a.x/mod);
	else ar = - acos(a.x/mod);
	return ar;
}

dot sqrtc(dot a){
	if(fabs(cmod(a) < 1e-10)) return (dot){0, 0};
	dot b;
	double r = cmod(a), fi = argc(a);
	fi /= 2.;
	r = sqrt(r);
	b.x = r * cos(fi);
	b.y = r * sin(fi);
	return b;
}


void main(){
    int n;
    if(1 != scanf("%i", &n)){
        printf("\x1b[91mError! Scanf failed!\x1b[0m\n");
        return;
    }
    if(2 > n){
        printf("You can't approximate less than two points!\n");
        return;
    }

    dot* array = malloc(n * sizeof(dot));
    if(array == NULL){
        perror("Malloc failed");
        return;
    }

    for(int i = 0; i < n; i++){
        if(2 != scanf("%lf %lf", &(array+i)->x, &(array+i)->y)){
            printf("\x1b[91mError! Scanf failed!\x1b[0m\n");
            free(array);
            return;
        }
    }

    dot centroid = {0, 0};

    for(int i = 0; i < n; i++){
        centroid.x += array[i].x;
        centroid.y += array[i].y;
    }

    centroid.x /= n;
    centroid.y /= n;

    dot S = {0, 0};
    double xi = 0, yi = 0;

    for(int i = 0; i < n; i++){
        xi = centroid.x - array[i].x;
        yi = centroid.y - array[i].y;
        xi *= xi;
        yi *= yi;
        S.x += xi;
        S.y += yi;
    }

    // S = sqrtc(S);

    double answera, answerb, answerc;

    answera = -S.y;
    answerb = S.x;
    answerc = centroid.x * answera + centroid.y * answerb;
    answerc *= -1;

    printf("Answer:\n");
    printf("\x1b[92m");
    printf("%lfx + %lfy + %lf = 0", answera, answerb, answerc);
    printf("\n\x1b[0m");

    free(array);
    return;
}