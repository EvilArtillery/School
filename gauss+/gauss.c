#include<math.h>
#include <string.h>
#include <stdlib.h>
#include"lib.h"


int solve(int n, double *a, double *b, double *x){
  double tmp;
  int i, j, I, k;
  double max;

  double* bcopy = malloc(n * sizeof(double));
  memcpy(bcopy, b, (n * sizeof(double)));

  for ( i = 0 ; i < n ; i++) {
    I = -1;
    max = 1e-14;
    printf("\x1b[91m%i\x1b[0m\n", i);
    for (j = i ; j < n; j++){
      printf("\x1b[92m%lf\x1b[0m\n", a[j*n + i]);
      if ( fabs (a[j*n + i]) > max ) {
        I = j ;
      }
    }
    printf("\x1b[96m%lf\x1b[0m\n\n", bcopy[i]);

    if ( I == -1 ) {
      printf( "Error!\n" ) ;
      return -1 ;
    }

    if ( I != i ) {
      tmp = bcopy[i] ;
      bcopy[i] = bcopy[I] ;
      bcopy[I] = tmp ;
      for ( j = i ; j < n ; j ++) {
        tmp = a[i*n + j];
        a[i*n + j] = a[I*n + j];
        a[I*n + j] = tmp;
      }
    }

    for ( j = i + 1 ; j < n ; j ++) {
      tmp = a[j*n + i] / a[i*n + i];
      bcopy[j] -= bcopy[i]*tmp;
      for ( k = i + 1 ; k < n ; k++) {
        a[j*n + k] -= a[i*n + k]*tmp;
      }
    }
  }

  for ( i = n - 1 ; i >= 0 ; i -- ) {
    x[i] = bcopy[i] / a[i*n + i];
    for ( j = 0 ; j < i ; j ++) {
      bcopy[j] -= a[j*n + i]*x[i];
    }
  }

  free(bcopy);
  return 1;
}
