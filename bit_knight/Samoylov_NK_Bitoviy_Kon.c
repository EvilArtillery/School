#include <stdlib.h>
#include<stdio.h>

int separation (int i, int j, int N);
int condition (int i, int j, char* board, int N);
int can_go (char *board, int i, int j, int N);
int occupy (int i, int j, char* board, int N);
void variants (int *nextX, int *nextY, int startX, int startY, int var);
int way (char *board, int i0, int j0, int N, int counter);

int main() {
  int N = 0;
  int startX = 0;
  int startY = 0;
  printf ("Размер доски N:\n");
  if (scanf("%d", &N) != 1) {
    printf("error: not a number\n");
    return -1;
  }
  if (N <= 0) {
    printf("error N <= 0\n");
    return -1;
  }
  printf ("Начальное положение коня(координаты):\n");
  if (scanf("%d", &startX) != 1) {
    printf("error: not a number\n");
    return -1;
  }
  if (scanf("%d", &startY) != 1) {
    printf("error: not a number\n");
    return -1;
  }
  char *board = malloc(sizeof(char) * separation(N - 1, N - 1, N));
  if (board == NULL) return -1;
  
  for (int u = 0; u < separation( N - 1 , N - 1, N); u++) {
    board[u] = 0;
  }
  
  if (can_go(board, startX, startY, N) < 0) {
    printf("error: start cordinates\n");
    return -1;
  }
  int count = 1;
  way (board, startX, startY, N, count);
  free(board);
  return 0;
}

int separation (int i, int j, int N) {
  int line = 0;
  if ((i * N + j + 1) % sizeof(char) != 0) {
    line = (i * N + j + 1) / sizeof(char) + 1;
  }
  else {
    line = ( i * N + j + 1) / sizeof(char);
  }
  return line;
}

int condition (int i, int j, char* board, int N) {
  int line = separation(i, j, N);
  char pos = (board[line - 1]) | (1 << (sizeof(char) * line - (i * N + j + 1)));
  if (pos == board[line - 1]) return 1;
  return 0;
}

int can_go (char *board, int i, int j, int N) {
  if (i > N - 1 || j > N - 1 || j < 0 || i < 0 || condition(i, j, board, N) > 0) return -1;
  return 0;
}

int occupy (int i, int j, char* board, int N) {
  int line = separation(i, j, N);
  board[line - 1] = (board[line - 1]) | (1 << (sizeof(char) * line - (i * N + j + 1)));
  return 0;
}

void variants (int *nextX, int *nextY, int startX, int startY, int var) {
  if (var == 0) {
    *nextX = startX + 2;
    *nextY = startY - 1;
  }
  else if (var == 1) {
    *nextX = startX + 2;
    *nextY = startY + 1;
  }
  else if (var == 2) {
    *nextX = startX + 1;
    *nextY = startY + 2;
  }
  else if (var == 3) {
    *nextX = startX - 1;
    *nextY = startY + 2;
  }
  else if (var == 4) {
    *nextX = startX - 2;
    *nextY = startY + 1;
  }
  else if (var == 5) {
    *nextX = startX - 2;
    *nextY = startY - 1;
  }
  else if (var == 6) {
    *nextX = startX - 1;
    *nextY = startY - 2;
  }
  else if (var == 7) {
    *nextX = startX + 1;
    *nextY = startY - 2;
  }
}

int way (char *board, int i0, int j0, int N, int counter) {
  int i1 = 0;
  int j1 = 0;
  int line = separation(i0, j0, N);
  if (counter == N * N) {
    board[i0 * N + j0] = counter;
    printf("%d-й ход:  %d  %d \n", counter, j0, i0);
    return 0;
  }
  for (int i = 0; i < 8; i++) {
    variants(&i1, &j1, i0, j0, i);
    if (can_go(board, i1, j1, N) < 0) {
      continue;
    }
    occupy(i0, j0, board, N);
    if (way (board, i1, j1, N, counter + 1) < 0) {
      continue;
    }
    else {
      printf("%d-й ход:  %d  %d \n", counter, j0, i0);
      return 0;
    }
  }
  board[line - 1] = (board[line - 1]) & (~(1 << (sizeof(char) * line - (i0 * N + j0 + 1))));
  return -1;
}
