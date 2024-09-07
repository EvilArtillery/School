#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double oscillator_no_speed(double phi0, double dt, double l, double g){
    double phit = phi0;
    double psit = 0;
    double w = g/l;

    double psit1, phit1;

    while(psit >= 0){
            phit1 = phit + (psit * dt);
            psit1 = psit - 
    }
}

int main(){
    double l = -1, phi = -1, psi = 0;
    double g = 9.80665;

    
}