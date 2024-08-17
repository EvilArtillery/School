#ifndef LIB_H
#define LIB_H

double calculate_identity (const char *str1, const char *str2);
int calculate_hamming_distance (const char *str1, const char *str2);
int calculate_levenstein_distance (const char *str1, const char *str2, int *D);
void create_editorial_regulations (const int *D, const char *str1, const char *str2, const int levenstein_distance, char *editorial_regulations);

#endif //LIB_H
