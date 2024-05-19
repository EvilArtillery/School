#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
  int weight;
} mommy;

int compare_(void* _ptr1, void* _ptr2) {
  mommy* ptr1 = (mommy*)_ptr1;
  mommy* ptr2 = (mommy*)_ptr2;

  return ptr1->weight > ptr2->weight;
}

void swap_(void* _ptr1, void* _ptr2) {
  mommy* ptr1 = (mommy*)_ptr1;
  mommy* ptr2 = (mommy*)_ptr2;

  ptr1->weight = ptr1->weight + ptr2->weight;
  ptr2->weight = ptr1->weight - ptr2->weight;
  ptr1->weight = ptr1->weight - ptr2->weight;
}

void* shift_(void* _ptr, int n) {
  return (mommy*)_ptr + n;
}

int partition(void* array, int n, int (*compare)(void*, void*), void (*swap)(void*, void*), void* (*shift)(void*, int) ) {
  int i = 0;
  int j = n - 1;
  void* m = shift(array, rand()%n);
  while (1) {
    while ( compare(m, shift(array, i)) ) i++;
    while ( compare(shift(array, j), m) ) j--;
    if (i >= j) return j;
    
    if (m == shift(array, i) ) m = shift(array, j);
    else if (m == shift(array, j) ) m = shift(array, i);
    swap(shift(array, i++), shift(array, j--));
  }
  return 0;
}

void quicksort(void* array, int n, int (*compare)(void*, void*), void (*swap)(void*, void*), void* (*shift)(void*, int) ) {
  int p;
  while(1) {
    if (n<=1) return;
    if (n==2) {
      if ( compare(array, shift(array, 1) ) ) swap(array, shift(array, 1) );
      return;
    }
    p = partition(array, n, compare, swap, shift);
    if (p+1 < n/2.) {
      if (p > 0) quicksort(array, p+1, compare, swap, shift);
      array = shift(array, p + 1);
      n -= p + 1;
    }
    else {
      if (p+1 < n-1) quicksort( shift(array, p+1), n-p-1, compare, swap, shift);
      n = p + 1;
    }
  }  
}


int main() {
  srand(time(NULL)); // srand ha ha
  int n = 1000000;
  mommy* a = malloc(n*sizeof(*a));
  if (!a) return -1;
  for (int i=0; i<n; i++) {
    mommy t;
    t.weight = rand()%10;
    *(a + i) = t;
    //printf("%d ", t.weight);
  }
  printf("\n");
  quicksort(a, n, compare_, swap_, shift_);

  int c = 0;
  for (int i=0; i<n-1; i++) {
	  if( (int)(((double)i)/((double)n)*100)==c ) {
		  printf("%d%%\n", c);
		  c+=5;
	  }
	  if ((a+i)->weight > (a+i+1)->weight) printf("Error ");
	  //printf("%d\n", (a+i)->weight );
  }
  printf("Done. \n");

  free(a);
  return 0;
}






