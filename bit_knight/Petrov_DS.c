#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

void set_bit(unsigned char *board, int position){
	unsigned char *target;
	target = board + (position / 8);
	*target = *target | (1 << position%8);
}

void remove_bit(unsigned char *board, int position){
	unsigned char *target = board + (position/8);
	*target &= ~(1 << position%8);
}

int get_bit(unsigned char *board, int position){
	unsigned char *target = board + (position/8);
	int value = 1 & (*target >> position%8);
	return value;
}

int main(){
	int board_side = -1, board_size;
	int xStart = -1, yStart = -1;

	printf("Enter the length of your board: ");
	if(! scanf("%i", &board_side)){
		perror("Scanf failed");
		return -1;
	}

	if(board_side < 5){
		printf("No tour possible");
		return 0;
	}

	printf("Enter the x coordinate of starting position: ");
	if(! scanf("%i", &xStart)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter the y coordinate of starting position: ");
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

	int array_size = board_size/(sizeof(unsigned char) * 8) + (0 != (board_size%8));
	unsigned char* board = malloc(array_size * sizeof(unsigned char));

	for(int i = 0; i < array_size; i++){
		board[i] = 0;
	}

	int x = xStart, y = yStart;
	int xMove = -1, yMove = -1;

	int i, j, k, minMoves, possibleMoves;
	int skip = 0, move, xNow = -1, yNow = -1, coordinate;
	for(i = 1; i < board_size; i++){
		coordinate = x * board_side + y;
		set_bit(board, coordinate);
		printf("(%i, %i)\n", x, y);
		minMoves = 9;
		move = -1;
		for(j = skip; j < 8 + skip; j++){
			xMove = x + moves[j%8][0];
			if(xMove >= board_side) continue;
			if(xMove < 0) continue;
			yMove = y + moves[j%8][1];
			if(yMove >= board_side) continue;
			if(yMove < 0) continue;
			coordinate = xMove * board_side + yMove;
			if(1 == get_bit(board, coordinate)) continue;
			possibleMoves = 0;
			for(k = 0; k < 8; k++){
				if(8 == (j%8 + k)) continue;
				xNow = x + moves[j%8][0] + moves[k][0];
				if(xNow >= board_side) continue;
				if(xNow < 0) continue;
				yNow = y + moves[j%8][1] + moves[k][1];
				if(yNow >= board_side) continue;
				if(yNow < 0) continue;
				coordinate = xNow * board_side + yNow;
				if(0 == get_bit(board, coordinate)) possibleMoves++;
			}
			if(possibleMoves < minMoves){
				if(0 == possibleMoves){
					if(i+1 < board_size){
						continue;
					}
				}
				minMoves = possibleMoves;
				move = j;
			}
		}
		if((9 == minMoves) && (i < board_size-1)){
			skip += 1;
			for(k = 0; k < array_size; k++){
				board[k] = 0;
			}
			i = 0;
			x = xStart;
			y = yStart;
			printf("\x1b[31mAbort; no way out\x1b[0m\n");
			continue;
		}
		x += moves[move][0];
		y += moves[move][1];
	}

	printf("\x1b[31m(%i, %i)\x1b[0m\n", x, y);

	free(board);
	return 1;
}
