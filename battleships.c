/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	/*run through the 2D array, printing each values*/
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("%d ", values[i][j]);
		}
		printf("\n");
	}
	//values[0][0] = 0; // to prevent compiler warning (you must complete this function)
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	/*Ship 2*/
	map[0][0] = 2;
	map[1][0] = 2;

	/*Ship 3*/
	map[2][1] = 3;
	map[2][2] = 3;
	map[2][3] = 3;

	/*Ship 4*/
	map[MAP_SIZE - 1][0] = 4;
	map[MAP_SIZE - 1][1] = 4;
	map[MAP_SIZE - 1][2] = 4;
	map[MAP_SIZE - 1][3] = 4;

	/*Ship 5*/
	map[MAP_SIZE - 1][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 2][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 3][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 4][MAP_SIZE - 1] = 5;
	map[MAP_SIZE - 5][MAP_SIZE - 1] = 5;
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int col;
	int row;
	int dir;

	/* direction - vertical or horizontal*/
	/* 1 = vertical and 0 = horizontal*/
	dir = rand() % 2;


	/* HEAD of the ship - the first coordinate*/

	if (dir == 1) {
		col = (rand() % MAP_SIZE);
		row = (rand() % (MAP_SIZE - (size - 1)));
		for (int i = 0; i < size; i++) {
			map[col][row + i] = size;
		}

	}
	else if (dir == 0) {
		col = (rand() % (MAP_SIZE - (size - 1)));
		row = (rand() % MAP_SIZE);
		for (int j = 0; j < size; j++) {
			map[col + j][row] = size;
		}
	}

}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int count = 0;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == value) {
				count++;
			}
		}
	}

	return count;
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				*col = j;
				*row = i;

				if (map[*row][*col + 1] == size) {
					return 1;
				}
				else if (map[*row + 1][*col] == size) {
					return 2;
				}

			}
		}
	}

	return 0;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int dir;
	int row;
	int col;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				row = i;
				col = j;

				/*horizontal or vertical*/
				if (map[row][col + 1] == size) {
					dir = 1;
				}
				else if (map[row + 1][col] == size) {
					dir = 2;
				}

				break;
			}
		}
	}

	/*Checking if the ship goes outside the grid*/
	/*if horizontal*/
	if (dir == 1) {
		if ((col + size) > (MAP_SIZE - 1)) {
			return 0;
		}
		/*if vertical*/
	}
	else if (dir == 2) {
		if ((row + size) > (MAP_SIZE - 1)) {
			return 0;
		}
	}


	/*Checking for overlapping and adjacent*/
	/*if horizontal*/
	if (dir == 1) {

		for (int k = 0; k < size; k++) {
			if ((row > 0) && (map[row - 1][col + k] != 0)) {
				return 0;
			}
			if ((row < (MAP_SIZE - 1)) && (map[row + 1][col + k] != 0)) {
				return 0;
			}
		}


		if (map[row][col - 1] != 0) {
			return 0;
		}


		if (map[row][col + size] != 0) {
			return 0;
		}

		/*if vertical*/
	}
	else if (dir == 2) {

		for (int k = 0; k < size; k++) {
			if ((col > 0) && (map[row + k][col - 1] != 0)) {
				return 0;
			}
			if ((col < (MAP_SIZE - 1)) && (map[row + k][col + 1] != 0)) {
				return 0;
			}
		}

		if (map[row - 1][col] != 0) {
			return 0;
		}


		if (map[row + size][col] != 0) {
			return 0;
		}

	}


	return 1;
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	int valid2 = 0;
	int valid3 = 0;
	int valid4 = 0;
	int valid5 = 0;

	while ((valid2 == 0) || (valid3 == 0) || (valid4 == 0) || (valid5 == 0)) {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				map[i][j] = 0;
			}
		}

		AddRandomShip(5, map);
		valid5 = IsShipValid(5, map);

		AddRandomShip(4, map);
		valid4 = IsShipValid(4, map);

		AddRandomShip(3, map);
		valid3 = IsShipValid(3, map);

		AddRandomShip(2, map);
		valid2 = IsShipValid(2, map);

		if ((valid2 == 1) && (valid3 == 1) && (valid4 == 1) && (valid5 == 1)) {
			break;
		}
	}
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int count = 0;
	int hit = 1;
	int size;

	if (shots[row][col] == 0) {

		/*count the number of shots*/
		int numshots = 1;
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				if (shots[i][j] != 0) {
					numshots++;
				}
			}
		}

		printf("value at map: %d ", map[row][col]);
		printf("value at shots: %d ", shots[row][col]);

		/*if missed*/
		if (map[row][col] == 0) {
			shots[row][col] = numshots;
			hit = 5;
		}
		else {
			size = map[row][col];

			/*Count the number of hits*/
			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					if (map[i][j] == size) {
						if (shots[i][j] != 0) {
							count++;
						}
					}
				}
			}
			/*If last element of the ship hit = destroyed*/
			if (count == (size - 1)) {
				hit = 0;
			}

		}

		if (hit == 1) {
			shots[row][col] = numshots + 1000;
		}
		else if (hit == 0) {

			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					if (map[i][j] == size) {
						shots[i][j] = ((shots[i][j]) % 1000) + (size * 1000);
					}
					if ((shots[i][j] % 1000 == 0) && (map[i][j] == size)) {
						shots[i][j] = numshots + (size * 1000);
					}
				}
			}
		}

	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	int size;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; i < MAP_SIZE; i++) {
			if (map[i][j] != 0) {
				size = map[i][j];
				if (shots[i][j] < (1000 * size)) {
					return 0;
				}
			}


		}
	}

	return 1;

}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













