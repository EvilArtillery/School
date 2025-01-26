#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"


int solve(int n, double *a, double *b, double *x, double minimal){
  double tmp;
  int i, j, I, k;
  double max;

  clock_t begin = clock();

  for ( i = 0 ; i < n ; i++) {
    I = -1;
    max = minimal * 1e-14;
    // printf("\x1b[91m%i\x1b[0m\n", i);
    for (j = i ; j < n; j++){
      // printf("\x1b[92m%3.2lf \x1b[0m", a[j*n + i]);
      if ( fabs (a[j*n + i]) > max ) {
        I = j ;
        max = fabs (a[j*n + i]);
      }
    }

    if ( I == -1 ) {
      printf( "Error!\n" ) ;
      return -1 ;
    }

    if ( I != i ) {
      tmp = b[i] ;
      b[i] = b[I] ;
      b[I] = tmp ;
      for ( j = i ; j < n ; j ++) {
        tmp = a[i*n + j];
        a[i*n + j] = a[I*n + j];
        a[I*n + j] = tmp;
      }
    }

    // print_matrix(a, b, n);

    for ( j = i + 1 ; j < n ; j ++) {
      tmp = a[j*n + i] / a[i*n + i];
      b[j] -= b[i]*tmp;
      for ( k = i ; k < n ; k++) {
        a[j*n + k] -= a[i*n + k] * tmp;
        if(1e-14 > fabs(a[j*n + k])) a[j*n + k] = 0;
      }
    }

    // print_matrix(a, b, n);
  }

  for ( i = n - 1 ; i >= 0 ; i -- ) {
    x[i] = b[i] / a[i*n + i];
    for ( j = 0 ; j < i ; j ++) {
      b[j] -= a[j*n + i]*x[i];
    }
  }

  if(-1 == begin) printf("\x1b[31mRunning time is not available!\x1b[0m");
  else {
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\x1b[32mCPU time spent solving: %lf\n\x1b[0m", time_spent);
  }

  return 1;
}
