#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double oscillator_no_speed(double phi0, double dt, double l, double g){
    double phit = phi0;
    double psit = 0;
    double w = g/l;
    int n = 0;

    double psit1, phit1;

    while(psit >= 0){
        phit1 = phit + (psit * dt);
        psit1 = psit - (w * sin(phit) * dt);

        n++;
        psit = psit1;
        phit = phit1;
    }

    n += (n + 1);
    return(n * dt);
}

double speed_to_no_speed(double phi0, double psi0, double dt, double l, double g){
    double phit = phi0;
    double psit = psi0;
    double w = g/l;

    double phit1, psit1;

    while(psit/psi0 > 0){
        phit1 = phit + (psit * dt);
        psit1 = psit + (w * sin(phit) * dt);

        psit = psit1;
        phit = phit1;
    }

    return(oscillator_no_speed(phit, dt, l, g) - dt);
}

int main(){
    double l = -1;
    double g = 9.80665;

    printf("Enter the length of your pendulum: ");
    if(1 != scanf("%lf", &l)){
        perror("Scanf failed");
        return -1;
    }

    if(0 >= l){
        printf("\x1b[31mError: length has to be more than 0\n\x1b[0m");
        return 0;
    }

    double phi0 = 0;
    printf("Enter the starting angle of your pendulum: ");
    if(1 != scanf("%lf", &phi0)){
        perror("Scanf failed");
        return -1;
    }

    double psi0 = 0;
    printf("Enter the starting speed of your pendulum: ");
    if(1 != scanf("%lf", &psi0)){
        perror("Scanf failed");
        return -1;
    }

    if(0 == psi0 && 0 == phi0){
        printf("\x1b[31mError: no movement\n\x1b[0m");
        return 0;
    }

    double dt = 0;
    printf("Enter an acceptable margin for errors: ");
    if(1 != scanf("%lf", &dt)){
        perror("Scanf failed");
        return -1;
    }

    if(0 >= dt){
        printf("\x1b[31mError: margin has to be more than 0\n\x1b[0m");
        return 0;
    }

    double result;
    if(0 == psi0) result = oscillator_no_speed(phi0, dt, l, g);
    else result = speed_to_no_speed(phi0, psi0, dt, l, g);

    printf("%lf", result);
    return(1);
}
