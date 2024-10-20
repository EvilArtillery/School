#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "lib.h"

double function(double x){
  return x * x;
}

int main(){
  double a, b, delta;

  printf("Enter the left limit of your interval: ");
  if(1 != scanf("%lf", &a)){
    perror("Scanf failed");
    return -1;
  }

  printf("Enter the right limit of your interval: ");
  if(1 != scanf("%lf", &b)){
    perror("Scanf failed");
    return -1;
  }

  if(1e-14 > (b-a)){
    printf("\x1b[91mError! The right limit has to be more than left limit!\x1b[0m\n");
    return 0;
  }

  printf("Enter the minimal counting interval: ");
  if(1 != scanf("%lf", &delta)){
    perror("Scanf failed");
    return -1;
  }
  if(1e-14 > delta){
    printf("\x1b[91mError! The minimal interval has to be more than zero!\x1b[0m\n");
    return 0;
  }

  if(1e-14 > (b - a - delta)){
    printf("\x1b[91mError! The whole interval has to be more than a minimal one!\x1b[0m\n");
    return 0;
  }

  printf("\x1b[92m%lf\x1b[0m\n", divide(a, b, function, delta));

  return 1;
}
