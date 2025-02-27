#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct dot {
    double x;
    double y;
} dot;


int main(int argc, char *argv[]){
    int n;

    if(2 != argc){
        printf("\x1b[91mError! Incorrect number of arguments!\x1b[0m\n");
        return -1;
    }

    FILE* in = fopen(argv[1], "r");
    if(NULL == in){
		perror("File opening error"); //That's error output from stdlib.h
		return -1;
	}

    if(1 != fscanf(in, "%i", &n)){
        printf("\x1b[91mError! Scanf failed!\x1b[0m\n");
        return -1;
    }
    if(2 > n){
        printf("You can't approximate less than two points!\n");
        return 0;
    }

    dot* array = malloc(n * sizeof(dot));
    if(array == NULL){
        perror("Malloc failed");
        return -1;
    }

    for(int i = 0; i < n; i++){
        if(2 != fscanf(in, "%lf %lf", &(array+i)->x, &(array+i)->y)){
            printf("\x1b[91mError! Scanf failed!\x1b[0m\n");
            free(array);
            return -1;
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

    double answera, answerb, answerc;

    answera = -S.y;
    answerb = S.x;
    answerc = centroid.x * answera + centroid.y * answerb;
    answerc *= -1;

    printf("Answer:\n");
    printf("\x1b[92m");
    printf("%.3lfx + %.3lfy + %.3lf = 0", answera, answerb, answerc);
    printf("\n\x1b[0m");

    free(array);
    return 1;
}