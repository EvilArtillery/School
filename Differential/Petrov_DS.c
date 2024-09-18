#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double oscillator_no_speed(double phi0, double dt, double l, double g){
    double phit = fabs(phi0);
    if(1e-14 > phit) return 0;
    double psit = 0;
    double w = -g/l;
    unsigned long long n = 0;

    double psit1, phit1;

    while(psit >= 0){
        phit1 = phit - (psit * dt);
        psit1 = psit - (w * sin(phit) * dt); /*
        printf("Angle: %lf\n", phit1);
        printf("Speed: %lf\n", psit1); */

        n++;
        psit = psit1;
        phit = phit1;
    }

    n += (n + 1);
    return(n * dt);
}

double speed_to_no_speed(double phi0, double psi0, double dt, double l, double g){
    double energy, height, angle, speed;

    speed = psi0 * l;

    height = l * (1 - cos(phi0));
    //e = (v^2)/2 + gh
    energy = speed * speed / 2;
    energy += g * height;

    //e = gh = gl(1 - cos(phi))
    height = energy / g;
    height /= l;

    height -= 1;
    height *= -1;

    if(fabs(height) > 1){
        printf("\x1b[31mToo much energy!\x1b[0m\n");
        return 0;
    }
    angle = acos(height);
    
    return(oscillator_no_speed(angle, dt, l, g) - dt);
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
    if(fabs(phi0) - M_PI > -1e-14){
        printf("\x1b[31mError: too big starting angle\n\x1b[0m");
        return 0;
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
    printf("Enter a time step for calculating (in seconds): ");
    if(1 != scanf("%lf", &dt)){
        perror("Scanf failed");
        return -1;
    }

    if(0 >= dt){
        printf("\x1b[31mError: step has to be more than 0\n\x1b[0m");
        return 0;
    }

    double result;
    if(0 == psi0) result = oscillator_no_speed(phi0, dt, l, g);
    else result = speed_to_no_speed(phi0, psi0, dt, l, g);

    if(0 == result) return 0;
    printf("%lf\n", result);
    return(1);
}
