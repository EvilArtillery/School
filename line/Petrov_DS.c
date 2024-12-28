#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct dot{
    double x, y;
} dot;


int main(int argc, char* argv[]){
    int n = 0;

    if(1 == argc){
        printf("\x1b[91m");
        printf("Error! Not enough arguments!");
        printf("\x1b[0m");
        printf("\n");
        return 0;
    }

    FILE* in = fopen(argv[1], "r");
    if(NULL == in){
        printf("\x1b[91m");
        printf("Couldn't open file\n");
        printf("\x1b[0m");
        return 0;
    }

    if(1 != fscanf(in, "%i", &n)){
        printf("\x1b[91mScanf error!\n\x1b[0m");
        return -1;
    }

    dot* list = malloc(n * sizeof(dot));

    for (int i = 0; i < n; i++){
        if(2 != fscanf(in, "%lf %lf", &((list + i)->x), &((list+i)->y))){
            printf("\x1b[91mScanf error!\n\x1b[0m");
            return -1;
        }
    }

    // for(int i = 0; i < n; i++) printf("%.2lf %.2lf\n", (list+i)->x, (list+i)->y);

    free(list);
    return 1;
}