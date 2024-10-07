#include "lib.h"

int main() {
  FILE *in = NULL;
  List *head = NULL;
  in = fopen("file.txt", "r");
  if (in == NULL) return -1;
  if (read_file(in, &head) < 0) {
    List_free(head);
    fclose(in);
    return -1;
  }
  fclose(in);
  print(head);
  List_free(head);
  return 0;
}
