#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double calculate_identity (const char *str1, const char *str2)
{
  if (!str1 || !str2) return -1.;
  double exact_chars = 0;
  int length1 = strlen(str1), length2 = strlen(str2);
  if(length1 > length2){
    int temp = length1;
    length1 = length2;
    length2 = temp;
  }

  char now1 = -1, now2 = -1;
  for(int i = 0; i < length1; i++){
    now1 = str1[i];
    now2 = str2[i];
    if(now1 == now2) exact_chars ++;
  }

  return exact_chars/length2;
  return 0.;
}

int calculate_hamming_distance (const char *str1, const char *str2)
{
  if (!str1 || !str2) return -1;
  int length1 = strlen(str1), length2 = strlen(str2);
  if(length1 > length2){
    int temp = length1;
    length1 = length2;
    length2 = temp;
  }
  double not_exact_chars = 0;

  char now1 = -1, now2 = -1;
  for(int i = 0; i < length1; i++){
    now1 = str1[i];
    now2 = str2[i];

    if(now1 != now2) not_exact_chars ++;
  }

  return not_exact_chars + length2 - length1;
  return 0;
}

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
      D[i + j * (length1 + 1)] = 0;
    }
  }

  int subCost = 0;
  for (int i = 1; i < length1 + 1; i++){
    for (int j = 1; j < length2 + 1; j++){
      subCost = 0;
      if(str1[i-1] == str2[j-1]) subCost = 1;


      int lev1 = D[i-1 + j * (length1 + 1)] + 1;
      int lev2 = D[i + (j-1) * (length1 + 1)] + 1;
      int lev3 = D[i-1 + (j-1) * (length1 + 1)] + subCost;
      int levmin = lev1;
      if(lev2 < levmin) levmin = lev2;
      if(lev3 < levmin) levmin = lev3;
      D[i + j * (length1 + 1)] = levmin;
    }
  }
  return D[(length1+1) * (length2+1) - 1];
}

void create_editorial_regulations (const int *D, const char* n1, const char* n2, const int levenstein_distance, char *editorial_regulations){
  if (!D || !n1 || !n2 || !levenstein_distance || !editorial_regulations) return;

  int i = strlen(n1), j = strlen(n2), counter = levenstein_distance;
  int costL = 10, costLU = 10, costU = 10;
  while (1 <= i && 1 <= j){
    counter --;
    costL = D[(i-1) + j * strlen(n1)];
    costLU = D[(i-1) + (j-1) * strlen(n1)];
    if(D[i + j * strlen(n1)] == costLU) costLU--;
    costU = D[i + (j-1) * strlen(n1)];

    if(costL <= costLU && costL <= costU){
      i --;
      editorial_regulations[counter] = 'D';
      continue;
    }
      
    if(costLU <= costL && costLU <= costU){
      i --;
      j --;
      if(D[i + j * strlen(n1)] == D[i+1 + (j+1) * strlen(n1)]){
        continue;
      }
      editorial_regulations[counter] = 'R';
      continue;
    }
    
    if(costU <= costL && costU <= costLU){
      j --;
      editorial_regulations[counter] = 'I';
      continue;
    }
  }
  editorial_regulations[levenstein_distance] = '\0';
}
