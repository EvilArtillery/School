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

int divide(double a, double b, double f(double), double delta){
  double sum1, sumhalfs;
  double middle = (a + b) / 2.;

  sum1 = integral(a, b, f);
  if(delta > (middle - a)) return 0;

  sumhalfs = integral(a, middle, f) + integral(middle, b, f);

  if(1e-12 < fabs(sum1 - sumhalfs)){
    return 1;
  }

  return 0;
}

int unite(double a, double b, double c, double f(double)){
  double sumab = integral(a, b, f);
  double sumbc = integral(b, c, f);
  double sumac = integral(a, c, f);

  if(fabs(sumab + sumbc - sumac) < 1e-12) return 1;
  return 0;
}