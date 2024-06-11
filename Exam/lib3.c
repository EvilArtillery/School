#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_levenstein_distance (const char *str1, const char *str2, int *D)
{
  if (!str1 || !str2 || !D) return -1;
  int length1 = strlen(str1), length2 = strlen(str2);
  if(length1 > length2){
    int temp = length1;
    length1 = length2;
    length2 = temp;
  }

  for (int i = 0; i < length1 + 1; i++){
    for (int j = 0; j < length2 + 1; j ++){
      D[i + j * length1] = 0;
      if(0 == i && j > 0) D[(j-1) * length1] = str2[j];
      if(0 == j && i > 0) D[i-1] = str1[i];
    }
  }

  int subCost = 0;
  for (int i = 1; i < length1 + 1; i++){
    for (int j = 1; j < length2 + 1; j++){
      subCost = 0;
      if(str1[i-1] == str2[j-1]) subCost = 1;


      int lev1 = D[i-1 + j * length1] + 1;
      int lev2 = D[i + (j-1) * length1] + 1;
      int lev3 = D[i-1 + (j-1) * length1] + subCost;
      int levmin = lev1;
      if(lev2 < levmin) levmin = lev2;
      if(lev3 < levmin) levmin = lev3;
      D[i + j * length1] = levmin;
    }
  }
  return D[(length1+1) * (length2+1)];
}
