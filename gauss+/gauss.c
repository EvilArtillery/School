#include<math.h>
#include"lib.h"


int solve(int n, double *a, double *b, double *x){
  double tmp;
  int i, j, I, k;
  for ( i = 0 ; i < n ; i++) {
    I = -1;
    for (j = i ; j < n; j++){
      if ( fabs (a[j*n + i]) > 1e-14 ) {
        I = j ;
        break;
      }
    }
//    for (k = I; k < n; k++){
//      if (a[k*n + i] > a[I*n + i]) I = k;
//    }
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
    for ( j = i + 1 ; j < n ; j ++) {
      tmp = a[j*n + i] / a[i*n + i];
      b[j] -= b[i]*tmp;
      for ( k = i + 1 ; k < n ; k++) {
        a[j*n + k] -= a[i*n + k]*tmp;
      }
    }
  }
  for ( i = n - 1 ; i >= 0 ; i -- ) {
    x[i] = b[i] / a[i*n + i];
    for ( j = 0 ; j < i ; j ++) {
      b[j] -= a[j*n + i]*x[i];
    }
  }
  return 1;
}
