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

int divide(double a, double b, double f(double), double delta){
  double sum1, sumhalfs;
  double middle = (a + b) / 2.;

  if(delta > (middle - a)) return 0;

  double fa, fb, fmid;
  fa = f(a);
  fb = f(b);
  fmid = f(middle);

  sum1 = integral(a, b, f, fa, fb);
  sumhalfs = integral(a, middle, f, fa, fmid) + integral(middle, b, f, fmid, fb);

  if(1e-10 < fabs(sum1 - sumhalfs)){
    return 1;
  }

  return 0;
}

int unite(double a, double b, double c, double f(double)){
  double fa, fb, fc;
  fa = f(a);
  fb = f(b);
  fc = f(c);
  double sumab = integral(a, b, f, fa, fb);
  double sumbc = integral(b, c, f, fb, fc);
  double sumac = integral(a, c, f, fa, fc);

  if(fabs(sumab + sumbc - sumac) < 1e-10) return 1;
  return 0;
}