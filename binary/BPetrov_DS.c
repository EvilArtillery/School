#include <stdio.h>
#include <stdlib.h>

int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
int xM, yM, board_size = -1;

int checkMoves(int** board, int x, int y){
	int i, temp = 0, xM = -1, yM = -1;
	for(i = 0; i < 8; i++){
		xM = x + moves[i][0];
        	yM = y + moves[i][1];
	        if(xM < 0) continue;
        	if(yM < 0) continue;
	        if(xM >= board_size) continue;
        	if(yM >= board_size) continue;
		if(board[xM][yM] & 1) continue;
        	temp ++;
	}
	return temp;
}

void binaryPrint(int target){
	for(int counter = (8 * sizeof(int)) - 1; counter > 0; counter --){
		printf("%i", (target >> counter) & 1);
	}
	printf("\n");
}

void printBoard(int** board, int length, int x, int y){
	int value = -1;
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			value = board[i][j] >> 9;
			if((x == i) && (y == j)){
				printf("\x1b[31m" "[%3i]" "\x1b[0m", value);
				continue;
			}
			printf("[%3i]", value);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int main(){
	unsigned int temp, x, y;

	printf("Enter the size of your board: ");
	if(! scanf("%u", &board_size)){
		perror("Scanf failed");
		return -1;
	}

	if(5 > board_size){
		printf("No tour possible\n");
		return -1;
	}

	int** board = malloc(board_size * sizeof(int*));
	for(temp = 0; temp < board_size; temp ++){
		board[temp] = malloc(board_size * sizeof(int));
	}

	for(x = 0; x < board_size; x++){
		for(y = 0; y < board_size; y++){
			board[x][y] = 0;
		}
	}

	printf("Enter the x of starting position: ");
	if(! scanf("%u", &x)){
		perror("Scanf failed");
		return -1;
	}

	printf("Enter the y of starting position: ");
	if(! scanf("%u", &y)){
		perror("Scanf failed");
		return -1;
	}

	if((board_size % 2 == 1) && ((x + y) % 2 == 1)){
		printf("No tour possible\n");
		return -1;
	}

	printf("\n");

	int xM, yM, minMoves = 8, TimeHere, ForksByMove;
        int movesMade, k, xF = -1, yF = -1;
        for(movesMade = 0; movesMade < board_size * board_size; movesMade ++){
//visuals       printBoard(board, board_size, x, y);
//debug		binaryPrint(board[x][y]);
//debug		printf("%i\n\n", checkMoves(board, x, y));
                minMoves = 8;
		TimeHere = ((board[x][y] >> 1) & 15);
		ForksByMove += ((board[x][y] >> 5) & 15);
                for(temp = 0; temp < 8; temp ++){
                        xM = x + moves[temp][0];
                        yM = y + moves[temp][1];
                        if(xM < 0) continue;
                        if(yM < 0) continue;
                        if(xM >= board_size) continue;
                        if(yM >= board_size) continue;
                        if(board[xM][yM] & 1) continue;
                        k = checkMoves(board, xM, yM);
                        if((k < minMoves) && ((0 != k) || ((board_size * board_size) == (movesMade + 2)))){
                                minMoves = k;
                                xF = xM;
                                yF = yM;
                                TimeHere = 0;
                        }
                        else if((k == minMoves) &&((k) || ((board_size * board_size) == (movesMade + 2)))){
                                xF = xM;
                                yF = yM;
                                TimeHere ++;
                                if(ForksByMove == TimeHere){
                                        break;
                                }
                        }
                }
		
                for(temp = 0; temp < 8; temp ++){
                        xM = x + moves[temp][0];
                        yM = y + moves[temp][1];
                        if(xM < 0) continue;
                        if(yM < 0) continue;
                        if(xM >= board_size) continue;
                        if(yM >= board_size) continue;
                        if(board[xM][yM] & 1) continue;
                        k = checkMoves(board, xM, yM);
                        if(k == minMoves){
                                ForksByMove += 1;
                        }
                }

		board[x][y] = (((((movesMade + 1) << 9) | (ForksByMove << 5)) | (TimeHere << 1)) | 1);

                if((0 == ForksByMove) && ((board_size * board_size) != (movesMade + 1))){
			board[x][y] = 0;
                        movesMade -= 2;
                        ForksByMove = -1;
                }
                x = xF;
                y = yF;
		if(-1 != ForksByMove) ForksByMove = 0;

        }
	printBoard(board, board_size, -1, -1);
	printf("\n");
	free(board);
	return 1;
}

