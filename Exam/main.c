#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

int main (int argc, char *argv[])
{
  if (argc != 3) 
  {
    printf ("Too Few Arguments!\n");
    return -1;
  }

  FILE *in1 = NULL, *in2 = NULL;
  in1 = fopen (argv[1], "r");
  in2 = fopen (argv[2], "r");
  if (!in1 || !in2)
  {
    if (in1) fclose (in1);
    if (in2) fclose (in2);
    return -1;
  }

  char *str1 = NULL, *str2 = NULL;

  if (fscanf (in1, "%ms", &str1) != 1 || fscanf (in2, "%ms", &str2) != 1)
  {
    fclose (in1);
    fclose (in2);
    if (str1) free (str1);
    if (str2) free (str2);
    printf ("Unable to Read Some File\n");
    return -1;
  }

  fclose (in1);
  fclose (in2);

  int *D = (int*) malloc ((strlen (str1) + 1) * (strlen (str2) + 1) * sizeof (*D));

  if (!D)
  {
    free (str1);
    free (str2);
    printf ("Not Enough Memory\n");
    return -1;
  }

  double identity = calculate_identity (str1, str2);
  int hamming_distance = calculate_hamming_distance (str1, str2);
  int levenstein_distance = calculate_levenstein_distance (str1, str2, D);

  char *editorial_regulations = NULL;
  if (levenstein_distance > 0) 
  {
    editorial_regulations = (char*) malloc ((levenstein_distance + 1) * sizeof (*editorial_regulations));

    if (!editorial_regulations)
    {
      free (D);
      return -1;
    }
    create_editorial_regulations (D, str1, str2, levenstein_distance, editorial_regulations);
  }
  printf ("identity = %e\nhamming_distance = %d\nlevenstein_distance = %d\n",
          identity, hamming_distance, levenstein_distance);

  if (levenstein_distance > 0)
    printf ("editorial_regulations = %s\n", editorial_regulations);

  free (D);
  free (str1);
  free (str2);

  if (levenstein_distance > 0) 
    free (editorial_regulations);

  return 0;
}
