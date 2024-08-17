#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

int main(){
	int board_side = -1, board_size;
	int xStart = -1, yStart = -1;

	if(! scanf("%i", &board_side)){
		perror("Scanf failed");
		return -1;
	}

	if(board_side < 5){
		printf("No tour possible");
		return 0;
	}

	if(! scanf("%i", &xStart)){
		perror("Scanf failed");
		return -1;
	}

	if(! scanf("%i", &yStart)){
		perror("Scanf failed");
		return -1;
	}

	if(1 == ((xStart + yStart) % 2)){
		if(0 == (board_side % 2)){
			printf("No tour possible\n");
			return 0;
		}
	}

	board_size = board_side * board_side;

	bool* board = malloc(board_size * sizeof(bool));

	for(int i = 0; i < board_size; i++){
		board[i] = 0;
	}

	int x = xStart, y = yStart;
	board[x * board_side + y] = 1;

	int i, j, k, minMoves, possibleMoves, move, xNow = -1, yNow = -1;
	for(i = 0; i < board_size; i++){
		printf("(%i, %i)\n", x, y);
		minMoves = 9;
		move = -1;
		for(j = 0; j < 8; j++){
			xStart = x + moves[j][0];
			if(xStart >= board_side) continue;
			if(xStart < 0) continue;
			yStart = y + moves[j][1];
			if(yStart >= board_side) continue;
			if(yStart < 0) continue;
			if(1 == board[xStart * board_side + yStart]) continue;
			possibleMoves = 0;
			for(k = 0; k < 8; k++){
				if(8 == (j + k)) continue;
				xNow = x + moves[j][0] + moves[k][0];
				if(xNow >= board_side) continue;
				if(xNow < 0) continue;
				yNow = y + moves[j][1] + moves[k][1];
				if(yNow >= board_side) continue;
				if(yNow < 0) continue;
				if(0 == board[xNow * board_side + yNow]) possibleMoves++;
			}
			if(possibleMoves < minMoves){
				if(0 == possibleMoves){
					if(i+1 < board_size) continue;
				}
				minMoves = possibleMoves;
				move = j;
			}
		}
		x += moves[move][0];
		y += moves[move][1];
		board[x * board_side + y] = 1;
	}

	printf("\x1b[31m(%i, %i)\x1b[0m\n", x, y);

	free(board);
	return 1;
}
