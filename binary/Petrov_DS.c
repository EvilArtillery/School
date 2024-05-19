#include <stdio.h>
#include <stdlib.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
unsigned int a, temp, x, y;

int checkMoves(int* board, int x, int y){
	int i, result = 0, xM, yM;

	for(i = 0; i < 8; i++){
		xM = x + moves[i][0];
		yM = y + moves[i][1];
		if(xM < 0) continue;
		if(yM < 0) continue;
		if(xM >= a) continue;
		if(yM >= a) continue;
		if(0 == board[xM + (a * yM)]) result ++;
	}

	return result;
}

void printBoard(int* board, int a, int xNow, int yNow){
	printf("\n");
	int i, j, value;
	for(i = a - 1; i > -1; i--){
		for(j = 0; j < a; j++){
			value = board[i + (a * j)];
			if((xNow == i) && (yNow == j)){
				printf("\x1b[31m" "[%3i]" "\x1b[0m", value);
				continue;
			}
			printf("[%3i]", value);
		}
		printf("\n");
	}
	printf("\n\n-------------------------------------\n");
}

int main(){

	printf("Enter the length of your board: ");
	if(! scanf("%i", &a)){
		perror("Scanf failed");
		return -1;
	}

/*	printf("Enter the height of your board: ");
	if(! scanf("%i", &b)){
		perror("Scanf failed");
		return -1;
	}

	if(b < a){
		temp = b;
		b = a;
		a = temp;
	}

	if((1 == a) || (2 == a)){
		printf("No tour possible\n");
		return -1;
	}

	if((3 == a) && ((3 == b) || (5 == b) || (6 == b))){
		printf("No tour possible\n");
		return -1;
	}

	if((4 == a) && (4 == b)){
		printf("No tour possible\n");
		return -1;
	}*/

	if(5 > a){
		printf("No tour possible\n");
		return -1;
	}

	printf("Enter the x of starting position: ");
	if(! scanf("%i", &x)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter the y of starting position: ");
	if(! scanf("%i", &y)){
		perror("Scanf failed");
		return -1;
	}

	if(((a % 2) == 1) && (1 == ((x + y) % 2))){
		printf("No tour possible\n");
		return -1;
	}

	int* board = (int *) malloc(a * a * sizeof(int*));
	if(! board){
		perror("Memory allocation error");
		return -1;
	}

	int i;
	for(i = 0; i < a * a; i++){
		board[i] = 0;
	}

	int* ForksByMove = (int*) malloc(a * a * sizeof(int));
	for(temp = 0; temp < a * a; temp ++){
		ForksByMove[temp] = -1;
	}

	printf("\n\n");
//	printBoard(board, a, -1, -1);

	int* TimeHere = (int*) malloc(a * a * sizeof(int));

	for(temp = 0; temp < a * a; temp ++){
		TimeHere[temp] = 0;
	}

	int xM, yM, minMoves = 8;
	int movesMade, k, xF = -1, yF = -1;
	for(movesMade = 0; movesMade < a * a; movesMade ++){
		board[x + (a * y)] = movesMade + 1;
//		printBoard(board, a, x, y);
		minMoves = 8;
		for(temp = 0; temp < 8; temp ++){
			xM = x + moves[temp][0];
			yM = y + moves[temp][1];
			if(xM < 0) continue;
			if(yM < 0) continue;
			if(xM >= a) continue;
			if(yM >= a) continue;
			if(board[xM + (a * yM)]) continue;
			k = checkMoves(board, xM, yM);
			if((k < minMoves) && ((0 != k) || ((a * a) == (movesMade + 2)))){
				minMoves = k;
				xF = xM;
				yF = yM;
				TimeHere[movesMade] = 0;
			}
			else if((k == minMoves) &&((k) || ((a * a) == (movesMade + 2)))){
				xF = xM;
				yF = yM;
				TimeHere[movesMade] += 1;
				if(ForksByMove[movesMade] == TimeHere[movesMade]){
					break;
				}
			}
		}
		for(temp = 0; temp < 8; temp ++){
			xM = x + moves[temp][0];
			yM = y + moves[temp][1];
			if(xM < 0) continue;
			if(yM < 0) continue;
			if(xM >= a) continue;
			if(yM >= a) continue;
			if(board[xM + (a * yM)]) continue;
			k = checkMoves(board, xM, yM);
			if(k == minMoves){
				if(-1 == ForksByMove[movesMade]) ForksByMove[movesMade] += 1;
				ForksByMove[movesMade] += 1;
			}
		}

		if((0 == ForksByMove[movesMade]) && ((a * a) != (movesMade + 1))){
			board[x + (a * y)] = 0;
			movesMade -= 1;
			ForksByMove[movesMade] -= 1;
			movesMade -= 1;
		}
		x = xF;
		y = yF;
	}
	printBoard(board, a, -1, -1);
	printf("\n");
	free(board);
	free(ForksByMove);
	free(TimeHere);
	return 1;
}
