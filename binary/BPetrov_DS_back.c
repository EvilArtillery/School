#include <stdio.h>
#include <stdlib.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

void turnsToMoveBoard(int* turns, int move, int* moveBoard, int board_size){
	int i;
	/* Clear moveBoard */
	for (i = 0; i < board_size * board_size; i++) {
		moveBoard[i] = 0;
	}	
	/* Fill moves */
	for (i = 0; i < move; i++){
		moveBoard[turns[2 * i] + (turns[2 * i + 1] * board_size)] = i;
	}	
}	


void printMoveBoard(int* moveBoard, int board_size, int x, int y){
	int i, j, value;
	for(i = board_size-1; i >= 0; i--){
		for(j = 0; j < board_size; j++){
			value = moveBoard[j + (i * board_size)];
			if(x == j && y == i){
				printf("\x1b[31m" "[%3i]" "\x1b[0m", value);
			}
			else{
				printf("[%3i]", value);
			}
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int countMoves(unsigned char* board, int board_size, int x, int y){
	int result = 0, xM, yM;
	for(int tmp = 0; tmp < 8; tmp ++){
		xM = x + moves[tmp][0];
		yM = y + moves[tmp][1];
		if(xM < 0) continue;
                if(yM < 0) continue;
                if(xM >= board_size) continue;
                if(yM >= board_size) continue;
		if(board[xM + (yM * board_size)] > 0) continue;
		result += 1;
	}
	return result;
}

void chooseNextField(int* x, int* y, int variants){
	for(int tmp = 0; tmp < 8; tmp ++){
		if (variants & (1<<tmp)){
			*x = *x + moves[tmp][0];
			*y = *y + moves[tmp][1];
			break;
		}	
	}	
}	

int findMoveIndex (int x, int y){
	for (int tmp = 0; tmp < 8 ; tmp++){
		if ((moves[tmp][0] == x) && (moves[tmp][1] == y)) return tmp;
	}      	
	return -1;
}	

void stepBack(int* turns, unsigned char* board, int* moveBoard, int* x, int* y, int* movesMade, unsigned char * variants, int size){
	int prevX = turns[2 * (*movesMade -1)];
	int prevY = turns[2 * (*movesMade -1) + 1];
	int deltaX = *x - prevX;
	int deltaY = *y - prevY;

	int index = findMoveIndex(deltaX, deltaY);

	unsigned char prev_variants = board[prevX + (size * prevY)];

	/* Remove this variant */
	prev_variants = prev_variants & (255 ^ (1<<index));

	/* Clear turns and boards */
	turns[2 * (*movesMade)] = 0;
	turns[2 * (*movesMade) + 1] = 0;
	board[*x + (*y * size)] = 0;
	moveBoard[*x + (*y * size)] = 0;

	/* Write updated variants and counts back counters */
	board[prevX + (size * prevY)] = prev_variants;
	*variants = prev_variants;
	*x = prevX; *y = prevY;
	(*movesMade)--;

}		

/*
void writeMoves(unsigned char* board, int* moveBoard, int board_size, int x, int y){
	int xM, yM, tmp;
	for(tmp = 0; tmp < 8; tmp ++){
		xM = x + moves[tmp][0];
		yM = y + moves[tmp][1];
		if(xM < 0) continue;
		if(yM < 0) continue;
		if(xM >= board_size) continue;
		if(yM >= board_size) continue;
		if(readMoves(board, board_size, xM, yM)) continue;
		board[x + (y * board_size)] = (board[x + (y * board_size)]) | (1 << tmp);
	}
}
*/

void charBinaryPrint(unsigned char target){
	int max = sizeof(unsigned char) * 8;
	for(int counter = max; counter > 0; counter --){
		printf("%i", (target >> counter) & 1);
	}
	printf("\n");
}

int main(){
	int size = 0, x, y, tmp, xStart, yStart;

	printf("Enter the size of your board: ");
	if(1 != scanf("%i", &size)){
		printf("\x1b[31mInput error!\x1b[0m\n");
		return -1;
	}

	if(5 > size){
		printf("No tour possible\n");
		return -1;
	}

	printf("Enter the x of your starting position: ");
	if(1 != scanf("%i", &x)){
                printf("\x1b[31mInput error!\x1b[0m\n");
                return -1;
        }

	if(x < 0){
		printf("\x1b[31m" "Outside the board" "\x1b[0m\n");
		return -1;
	}
	if(x >= size){
                printf("\x1b[31m" "Outside the board" "\x1b[0m\n");
                return -1;
        }

	printf("Enter the y of your staring position: ");
	if(1 != scanf("%i", &y)){
                printf("\x1b[31mInput error!\x1b[0m\n");
                return -1;
        }

	if(y < 0){
                printf("\x1b[31m" "Outside the board" "\x1b[0m\n");
                return -1;
        }
        if(y >= size){
                printf("\x1b[31m" "Outside the board" "\x1b[0m\n");
                return -1;
        }

	if(1 == (size % 2)){
		if(1 == ((x + y) % 2)){
			printf("No tour possible\n");
			return -1;
		}
	}

	xStart = x; yStart = y;
	unsigned char* board = (unsigned char*) malloc(size * size * sizeof(unsigned char));
	if(NULL == board){
		perror("Memory allocation error");
		return -1;
	}

	int* moveBoard = (int*) malloc(size * size * sizeof(int));
	if(NULL == moveBoard){
		perror("Memory allocation error");
		free(board);
		return -1;
	}

	/* X,Y coordinates array */
	int* turns = (int*) malloc(2 * size * size * sizeof(int));

	for(tmp = 0; tmp < size * size; tmp ++){
		moveBoard[tmp] = 0;
		board[tmp] = 0;
		turns[tmp * 2] = 0;
		turns[tmp * 2 + 1] = 0;
	}


	int movesMade;
	for(movesMade = 0; movesMade < size * size; movesMade ++){

		/* Set turn */
		turns[2 * movesMade] = x;
		turns[2 * movesMade + 1] = y;
		moveBoard[x + (y * size)] = movesMade + 1;

		//debug and visuals
		//turnsToMoveBoard(turns, movesMade, moveBoard, size);
		//printMoveBoard(moveBoard, size, x, y);

		int minMoves = 8, movesCount;
		unsigned char variants = 0;
		int xM, yM;
		for(tmp = 0; tmp < 8; tmp ++){
			xM = x + moves[tmp][0];
			yM = y + moves[tmp][1];
			if(xM < 0) continue;
			if(yM < 0) continue;
			if(xM >= size) continue;
			if(yM >= size) continue;
			if(board[xM + (yM * size)]) continue;
			
			/* Next field is empty
			 * Count possible moves from it
			 */
			movesCount = countMoves(board, size, xM, yM);
			if(movesCount < minMoves){
				/* Reset variants and write new one*/
				variants = 0;
				variants = variants | (1 << tmp);
				minMoves = movesCount;
			} else if(movesCount == minMoves){
				variants = variants | (1 << tmp);
			}
		}

		/* Write all possible moves to board */
		board[x + (y * size)] = variants;

		/* All done. Exit */
		if ((0 == variants) && (size*size == movesMade + 1)) break;

		/* If no moves from here go to previous fork */
		while (0 == variants) {
			printf("x=%2d y=%2d\n", x,y);
			charBinaryPrint(variants);
			stepBack(turns, board, moveBoard, &x, &y, &movesMade, &variants, size);
			printf("x=%2d y=%2d\n", x,y);
			charBinaryPrint(variants);
		}	

		/* Back to start. No ways */
		if ((0 == variants) && ( x == xStart) && (y == yStart)) break;

		/* Choose next field from possible variants */
		chooseNextField(&x,&y,variants);

	}

	//debug and visuals
	// turnsToMoveBoard(turns, movesMade, moveBoard, size);
	printMoveBoard(moveBoard, size, x, y);
	free(board);
	free(moveBoard);
	free(turns);
	return 1;
}
