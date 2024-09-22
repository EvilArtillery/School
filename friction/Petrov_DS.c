#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double speed0 = 0, angle0 = 0;

    printf("Enter the initial speed: ");
    if(1 != scanf("%lf", &speed0)){
        perror("Scanf failed");
        return -1;
    }

    if(speed0 <= 1e-14){
        printf("\x1b[31mInitial speed has to be more than 0!\x1b[0m\n");
        return 0;
    }

    printf("Enter the throw angle: ");
    if(1 != scanf("%lf", &angle0)){
        perror("Scanf failed");
        return -1;
    }

    if(angle0 <= 1e-14){
        printf("\x1b[31mThrow angle has to be more than 0!\x1b[0m\n");
        return 0;
    }
    if(angle0 > M_PI_2){
        printf("\x1b[31mThrow angle has to be less than pi/2!\x1b[0m\n");
        return 0;
    }
}