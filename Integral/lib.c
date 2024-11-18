#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lib.h"

double integral(double a, double b, double f(double), double f1, double f2){
  double result;
  double left = f1;
  double right = f2;
  if(isnan(f1)) left = f(a);
  if(isnan(f2)) right = f(b);
  result = left + right;
  result *= (b - a);
  result /= 2.;
  return result;
}