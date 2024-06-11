#include <stdio.h>
#include <stdlib.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};


void printMoveBoard(int* board, int board_size, int x, int y){
	int i, j, value;
	for(i = board_size-1; i >= 0; i--){
		for(j = 0; j < board_size; j++){
			value = board[i + (j * board_size)];
			if(x == i && y == j){
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

int readMoves(unsigned char* board, int board_size, int x, int y){
	int result = 0;
	for(int tmp = 0; tmp < 8; tmp ++){
		if((board[x + (y * board_size)] >> tmp) & 1){
			result ++;
		}
	}
	return result;
}

int checkMoves(int* moveBoard, int board_size, int x, int y){
	int result = 0, xM, yM;
	for(int tmp = 0; tmp < 8; tmp ++){
		xM = x + moves[tmp][0];
		yM = y + moves[tmp][1];
		if(xM < 0) continue;
                if(yM < 0) continue;
                if(xM >= board_size) continue;
                if(yM >= board_size) continue;
		if(moveBoard[xM + (yM * board_size)]) continue;
		result += 1;
	}
	return result;
}

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

void charBinaryPrint(unsigned char target){
	int max = sizeof(unsigned char) * 8;
	for(int counter = max; counter > 0; counter --){
		printf("%i", (target >> counter) & 1);
	}
	printf("\n");
}

int main(){
	int size = 0, x, y, tmp;

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

	if(x < 0){
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

	for(tmp = 0; tmp < size * size; tmp ++){
		moveBoard[tmp] = 0;
	}

	for(tmp = 0; tmp < size; tmp ++){
		for(int tmp2 = 0; tmp2 < size; tmp2 ++){
			writeMoves(board, moveBoard, size, tmp, tmp2);
		}
	}

	int movesMade;
	int xM, yM, xF, yF;
	int movesFromChecked, minMoves;
	int ForkCounter, ForkBlock, ForkBlockBase = 1;

	for(movesMade = 0; movesMade < size * size; movesMade ++){
		moveBoard[x + (y * size)] = movesMade + 1;
		ForkBlock = ForkBlockBase;

		//debug and visuals
		printMoveBoard(moveBoard, size, x, y);

		minMoves = 8;
		for(tmp = 0; tmp < 8; tmp ++){
			xM = x + moves[tmp][0];
			yM = y + moves[tmp][1];
			if(xM < 0) continue;
			if(yM < 0) continue;
			if(xM >= size) continue;
			if(yM >= size) continue;
			if(moveBoard[xM + (yM * size)]) continue;
			writeMoves(board, moveBoard, size, xM, yM);
			movesFromChecked = readMoves(board, size, xM, yM);
			if(movesFromChecked < minMoves){
				minMoves = movesFromChecked;
				ForkBlock = ForkBlockBase;
				continue;
			}
			if(movesFromChecked == minMoves){
				ForkBlock ++;
			}
		}

		xF = -1;
		yF = -1;
		minMoves = 8;
		ForkCounter = 0;
		for(tmp = 0; tmp < 8; tmp ++){
			if(ForkBlock == ForkCounter) break;
			if((board[x + (y * size)] >> tmp) & 1){
				xF = x + moves[tmp][0];
				yF = y + moves[tmp][1];
				ForkCounter ++;
			}
		}

		if(-1 == xF){
			ForkBlockBase = 0;
			movesMade -= 2;
			continue;
		}
		x = xF;
		y = yF;
		ForkBlockBase = 0;
	}

	printMoveBoard(moveBoard, size, x, y);
	free(board);
	free(moveBoard);
	return 1;
}
