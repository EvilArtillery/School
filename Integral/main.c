#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int main(){
  double a, b, delta;
  int n;

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

  if(1e-14 > (b - a - delta)){
    printf("\x1b[91mError! The whole interval has to be more than a minimal one!\x1b[0m\n");
    return 0;
  }

  

  return 1;
}
