/*
This is a classic Rock Papers Scissors using only 
numbers 1-2-3 for player 1 and 8-9-0 for player 2.

PRESS 5 to quit.


Code written by: TAK'S JOSEPH REFUGIO
Code Written for: Nothing. Just Practicing.
Date code Written: January 2019
*/

#include<stdio.h>
#include<stdlib.h>

typedef enum WIN_STATUS {WIN, LOSE, DRAW};
typedef enum choice {ROCK, PAPER, SCISSORS} TOKEN_CHOICE;

TOKEN_CHOICE choiceChange1(int player1Token) {
	TOKEN_CHOICE player1Choice;
	switch(player1Token)
	{
		case 1:
		player1Choice = ROCK;
		break;

		case 2:
		player1Choice = PAPER;
		break;

		case 3:
		player1Choice = SCISSORS;
		break;
	} 
	return player1Choice;
}

TOKEN_CHOICE choiceChange2(int player2Token) {
	TOKEN_CHOICE player2Choice;
	switch(player2Token)
	{
		case 8:
		player2Choice = ROCK;
		break;

		case 9:
		player2Choice = PAPER;
		break;

		case 0:
		player2Choice = SCISSORS;
		break;
	} 
	return player2Choice;
}
void choiceChangeAll(TOKEN_CHOICE*player1Token, TOKEN_CHOICE*player2Token) {
	player1Token = choiceChange1(player1Token);
	player2Token = choiceChange2(player2Token);
}
void checkTokens(TOKEN_CHOICE playertoken) {
	switch (playertoken)
	{
		case ROCK:
		printf("Player1: ROCK");
		break;

		case PAPER:
		printf("Player1: PAPER");
		break;

		case SCISSORS:
		printf("Player1: SCISSORS");
		break;
	}

	printf("\n");
}

int main()
{
	int token1 = 0;
	int token2 = 0;

	while(token1 != 5 && token2 != 5)
	{
		printf("ROCK PAPERS SCISSORS...Shoot!\n");
		scanf("%d\n", &token1);
		scanf("%d\n", &token2);
		choiceChangeAll(&token1, &token2);

		//FIXME: Continue creating a routine that checks 
		//what each of the players used as tokens
		//to make sure that all of the token assigning routines
		//are working nominally
		checkTokens(token1);
		checkTokens(token2);
	}
	return 0;
}

