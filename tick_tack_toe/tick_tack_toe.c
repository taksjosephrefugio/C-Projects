/*
This is a tick-tack-toe game that checks for 
three-in-a-rows for either vertical, horizontal,
or diagonal orientation. 

INPUT: a char for a token, and the game will constantly
ask for a number coinciding with the part of the board
to put your token

OUTPUT: Either win or lose or draw

Code written by: TAK'S JOSEPH REFUGIO
Code written on: Spring 2017
Code written for: Prof. Theys, CS Department, UIC
*/
#include <stdio.h>
#define NUM_ROWS 3
#define NUM_COLS 3

typedef enum {LOSE, WIN, WAITING} DECISION;

char myBoard[NUM_ROWS][NUM_COLS];
char playertoken[2] = {'x', 'o'};

// Resets the Board
void initializeBoard (char aBoard[NUM_ROWS][NUM_COLS]) {	
	for (int CTR1 = 0; CTR1 < NUM_ROWS; CTR1++)
	{
		for (int CTR2 = 0; CTR2 < NUM_COLS; CTR2++)
		{
			aBoard[CTR1][CTR2] = '-';
		}
	}
}

// Print the Board on the Terminal
void printBoard (char aBoard[NUM_ROWS][NUM_COLS]) {
	for (int CTR1 = 0; CTR1 < NUM_ROWS; CTR1++) {
		for (int CTR2 = 0; CTR2 < NUM_COLS; CTR2++) {
			printf("%c ", aBoard[CTR1][CTR2]);
		}
		printf("\n");
	}
}

// Takes a board. Checks for any three-in-a-row. 
void verticalCheck(char aBoard[NUM_ROWS][NUM_COLS], DECISION*result, char token) {
	for (int CTR = 0; CTR < NUM_COLS; CTR++) {
		if (((aBoard[0][CTR] == token) && 
			(aBoard[1][CTR] == token)) && 
			(aBoard[2][CTR] == token)
			)
		{ *result = WIN; }
	}
}

// Takes a board. Checks for any three-in-a-column. 
void horizontalCheck(char aBoard[NUM_ROWS][NUM_COLS], DECISION*result, char token) {
	for (int CTR = 0; CTR < NUM_ROWS; CTR++) {
		if (((aBoard[CTR][0] == token) && 
			(aBoard[CTR][1] == token)) && 
			(aBoard[CTR][2] == token)
			)
		{ *result = WIN; }
	}
}

// Takes a board. Checks for any three-in-a-diagonal. 
void diagonalCheck(char aBoard[NUM_ROWS][NUM_COLS], DECISION*result, char token) {
	if (((aBoard[0][0] == token) && 
			(aBoard[1][1] == token)) && 
			(aBoard[2][2] == token)
			)
		{ *result = WIN; }

	if (((aBoard[0][2] == token) && 
			(aBoard[1][1] == token)) && 
			(aBoard[2][0] == token)
			)
		{ *result = WIN; }
}

// Places a player's token on the board
void insertToken(char aBoard[NUM_ROWS][NUM_COLS], char token) {
	int row, col;

	printf("\t\t\t\t\t\t\tRow:    ");
	scanf("%d", &row);

	printf("\t\t\t\t\t\t\tColumn: ");
	scanf("%d", &col);

	aBoard[row-1][col-1] = token;
}

// For testing results
void testResults(DECISION status) {
	switch(status) 
	{
		case LOSE:
		printf("Lose\n");
		break;

		case WIN:
		printf("Win!\n");
		break;

		case WAITING:
		printf("Waiting for winner\n");
		break;
	}
}


void main(void) {
	DECISION player1Status = WAITING;

	// Resets the Board
	initializeBoard(myBoard);

	while (player1Status != WIN) {
	system("cls");

	// Printing the Board
	printBoard(myBoard);

	// Prompting user for row and col to put token
	insertToken(myBoard, playertoken[0]);

	// Checking for three-in-a-rows
	diagonalCheck(myBoard, &player1Status, playertoken[0]);

	// Checks if there's a win
	testResults(player1Status);

	if (player1Status == WIN) { printBoard(myBoard); }
	}

}


