#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void friction_instance(double* x, double* speed_x, double friction, double dt){
    double x1, speed_x1;

    x1 = *x + (*speed_x * dt);
    speed_x1 = *speed_x - (*speed_x * friction * dt);

    *x = x1;
    *speed_x = speed_x1;
}

#ifdef SLON
void friction_instance_height(double* x, double* speed_x, double friction, double dt){
    double x1, speed_x1, frict;

    x1 = *x + (*speed_x * dt);
    frict = *speed_x * friction * dt * pow(M_E, -*x);
    speed_x1 = *speed_x - frict;

    *x = x1;
    *speed_x = speed_x1;
}
#endif //SLON


int main(){
    double speed0 = 0, angle0 = 0, friction = 0, dt = 0;

    printf("Enter the initial speed: ");
    if(1 != scanf("%lf", &speed0)){
        perror("Scanf failed");
        return -1;
    }

    if(speed0 <= 1e-14){
        printf("\x1b[91mInitial speed has to be more than 0!\x1b[0m\n");
        return 0;
    }

    printf("Enter the throw angle: ");
    if(1 != scanf("%lf", &angle0)){
        perror("Scanf failed");
        return -1;
    }

    if(angle0 <= 1e-14){
        printf("\x1b[91mThrow angle has to be more than 0!\x1b[0m\n");
        return 0;
    }
    if(angle0 > M_PI_2){
        printf("\x1b[91mThrow angle has to be less than pi/2!\x1b[0m\n");
        return 0;
    }

    printf("Enter your friction coefficient: ");
    if(1 != scanf("%lf", &friction)){
        perror("Scanf failed");
        return -1;
    }
/*
    if(-1e-14 >= friction){
        printf("\x1b[91mFriction can't be less than 0!\x1b[0m\n");
        return 0;
    }
    if(1 <= friction){
        printf("\x1b[91mFriction coefficient has to be less than 1!\x1b[0m\n");
        return 0;
    }
*/
    printf("Enter a time period for calculating (in seconds, usually 1e-5): ");
    if(1 != scanf("%lf", &dt)){
        perror("Scanf failed");
        return -1;
    }

    if(1e-10 > dt){
        printf("\x1b[91mToo small or negative time period!\x1b[0m\n");
        return 0;
    }

    double speedx = 0, speedy = 0, x = 0, y = 0;

    speedx = speed0 * cos(angle0);
    speedy = speed0 * sin(angle0);

    int n = 0;

    while(speedy > -1e-14){
        friction_instance(&x, &speedx, friction, dt);
        speedy -= 9.8 * dt;
        #ifdef SLON
        friction_instance_height(&y, &speedy, friction, dt);
        #endif //SLON
        #ifndef SLON
        friction_instance(&y, &speedy, friction, dt);
        #endif //NO SLON
        n += 1;
    }
    printf("Time moved upwards: \x1b[92;1m%lf\x1b[0m\n", dt * n);
    printf("Maximum height: \x1b[92;1m%lf\x1b[0m\n", y);
    while(y > -1e-14){
        friction_instance(&x, &speedx, friction, dt);
        speedy -= 9.8 * dt;
        #ifdef SLON
        friction_instance_height(&y, &speedy, friction, dt);
        #endif //SLON
        #ifndef SLON
        friction_instance(&y, &speedy, friction, dt);
        #endif //NO SLON
        n += 1;
    }

    printf("Time in air: \x1b[92;1m%lf\x1b[0m\n", dt * n);
    return 1;
}