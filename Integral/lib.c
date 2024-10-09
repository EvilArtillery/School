#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib.h"

double integral(double a, double b, double* f(double)){
  double result;
  result = f(a) + f(b);
  result *= (b - a);
  result /= 2.;
  return result;
}

double divide(double a, double b, double* f(double)){
  return 0;
}