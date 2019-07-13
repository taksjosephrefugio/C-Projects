/*
This program is a variation of the classic connect 4 game. However, this
program will look for an 'L' formed instead. The orientation of the 'L' does
not matter as long as its three-in-a-row plus a base ('L').

Every player will have their own unique token that they will 'drop' on a
particular column of the board. To win, a particular set of token is needed
to form an 'L'.

Player can't drop a token on a column that is already full. If a player enters
an input that is not an integer or it is oustide the 1-9 column range,
the program will print an error message and will prompt the user again for an input.

When an 'L' has been formed, a congratulatory message will be printed and a prommpt
will come up asking the user if they wishes to have another round of the game. If
the user opts not to play anymore, an exit message will be printed and pressing the
enter key will subesquently exits the program.

Program Name: Connect 'L', Project 2
System: Microsoft Visual Studio Community 2015, Windows 10
@author: TAK'S JOSEPH REFUGIO
@version: March 3, 2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM_ROWS 8
#define NUM_COLS 9

// FUNCTION PROTOTYPES
void gameProper(char aBoard[NUM_ROWS][NUM_COLS], char player_one_token, char player_two_token, char player_three_token);
char promptAnotherGame();

void printResults(char aBoard[NUM_ROWS][NUM_COLS], char lastplayer, int wincheck, int gameboardcheck);

void LCheck_vertical(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck);
void three_in_a_column(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * col_winCheck, int * startingRow);
void baseCheck_vertical(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * result);

void LCheck_horizontal(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck);
void three_in_a_row(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * row_winCheck, int * startingCol);
void baseCheck_horizontal(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * result);

int boardFullCheck(char aBoard[NUM_ROWS][NUM_COLS]);
void printBoard(char aBoard[NUM_ROWS][NUM_COLS]);
void clearBoard(char aBoard[NUM_ROWS][NUM_COLS]);

int columnPicker(char aBoard[NUM_ROWS][NUM_COLS], char token);
int availableRowPicker(char aBoard[NUM_ROWS][NUM_COLS], int columnPick);
void dimensionPicker(char aBoard[NUM_ROWS][NUM_COLS], char token, int*row, int*col);

void flushInputBuffer();
void printCharALot(char aChar, int num);
void printGameName();
void welcomeMessage();
void exitMessage();

int winningCombinationCheck(char aBoard[NUM_ROWS][NUM_COLS], char token);

int slopeRight(char aBoard[NUM_ROWS][NUM_COLS], char token, int*slopeRightRow, int*slopeRightCol);
void LCheck_slopeRight(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck);
int slopeLeft(char aBoard[NUM_ROWS][NUM_COLS], char token, int*slopeLeftCol, int*slopeLeftRow);
void LCheck_slopeLeft(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck);
int main()
{
	welcomeMessage();										/* Prints a welcome message that prints everytime the program is launched */

															/*Declaring the Gameboard Array*/
	char myBoard[NUM_ROWS][NUM_COLS];

	printBoard(myBoard);
	/*Initializing player tokens*/
	char player_one_token = 'O';
	char player_two_token = 'X';
	char player_three_token = 'B';

	char anotherRoundAns = ' ';
	do {
		system("cls");
		clearBoard(myBoard);															/* Resetting the board*/
		gameProper(myBoard, player_one_token, player_two_token, player_three_token);	/* Plays one game of Connect 'L'*/
		anotherRoundAns = promptAnotherGame();											/* Asks the user if they want to play again */
	} while (anotherRoundAns == 'Y');

	system("cls");
	exitMessage();											/* Prints the exit message that prints just right before the program closes. */
	return 0;
}

// This function is the most important function of all
// It contains the one entire game algorithm
// INPUT ARGUMENT: (1) aBoard - the gameboard; 
//				(2) player_one_token - player one's token
//				(2) player_two_token - player two's token
//				(2) player_three_token - player three's token
void gameProper(char aBoard[NUM_ROWS][NUM_COLS], char player_one_token, char player_two_token, char player_three_token)
{
	/*While loop variables in use*/
	char lastPlayerPlayed = ' ';
	int winCheck = 0;
	int gameBoardCheck = 0;
	int columnPick, availableRow;
	int whileCtr = 0;

	while ((winCheck == 0) && (gameBoardCheck == 0))				/*Cycles thru while there is no winner or while the board is not full*/
	{
		switch (whileCtr % 3)
		{
		case 0:																			/*PLAYER ONE GAMEPLAY*/
			printGameName();															/*Printing the game name*/
			printBoard(aBoard);															/*Prints the gameboard*/
			dimensionPicker(aBoard, player_one_token, &availableRow, &columnPick);		/*Gets the Row and Column to populate the board with a token*/
			aBoard[availableRow][columnPick - 1] = player_one_token;					/*Populates the board with the appropriate token*/
			winCheck = winningCombinationCheck(aBoard, player_one_token);				/*Checks for a winning 'L' combination*/
			lastPlayerPlayed = player_one_token;										/*Sets player as last player who played*/
																						/*Counter update*/
			whileCtr++;
			break;
		case 1:																			/*PLAYER TWO GAMEPLAY*/
			printGameName();															/*Printing the game name*/
			printBoard(aBoard);															/*Prints the gameboard*/
			dimensionPicker(aBoard, player_two_token, &availableRow, &columnPick);		/*Gets the Row and Column to populate the board with a token*/
			aBoard[availableRow][columnPick - 1] = player_two_token;					/*Populates the board with the appropriate token*/
			winCheck = winningCombinationCheck(aBoard, player_two_token);				/*Checks for a winning 'L' combination*/
			lastPlayerPlayed = player_two_token;										/*Sets player as last player who played*/
																						/*Counter update*/
			whileCtr++;
			break;
		case 2:																				/*PLAYER THREE GAMEPLAY*/
			printGameName();																/*Printing the game name*/
			printBoard(aBoard);																/*Prints the gameboard*/
			dimensionPicker(aBoard, player_three_token, &availableRow, &columnPick);		/*Gets the Row and Column to populate the board with a token*/
			aBoard[availableRow][columnPick - 1] = player_three_token;						/*Populates the board with the appropriate token*/
			winCheck = winningCombinationCheck(aBoard, player_three_token);					/*Checks for a winning 'L' combination*/
			lastPlayerPlayed = player_three_token;											/*Sets player as last player who played*/
																							/*Counter update*/
			whileCtr++;
			break;
		}

		gameBoardCheck = boardFullCheck(aBoard);
		system("cls");
	};


	system("cls");
	printResults(aBoard, lastPlayerPlayed, winCheck, gameBoardCheck);		/*Printing results*/
}

// This function prints the opening welcome message
// It also contains instructions for the game
void welcomeMessage()
{
	printCharALot('=', 80);
	printf("\n");

	printf("\t\t\t\t   CONNECT 'L'\n");
	printf("\t\t\t\tby: T.J. Refugio\n");

	printCharALot('=', 80);
	printf("\n");
	printf("\n");

	printf("GAME INSTRUCTIONS: \n");
	printf("(1) Three players are needed to play this game.\n");
	printf("(2) Players drop a token on a particular column and the token\n");
	printf("    either hits the bottom of the column or \n");
	printf("    until it hits another token on that row.\n");
	printf("(3) The first player who can form an 'L' shape with their token wins the game.\n");
	printf("    The orientation does not matter. It could be an 'L' lying vertically, horizontally, or diagonally.\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t    GOOD LUCK. HAVE FUN!\n");
	system("pause");
}

// This function prints the exit message that is printed
// right before the program terminates. 
void exitMessage()
{
	printCharALot('=', 80);
	printf("\n");

	printf("\t\t\t\t   CONNECT 'L'\n");
	printf("\t\t\t\tby: T.J. Refugio\n");

	printCharALot('=', 80);
	printf("\n");
	printf("\n");

	printf("> THANKS FOR PLAYING. HAVE A NICE DAY.\n");
}

// This function will ask the user if they want to play another game
// Returns either Y or N
char promptAnotherGame()
{
	char anotherRoundAns = ' ';
	/*Keeps looping while input is not Y or N (not case sensitive)*/
	do {
		printf("\n");
		printf("Do you want to play another round? [Y/N]");
		scanf(" %c", &anotherRoundAns);
		anotherRoundAns = toupper(anotherRoundAns);					/*Makes any input in uppercase*/

		if ((((anotherRoundAns != 'Y') && (anotherRoundAns != 'N'))) || (!isalpha(anotherRoundAns)))
		{
			printf("ERROR! Valid inputs are Y(Yes) or (No)\n");
		}
	} while ((((anotherRoundAns != 'Y') && (anotherRoundAns != 'N'))) || (!isalpha(anotherRoundAns)));

	return anotherRoundAns;
}

// This function flushes the input buffer
// Mainly used for input checks
void flushInputBuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {} /*Flushes the input buffer*/
}

// This function prints a character multiple times
// INPUT ARGUMENTS: (1) aChar - the character to be printed
//					(2) num - the number of times a character will be printed
void printCharALot(char aChar, int num)
{
	for (int ctr = 0; ctr < num; ctr++)
	{
		printf("%c", aChar);
	}
}

//This function prints the board that is an argument
void printBoard(char aBoard[NUM_ROWS][NUM_COLS])
{
	for (int ctr = 1; ctr <= 9; ctr++)
	{
		printf("%3d", ctr);
	}
	printf("\n");
	printf("---------------------------");
	printf("\n");

	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)
	{
		for (int ctr2 = 0; ctr2 < NUM_COLS; ctr2++)
		{
			printf("%3c", aBoard[ctr1][ctr2]);
		}
		printf("\n");
	}
}

// This function prints the name of the game
// You could think of it as a header of the game board
void printGameName()
{
	printCharALot('=', 27);
	printf("\n");

	printf("       CONNECT 'L'\n");
	printf("     by: T.J. Refugio\n");

	printCharALot('=', 27);
	printf("\n");
}

// This function clears/resets the board to its empty state
// INPUT ARGUMENTS: (1) aBoard - the gameboard
void clearBoard(char aBoard[NUM_ROWS][NUM_COLS])
{
	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)
	{
		for (int ctr2 = 0; ctr2 < NUM_COLS; ctr2++)
		{
			aBoard[ctr1][ctr2] = '-';
		}
	}
}

//This function prints whether or not there is a winner.
//If there is a winner, this function also prints who won the game.
// INPUT ARGUMENTS:
// winnerCheck - 0 ~ no winnner; 1 ~ there is a winner
// token - tells the compiler who won the game
void printResults(char aBoard[NUM_ROWS][NUM_COLS], char lastplayer, int wincheck, int gameboardcheck)
{
	if ((wincheck == 1) && (gameboardcheck == 0))
	{
		printGameName();
		printBoard(aBoard);
		printf("\n");
		printf("Congratulations, player %c! You won the game.", lastplayer);
	}
	else if (gameboardcheck == 1)
	{
		printGameName();
		printBoard(aBoard);
		printf("\n");
		printf("The Board is full. There is no winner.\n");
	}
}

// This function checks if the board in question is either full or has an open space
// INPUT ARGUMENTS:
// 1) aBoard - the board in question
// returns 0 (board has an open space; return 1 (the board is full)
int boardFullCheck(char aBoard[NUM_ROWS][NUM_COLS])
{
	int result = 1;
	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)
	{
		for (int ctr2 = 0; ctr2 < NUM_COLS; ctr2++)
		{
			if (aBoard[ctr1][ctr2] == '-')
				result = 0;
		}
	}
	return result;
}

// This function checks for a winning 'L' combination
// FUNCTIONS USED: (1) LCheck_vertical; (2) LCheck_horizontal
// INPUT ARGUMENTS: (1) aBoard - the gameboard; (2) token - player token
int winningCombinationCheck(char aBoard[NUM_ROWS][NUM_COLS], char token)
{
	int result = 0;
	for (int ctr = 0; ctr < 4; ctr++)
	{
		switch (ctr)
		{
		case 0:
			LCheck_vertical(aBoard, token, &result);
			break;
		case 1:
			LCheck_horizontal(aBoard, token, &result);
			break;
		case 2:
			LCheck_slopeRight(aBoard, token, &result);
			break;
		case 3:
			LCheck_slopeLeft(aBoard, token, &result);
			break;
		}
		if (result == 1)
			break;
	}
	return result;
}

// INPUT: (1) aBoard - the gameboard
// POINTERS MODIFIED:	(1) *row - denotes an available row of a user picked column
//						(2) *col - denotes the column picked by the user
// FUNCTIONS USED: (1) int columnPicker; (2) int availableRowPicker()
void dimensionPicker(char aBoard[NUM_ROWS][NUM_COLS], char token, int*row, int*col)
{
	do {
		/*Prompts for a column the user wishes to drop their token*/
		/*NOTE: columnPick WILL BE +1 THAN ARRAY INDICES. TAKE NOTE WHEN USING columnPick*/
		*col = columnPicker(aBoard, token);

		/*Selects an available row based on the column picked by the user*/
		/*NOTE: availableRow is array indices friendly (i.e. can be used as is when calling myBoard)*/
		*row = availableRowPicker(aBoard, *col);

		if (*row + 1 == 0)
		{
			printf("There is no available space on Column %d. Pick a different column.", *col);
			system("pause");
		}
	} while (*row < 0); /*Keeps looping when when the column that the user entered do not have an available space in it.*/
}


// This function is used to prompt the user to enter a column 
// that will be used to drop their token down on the gameboard.
// INPUT ARGUMENTS:
// 1) aBoard - the board in question
// 2) token - used to identify which player is playing
// RETURN: an integer denoting the column the user picked 
int columnPicker(char aBoard[NUM_ROWS][NUM_COLS], char token)
{
	int columnPick = 0;
	do {
		/*Printing the board*/
		/*
		system("cls");
		printBoard(aBoard);
		printf("\n");
		*/


		printf("Player %c, pick a column: ", token);
		scanf("%d", &columnPick);
		flushInputBuffer();								/*Flushes the input buffer*/
		printf("\n");


		if ((columnPick < 1) || (columnPick > NUM_COLS)) /*Prints an error message when input is not within valid range.*/
		{
			printf("ERROR: Input is either outside the  valid column range (1-9) or not an integer.\n");
			system("pause");
		}
		else
		{
			break;	/*Gets out of the do-while loop when input is valid.*/
		}
	} while ((columnPick < 1) || (columnPick > NUM_COLS));	//Will keep on looping while column input is outside the valid column range (1-9).

	return columnPick;
}

// This function will pick an available row based on the column picked by the user 
// INPUT ARGUMENTS: (1) aBoard - the board of interest; (2) columnPick - denotes which column the user choses to land a token
// RETURN: an integer denoting an available row in the column picked by the user
// NOTE: If the value of return is 0. This means that there was no available space in the column picked by the user
int availableRowPicker(char aBoard[NUM_ROWS][NUM_COLS], int columnPick)
{
	int availableRowNum = -1; /*Row number that contains an available space based on the column picked*/
	for (int ctr = NUM_ROWS - 1; ctr >= 0; ctr--)
	{
		if (aBoard[ctr][columnPick - 1] == '-')
		{
			availableRowNum = ctr;
			break;							/*Breaks out of the for-loop when an available space has been found*/
		}
		else
		{
			availableRowNum = -1;
		}
	}

	return availableRowNum;
}








// ---------------------------------------------------------------------------------- VERTICAL CHECKS --------------------------------------------------------------------//
//This function checks if a vertical 'L' exists anywhere on the board
// INPUT ARGUMENTS:
// aBoard - the board we are checking
// token - stores the character we are checking against
void LCheck_vertical(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck)
{
	int col_winCheck = 0;		//0 - no three-in-a-column for a particular column; 1 - has a three-in-a-column for a particular column
	int startingRow;		// denotes the starting row where a three-in-a-column exists
	int result = 0;				// denotes there is a winner - (i.e. an 'L' is found)
	char player_token = token;	// token of player who last played

								// LEGEND: 
								//ctr1 = COLUMN
								//ctr2 = ROW
	for (int ctr1 = 0; ctr1 < NUM_COLS; ctr1++)			// checking every columns
	{
		// checking for a three-in-a-column
		for (int ctr2 = 0; ctr2 <= NUM_ROWS - 3; ctr2++)
		{
			three_in_a_column(ctr2, ctr1, aBoard, token, &col_winCheck, &startingRow);
			if (col_winCheck == 1)
				break;
		}

		// checking for an 'L' if a three-in-a-column has been detected
		if (col_winCheck == 1)
		{
			baseCheck_vertical(startingRow, ctr1, aBoard, token, &result);
			break;
		}
	}

	*winnerCheck = result;
}


// This function checks if a three-in-a-column exists on the board
// INPUT ARGUMENTS:
// row - the starting row where a three-in-a-column might exists
// col - column to check
// aBoard - the board we are checking
// token - stores the character we are checking against
void three_in_a_column(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * col_winCheck, int * startingRow)
{
	if (((aBoard[row][col] == token) && (aBoard[row + 1][col] == token)) && (aBoard[row + 2][col] == token))		// checking for a three-in-a-column
	{
		*col_winCheck = 1;					// denotes there is a three-in-a-column
		*startingRow = row;			// sets the starting row where a three-in-a-column exists
	}
}



//This function checks if an 'L' exist when a three-in-a-column exists 
// INPUT ARGUMENTS:
// row - the starting row where a three-in-a-column exists
// col - column to check
// aBoard - the board we are checking
// token - stores the character we are checking against
// result - 0 ~ no 'L' exists; 1 ~ 'L' exists
void baseCheck_vertical(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * result)
{
	if ((col != 0) && (col != NUM_COLS - 1))			// checking for an 'L' in columns 2 thru 8
	{
		// 'L' check algorithm
		if (((aBoard[row][col - 1] == token) || (aBoard[row][col + 1] == token)) ||
			((aBoard[row + 2][col - 1] == token) || (aBoard[row + 2][col + 1] == token)))
		{
			*result = 1;
		}
	}
	else if (col == 0)						// checking for an 'L' in column 1
	{
		if ((aBoard[row][col + 1] == token) || (aBoard[row + 2][col + 1] == token))
		{
			*result = 1;
		}
	}
	else if (col == NUM_COLS - 1)						// checking for an 'L' in column 9
	{
		if ((aBoard[row][col - 1] == token) || (aBoard[row + 2][col - 1] == token))
		{
			*result = 1;
		}
	}
}
// ------------------------------------------------------------------------------ END -------------------------------------------------------------------------------------------//






// --------------------------------------------------------------------------- HORIZONTAL CHECKS ---------------------------------------------------------------------------------------//
//This function checks if a horizontal 'L' exists anywhere on the board
// INPUT ARGUMENTS:
// aBoard - the board we are checking
// token - stores the character we are checking against
void LCheck_horizontal(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck)
{
	int row_winCheck = 0;		//0 - no three-in-a-row for a particular row; 1 - has a three-in-a-row for a particular row
	int startingCol;		// denotes the starting column where a three-in-a-row exists
	int result = 0;				// denotes there is a winner (i.e. an 'L' is found)
	char player_token = token;	// token of player who last played

								// LEGEND: 
								//ctr1 = ROW
								//ctr2 = COLUMN
	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)			// checking every columns
	{
		// checking for a three-in-a-row
		for (int ctr2 = 0; ctr2 <= NUM_COLS - 3; ctr2++)
		{
			three_in_a_row(ctr1, ctr2, aBoard, token, &row_winCheck, &startingCol);
			if (row_winCheck == 1)
				break;
		}

		// checking for an 'L' if a three-in-a-row has been detected
		if (row_winCheck == 1)
		{
			baseCheck_horizontal(ctr1, startingCol, aBoard, token, &result);
			break;
		}
	}
	*winnerCheck = result;
}



// This function checks if a three-in-a-row exists on the board
// INPUT ARGUMENTS:
// row - the row to check
// col - the starting column where a three-in-a-row might exist
// aBoard - the board we are checking
// token - stores the character we are checking against
void three_in_a_row(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * row_winCheck, int * startingCol)
{
	if (((aBoard[row][col] == token) && (aBoard[row][col + 1] == token)) && (aBoard[row][col + 2] == token))		// checking for a three-in-a-row
	{
		*row_winCheck = 1;					// denotes there is a three-in-a-row
		*startingCol = col;			// sets the starting column where a three-in-a-row exists
	}
}


//This function checks if an 'L' exist when a three-in-a-column exists 
// INPUT ARGUMENTS:
// row - the row to check
// col - the starting column where a three-in-a-row exists
// aBoard - the board we are checking
// token - stores the character we are checking against
// result - 0 ~ no 'L' exists; 1 ~ 'L' exists
void baseCheck_horizontal(int row, int col, char aBoard[NUM_ROWS][NUM_COLS], char token, int * result)
{
	if ((row != 0) && (row != NUM_ROWS - 1))			// checking for an 'L' in row 2 thru 7
	{
		// 'L' check algorithm
		if (((aBoard[row - 1][col] == token) || (aBoard[row + 1][col] == token)) ||
			((aBoard[row - 1][col + 2] == token) || (aBoard[row + 1][col + 2] == token)))
		{
			*result = 1;
		}
	}
	else if (row == 0)						// checking for an 'L' in row 1
	{
		if ((aBoard[row + 1][col] == token) || (aBoard[row + 1][col + 2] == token))
		{
			*result = 1;
		}
	}
	else if (row == NUM_ROWS - 1)		// checking for an 'L' in row 8
	{
		if ((aBoard[row - 1][col] == token) || (aBoard[row - 1][col + 2] == token))
		{
			*result = 1;
		}
	}
}
// ------------------------------------------------------------------------------ END -------------------------------------------------------------------------------------------//



// ---------------------------------------------------------------------------------- SLOPE CHECKS --------------------------------------------------------------------//
// This function checks for a three-in-a-row with a slope to the right
// INPUT ARGUMENTS: (1) aBoard - the gameboard; (2) token - a player's token to be checked against
//				    (3) slopeRightCol & slopeRightRow denotes the matrix indices where the three-in-a-row starts
// RETURN VALUE: int result - 1 if a three-in-a-row with a slope to the right is found
//							  0 if otherwise
int slopeRight(char aBoard[NUM_ROWS][NUM_COLS], char token, int*slopeRightRow, int*slopeRightCol)
{
	int result = 0;
	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)
	{
		for (int ctr2 = 2; ctr2 < NUM_COLS; ctr2++)
		{
			if (((aBoard[ctr1][ctr2] == token) && (aBoard[ctr1 + 1][ctr2 - 1] == token)) && (aBoard[ctr1 + 2][ctr2 - 2] == token))
			{
				*slopeRightRow = ctr1;
				*slopeRightCol = ctr2;
				result = 1;
				break;
			}
		}
		if (result == 1)
		{
			break;
		}
	}
	return result;
}
// This function checks if there is an 'L' shape with slope to the right
// INPUT ARGUMENTS: (1) aBoard - the gameboard, (2) token - a player's token
//					 (3) winnerCheck - 0 if no slope right 'L's; 1 if ther is an 'L' with slope right
void LCheck_slopeRight(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck)
{
	int slopeRightCol = 0; /* Indicates the Column where the three-in-a-row occured*/
	int slopeRightRow = 0; /* Indicates the row where the three-in-a-row occured*/
	int slopeRightCheck = slopeRight(aBoard, token, &slopeRightRow, &slopeRightCol); /* Getting the coordinates of the first instance of three-in-a-row with slope right*/
	if (slopeRightCheck == 1)
	{
		/* Checks for Slope Right 'L's*/
		if (((aBoard[slopeRightRow - 1][slopeRightCol - 1] == token) || (aBoard[slopeRightRow + 1][slopeRightCol + 1] == token)) ||
			((aBoard[slopeRightRow + 1][slopeRightCol - 3] == token) || (aBoard[slopeRightRow + 3][slopeRightCol - 1] == token)))
		{
			*winnerCheck = 1;
		}
	}
}
// This function checks for a three-in-a-row with a slope to the left
// INPUT ARGUMENTS: (1) aBoard - the gameboard; (2) token - a player's token to be checked against
//				    (3) slopeLeftCol & slopeLeftRow denotes the matrix indices where the three-in-a-row starts
// RETURN VALUE: int result - 1 if a three-in-a-row with a slope to the left is found
//							  0 if otherwise
int slopeLeft(char aBoard[NUM_ROWS][NUM_COLS], char token, int*slopeLeftRow, int*slopeLeftCol)
{
	int result = 0;
	for (int ctr1 = 0; ctr1 < NUM_ROWS; ctr1++)
	{
		for (int ctr2 = 0; ctr2 < NUM_COLS - 2; ctr2++)
		{
			if (((aBoard[ctr1][ctr2] == token) && (aBoard[ctr1 + 1][ctr2 + 1] == token)) && (aBoard[ctr1 + 2][ctr2 + 2] == token))
			{
				*slopeLeftRow = ctr1;
				*slopeLeftCol = ctr2;
				result = 1;
				break;
			}
		}
		if (result == 1)
		{
			break;
		}
	}
	return result;
}
// This function checks if there is an 'L' shape with slope to the left
// INPUT ARGUMENTS: (1) aBoard - the gameboard, (2) token - a player's token
//					 (3) winnerCheck - 0 if no slope left 'L's; 1 if ther is an 'L' with slope left
void LCheck_slopeLeft(char aBoard[NUM_ROWS][NUM_COLS], char token, int*winnerCheck)
{
	int slopeLeftCheck = 0;
	int slopeLeftCol = 0;
	int slopeLeftRow = 0;

	slopeLeftCheck = slopeLeft(aBoard, token, &slopeLeftRow, &slopeLeftCol);
	if (slopeLeftCheck == 1)
	{
		if (((aBoard[slopeLeftRow - 1][slopeLeftCol + 1] == token) || (aBoard[slopeLeftRow + 1][slopeLeftCol - 1] == token)) ||
			((aBoard[slopeLeftRow + 1][slopeLeftCol + 3] == token) || (aBoard[slopeLeftRow + 3][slopeLeftCol + 1] == token)))
		{
			*winnerCheck = 1;
		}
	}
}
