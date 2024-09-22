#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int friction_instance(double* x, double* y, double* speed_x, double* speed_y, double friction){
    
}

int main(){
    double speed0 = 0, angle0 = 0, friction = 0;

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

    printf("Enter your friction coefficient: ");
    if(1 != scanf("%lf", &friction)){
        perror("Scanf failed");
        return -1;
    }

    if(-1e-14 >= friction){
        printf("\x1b[31mFriction can't be less than 0!\x1b[0m\n");
        return 0;
    }

    double speedx = 0, speedy = 0, x = 0, y = 0;

    speedx = speed0 * cos(angle0);
    speedy = speed0 * sin(angle0);

    int n = 0;

    while(x > -1e-14){
        friction_instance(&x, &y, &speedx, &speedy, friction);
        n += 1;
    }
}