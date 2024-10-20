#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib.h"

double integral(double a, double b, double f(double)){
  double result;
  result = f(a) + f(b);
  result *= (b - a);
  result /= 2.;
  return result;
}

double divide(double a, double b, double f(double), double delta){
  double sum1, sumhalfs;
  double middle = (a + b) / 2.;

  sum1 = integral(a, b, f);
  if(delta > (middle - a)) return sum1;

  sumhalfs = integral(a, middle, f) + integral(middle, b, f);

  if(delta > 10 * fabs(sum1 - sumhalfs)){
    double result = divide(a, middle, f, delta) + divide(middle, b, f, delta);
    return result;
  }

  return sum1;
}