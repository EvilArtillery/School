#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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

  double result = 0;

  double length = (b - a) / 100.;
  double x1 = a;
  double I1, I2;
  double fx1, fx2, fx15;
  fx1 = function(x1);

  time_t time1 = time(NULL);

  while(x1 < b){
    fx2 = function(x1 + length);
    fx15 = function(x1 + (length * 0.5));

    I1 = integral(x1, x1 + length, function, fx1, fx2);
    I2 = integral(x1, x1 + (length * 0.5), function, fx1, fx15) + integral(x1 + (length * 0.5), x1 + length, function, fx15, fx2);

    if(1e-12 < fabs(I1 - I2)){
      if(delta < (length * 0.5)){
        length *= 0.5;
        continue;
      }
    }
    else if(1e-13 > fabs(I1 - I2)){
      length *= 2;
      continue;
    }

    result += I1;
    x1 += length;
    fx1 = fx2;
//    printf("Step, l=%lf\n", length);
    
  }

  time_t time2 = time(NULL);


  printf("\x1b[92m%lf\x1b[0m\n", result);
  printf("Time worked: \x1b[32m%.3lf\x1b[0m seconds\n", (double)(time2 - time1));

  return 1;
}
