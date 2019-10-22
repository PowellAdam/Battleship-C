/*Author: Adam Powell
Exam 2
COP 2220
Professor Hunchuck
2/25/2018

This program is my version of the classic strategy game, "Battleship"
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define PAUSE system("pause")
#define CLEAR system("cls")
#define ROW 10
#define COL 10
#define WAIT Sleep(1000)


//FUNCTION PROTOTYPES
void viewScores(FILE *a, int *score);
void introScreen();
char getChoice();
void loadScores(int *score, FILE *f);
void menu();
void myFlush();
void displayBoard(char arr[][COL], char boats[][COL]);
void playGame(char arr[][COL], char boats[][COL], int *score);
void randomlyPlaceShip(char a[][COL], int size, char type);
void rules();
void title();

main() { // This is the main function
	FILE *fp;// for ascii art file
	char userBoard[ROW][COL] = { { '*' } };
	char ships[ROW][COL] = { { 0 } };

	int *score;
	char choice;
	int count = 0;
	char c = 0;
	FILE *f;//scores file
	srand(time(NULL));// seed the random function just once
	introScreen();
	score = 0;
	
	
	do {
		title();
		menu();

		choice = getChoice();
		switch (choice) {
		case 'A'://PLAY GAME

			for (int i = 0; i < ROW; i++) {//initializes the boat array
				for (int j = 0; j < COL; j++) {
					ships[i][j] = 0;

				}
			}

			//place aircraft carrier
			randomlyPlaceShip(ships, 5, 'A');

			//place the battleship
			randomlyPlaceShip(ships, 4, 'B');

			// place the submarine
			randomlyPlaceShip(ships, 3, 'S');

			//place the cruiser
			randomlyPlaceShip(ships, 3, 'C');

			//place the destroyer
			randomlyPlaceShip(ships, 2, 'D');

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {// sets all places that arent occupied to '*'
					if (ships[i][j] == '\0')
						ships[i][j] = '*';
				}//end inner for loop
			}//end outer for loop
			for (int i = 0; i < ROW; i++) {//ititializes user board
				for (int j = 0; j < COL; j++) {
					userBoard[i][j] = '*';
				}//end inner for loop
			}// end outer for loop

			displayBoard(userBoard, ships);
			playGame(userBoard, ships, &score);//
			loadScores(&score, &f);//CHECKS FOR HIGH SCORE AT THE END OF GAME
			
			break;
		case 'B'://HIGH SCORES
			CLEAR;
			title();
			viewScores(&f, &score);
			break;
		case 'C'://HOW TO PLAY
			rules();
			break;
		case 'D'://VIEW THE HOME SCREEN AGAIN
			CLEAR;
			introScreen();
			PAUSE;
			break;
		case'Q'://Quit
			CLEAR;
			printf("\n\n\n\t\t\t\t\tBYE BYE THANK YOU FOR PLAYING");
			WAIT;
			WAIT;
			break;
		default://IN CASE OF USER ERR
			printf("\n\t\t\t\t\tInvalid Selection, try again...\n");
			WAIT;
			WAIT;
			CLEAR;
			break;
		}

	} while (choice != 'Q');// end of do/while

}//end main()

void viewScores(FILE *f, int *score) {
	double size;
	int scoresA[11];
	char nameSpot[11][20] = { ' ' };


	f = fopen("score.bin", "r");
	if (f == NULL) {
		printf("\nNo high scores exists!\n\n");
		PAUSE;
		exit(-1);
	}
	else {
		printf("\n\t\t\t\t\t\t\t\t  TOP 10 HIGH SCORES\n");
		printf("\n\t\t\t\t\t\t\t\t  ==================\n\n");
		WAIT;
		
		fread(nameSpot, sizeof(char[11][20]), 1, f);
		fread(&scoresA, sizeof(int[11]), 1, f);

		for (int i = 0; i < 10; i++) {

			printf("\n\t\t\t\t\t\t\t\t   %i. %s\t %i \n\n", i + 1, nameSpot[i], scoresA[i]);
		}
	} // end else 
	fclose(f);
	printf("\t\t\t\t\t\t\t\t"); PAUSE;
}//end of createFile()


void displayBoard(char arr[][COL], char boats[][COL]) {//THE BIG SCREEN

	title();
	printf("\n\t\t\t\t\t    1  \t    2\t    3 \t    4  \t    5  \t    6  \t    7  \t    8  \t    9  \t    10\n");
	printf("\t\t\t\t-----------------------------------------------------------------------------------------\n");

	for (int i = 0; i < COL; i++) {


		switch (i) {
		case 0:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[A]    |");
			break;
		case 1:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[B]    |");
			break;
		case 2:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[C]    |");
			break;
		case 3:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[D]    |");
			break;
		case 4:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[E]    |");
			break;
		case 5:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[F]    |");
			break;
		case 6:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[G]    |");
			break;
		case 7:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[H]    |");
			break;
		case 8:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[I]    |");
			break;
		case 9:
			printf("\n\t\t\t\t       |\n");
			printf("\t\t\t\t[J]    |");
			break;

		}

		for (int j = 0; j < COL; j++) {
			printf("    %c\t", arr[i][j]);
		}//end inner for loop
	}//end outer for loop
	printf("\n\n\t\t\t");
}//end displayBoard()

char getChoice() {//gets user input (a char) from main menu and makes sure letter is uppercase.

	char result = 0;
	
	scanf("%c", &result);
	myFlush();
	
	result = toupper(result);

	return result;

}//end getChoice();

void introScreen() {//ascii art intro to get your blood pumping!  I designed all but the ship.  Ship was posted on https://www.ascii-code.com/ascii-art/vehicles/navy.php by Matthew Base
	FILE *intro;
	int c;
	title();
	intro = fopen("battleshipIntro.txt", "r");
	if (intro) {
		while ((c = getc(intro)) != EOF)
			putchar(c);
	}
	;//waits one second
	WAIT;//and another second (to mimic loading of old games)

	fclose(intro);
	printf("\t\t\t\t\t\t\t");
	PAUSE;
	CLEAR;

}//end of introScreen()

void menu() {//main menu
	printf("\t\t\t\t\t\t\t\t      [A] Play Game\n\n");
	printf("\t\t\t\t\t\t\t\t      [B] High Scores\n\n");
	printf("\t\t\t\t\t\t\t\t      [C] How to Play\n\n");
	printf("\t\t\t\t\t\t\t\t      [D] View the Intro Screen\n\n");
	printf("\t\t\t\t\t\t\t\t      [Q] Quit (Scores Save Automatically)\n\n");
	printf("\n\t\t\t\t\t\t\t\t     Enter Selection: ");
}//end menu()


void myFlush() {//clears the buffer
	char nothing;
	while (scanf("%c", &nothing) == NULL);
}//end myFlush

void playGame(char arr[][COL], char boats[][COL], int *score) {//Meat and Potatoes of the Game
	////Variables
 
	int temp = 0;
	char letter = 0;
	int number = 0;
	int letterNum = 0;
	int aFlag = 0, aircraft = 0;
	int bFlag = 0, battleship = 0;
	int cFlag = 0, cruiser = 0;
	int sFlag = 0, submarine = 0;
	int dFlag = 0, destroyer = 0;
	int downedShips = 0;
	int chFlag, numFlag;
	int boardFlag[10][10] = { 0 };
	char shipChar = ' ';
	for (int i = 0; i < 10; i++) {// populates array
		for (int x = 0; x < 10; x++) {
			boardFlag[i][x] = 0; 
		}
	}

	do {

		char shipChar = ' ';
		chFlag = 0;
		numFlag = 0;
		letter = ' ';

				do {
					printf("\t\t\t\t\t    MISSILES LAUNCHED: %i\t    \n \t\t\t\t\t\t  BOATS SUNK..       AIRCRAFT CARRIER: %i      BATTLESHIP: %i\n   \t\t\t\t\t\t           CRUISER: %i   SUBMARINE: %i\tDESTROYER: %i\n\n", *score, aFlag, bFlag, cFlag, sFlag, dFlag);
					printf("\n\t\t\t\t Enter the Letter cordinate followed by a space, and then number: ");
				do{
				
					scanf("%c%i", &letter, &number);
			
				} while (letter == 0 || letter < 65 || letter > 120 || number < 1 || number > 10 );
				//use getch and cacantinate it instead of scanf
				letter = toupper(letter);
				*score = *score + 1;

				switch (letter) {

				case 'A':
					letterNum = 0;
					chFlag = 1;
					break;
				case 'B':
					letterNum = 1;
					chFlag = 1;
					break;
				case 'C':
					letterNum = 2;
					chFlag = 1;
					break;
				case 'D':
					letterNum = 3;
					chFlag = 1;
					break;
				case 'E':
					letterNum = 4;
					chFlag = 1;
					break;
				case 'F':
					letterNum = 5;
					chFlag = 1;
					break;
				case 'G':
					letterNum = 6;
					chFlag = 1;
					break;
				case 'H':
					letterNum = 7;
					chFlag = 1;
					break;
				case 'I':
					letterNum = 8;
					chFlag = 1;
					break;
				case 'J':
					letterNum = 9;
					chFlag = 1;
					break;
				default:
					printf("\n\t\t\tProper Letter not entered. retry.");

					break;
				}

				number = number - 1;
				//IF STATMENT BELOW WILL TRACK WHICH CORDINATES HAVE BEEN HIT ALREADY AND PREVENT USER FROM HITTING TWICE
				if (boardFlag[letterNum][number] == 0) {
					boardFlag[letterNum][number] = 1;
				}
				else {
					printf("\n\t\t\t\tYou either already hit that spot or shot off the map, try again.\n");
					*score = *score - 1;
					WAIT; WAIT; WAIT;
					CLEAR;
					displayBoard(arr, boats);
					chFlag = 0;
					continue;
				}//end of if else

				switch (number) {
				case 0:
					numFlag = 1;
					break;
				case 1:
					numFlag = 1;
					break;
				case 2:
					numFlag = 1;
					break;
				case 3:
					numFlag = 1;
					break;
				case 4:
					numFlag = 1;
					break;
				case 5:
					numFlag = 1;
					break;
				case 6:
					numFlag = 1;
					break;
				case 7:
					numFlag = 1;
					break;
				case 8:
					numFlag = 1;
					break;
				case 9:
					numFlag = 1;
					break;
				default:
					printf("\n\t\t\tProper Digit not entered. retry.");

					break;
				}//end of switch
			} while (numFlag != 1 && chFlag != 1);

			if (boats[letterNum][number] != '*') {
				printf("\n\t\t\t\t\t\tDIRECT HIT!!\n\n");
				shipChar = boats[letterNum][number];
				arr[letterNum][number] = 'H';
			}
			else {
				printf("\n\t\t\t\t\t\tMISS!!\n");
				arr[letterNum][number] = 'M';
			}

			switch (shipChar) {
			case 'A'://aircraft carrier
				aircraft += 1;
				if (aircraft == 5) {
					printf("\n\t\t YOU SUNK THE AIRCRAFT CARRIER!!!\n\n");
					for (int i = 0; i < ROW; i++) {
						for (int j = 0; j < COL; j++) {
							if (boats[i][j] == 'A')
								arr[i][j] = 'A';
						}
					}
					aFlag = 1;
					downedShips += 1;
					WAIT;
				}
				break;
			case 'B'://battleship
				battleship += 1;
				if (battleship == 4) {
					printf("\n\t\t YOU SUNK THE BATTLESHIP!!!\n\n");
					for (int i = 0; i < ROW; i++) {
						for (int j = 0; j < COL; j++) {
							if (boats[i][j] == 'B')
								arr[i][j] = 'B';
						}
					}
					bFlag = 1;
					downedShips += 1;
					WAIT;
				}
				break;
			case 'C'://cruiser
				cruiser += 1;
				if (cruiser == 3) {
					printf("\n\t\t YOU SUNK THE CRUISER!!!\n\n");
					for (int i = 0; i < ROW; i++) {
						for (int j = 0; j < COL; j++) {
							if (boats[i][j] == 'C')
								arr[i][j] = 'C';
						}//end inner for loop
					}//end outer for loop
					cFlag = 1;
					downedShips += 1;
					WAIT;
				}//end if
				break;
			case 'D'://destroyer
				destroyer += 1;
				if (destroyer == 2) {
					printf("\n\t\t YOU SUNK THE DESTROYER!!!\n\n");
					dFlag = 1;
					downedShips += 1;
					for (int i = 0; i < ROW; i++) {
						for (int j = 0; j < COL; j++) {
							if (boats[i][j] == 'D')
								arr[i][j] = 'D';
						}//end inner for
					}//end outer for
					WAIT;
				}//end if
				break;
			case 'S'://submarine
				submarine += 1;
				if (submarine == 3) {
					printf("\n\t\t YOU SUNK THE SUBMARINE!!!\n\n");
					for (int i = 0; i < ROW; i++) {
						for (int j = 0; j < COL; j++) {
							if (boats[i][j] == 'S')
								arr[i][j] = 'S';
						}//end inner for
					}//end outer for
					sFlag = 1;
					downedShips += 1;
					WAIT;
				}//end if
				break;

			}//end switch

			if (downedShips == 5) {
				printf("\n\n\y\t\t\t\t\YOU WIN!!! YOUR SCORE IS: %i\n\n", *score);
				PAUSE;
			}//end if

			//wait 3 seconds 

			WAIT;
			WAIT;
			CLEAR;
			displayBoard(arr, boats);
		
	} while (downedShips != 5);//end do/while loop
}//end of playGame()

void randomlyPlaceShip(char a[][COL], int size, char type) {//ensures ships fit on board without overlap
	int i = 0, j = 0;
	int coinFlip = 0;
	int size1 = size;
	int sizeTemp = size;
	int placeSet = 0;

	do {
		i = rand() % ROW;
		j = rand() % COL;
		sizeTemp = size;
		placeSet = 0;
		coinFlip = rand() % 4; //4 sided coin decides the direction to attempt to face the ship

		switch (coinFlip) {
		case 0://horizontal and to the left try
			size1 = sizeTemp;
			for (sizeTemp; sizeTemp >= 0; sizeTemp--) {
				if (j < sizeTemp || a[i][j - sizeTemp] != 0) {
					placeSet = -1;
					break;
				}//end if
			}//end for
			if (placeSet == -1) {
				continue;
			}//end if
			for (size1 -= 1; size1 >= 0; size1--) {
				a[i][j - size1] = type;
			}//end for
			break;

		case 1://horizontal and to the right try
			size1 = sizeTemp;
			for (sizeTemp; sizeTemp >= 0; sizeTemp--) {
				if ((j + sizeTemp) > COL || a[i][j + sizeTemp] != 0) {
					placeSet = -1;
					break;
				}
			}
			if (placeSet == -1) {
				continue;
			}
			for (size1 -= 1; size1 >= 0; size1--) {
				a[i][j + size1] = type;
			}
			break;

		case 2://vertical descending try
			size1 = sizeTemp;
			for (sizeTemp; sizeTemp >= 0; sizeTemp--) {
				if ((i + sizeTemp) > ROW || a[i - sizeTemp][j] != 0) {
					placeSet = -1;
					break;
				}
			}
			if (placeSet == -1) {
				continue;
			}
			for (size1 -= 1; size1 >= 0; size1--) {
				a[i - size1][j] = type;
			}
			break;

		case 3:	//vertical ascending try
			size1 = sizeTemp;
			for (sizeTemp; sizeTemp >= 0; sizeTemp--) {
				if (i < sizeTemp || a[i + sizeTemp][j] != 0) {
					placeSet = -1;
					break;
				}//end if
			}//end for
			if (placeSet == -1) {
				continue;
			}//end if
			for (size1 -= 1; size1 >= 0; size1--) {
				a[i + size1][j] = type;
			}//end for
			break;

		}//end of switch

		placeSet = 1;
	} while (placeSet != 1);//end of do/while loop

	//printf("Direction: %d\n", coinFlip); //use if you want console to show the cordinates where ships where placed
	//printf("At {%d, %d}\n", i, j);      //was very effective during testing!
}//end randomlyPlaceShip()

void rules() {//Breif Explanation on how to Play
	CLEAR;
	title();
	printf("\n\n\n\t\t\t\t\tUse the board to try and guess where ships have been randomly placed...\n");
	printf("\n\n\t\t\t\t\tFire missiles at desired coordinates by entering the letter and then the number \n");
	printf("\n\n\t\t\t\t\tof the desired location.  The object of the game is to sink all 5 ships while \n");
	printf("\n\n\t\t\t\t\tfiring the least amount of missiles.  Try to earn a spot on the leader board!\n\n\n\t\t\t\t\t\t");
	WAIT;
	WAIT;
	PAUSE;
	CLEAR;

}//end of rules()

void title() {
	CLEAR;
	printf("\n\n\t\t      ============================================================================================================\n");
	printf("\t\t      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~            BATTLESHIP             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t\t      ============================================================================================================\n\n");
}// end title()


void loadScores(int *score, FILE *f) {
	char name[20] = { ' ' };
	char names[11][20] = { ' ' };
	int scores[11] = { 100,100,100,100,100,100,100,100,100,100,100 } ;
	int num = 1;
	int temp = 0;
	char tempName[20];
	double size;
	/*for (int i = 0; i < 11; i++) {
		int number = 72;
		score = number;
	}*/

	f = fopen("score.bin", "ab+");
	if (f == NULL) {
		printf("\nError! Could not open file!\n\n");
		PAUSE;

		exit(-1);
	}
	else {
		printf("Output file opened!\n");

		fread(names, sizeof(char[11][20]), 1, f);
		fread(scores, sizeof(int[11]), 1, f);
		fseek(f, 0, SEEK_SET);//ENSURES FILE IS READ AT SPECIFIC LOCATION(BEGINNING)
		fclose(f);
		PAUSE;
	} // end else 

	if (*score <= scores[10]) {
		printf("\t\tEnter your name: \n\t\t\t\t");

		scanf("%s", name);

		scores[10] = *score;
		strcpy(names[10], name);
	}

	for (int pass = 9; pass > 0; pass--) {  //bubble sort scores
		for (int i = 10; i > 0; i--) {
			if (scores[i] < scores[i - 1]) {
				temp = scores[i];
				strcpy(tempName, names[i]);
				scores[i] = scores[i - 1];

				strcpy(names[i], names[i - 1]);

				scores[i - 1] = temp;

				strcpy(names[i - 1], tempName);
			}

		}
	}

	f = fopen("score.bin", "w+");
	if (f == NULL) {
		printf("\nError! Could not open file!\n\n");
		PAUSE;
		exit(-1);
	}
	else {
		printf("Output file opened!\n");
		fwrite(names, sizeof(char[11][20]), 1, f);
		fwrite(scores, sizeof(int[11]), 1, f);

		printf("\t\t\t\t\t\t\tLEADER BOARD\n\n");
		for (int i = 0; i < 11; i++) {
			if(scores[i] > 17 && scores[i] < 101)
			printf("\t\t\t\t\t\t\t%i. %s %i\n\n", num++, names[i], scores[i]);
		}

		fclose(f);
		PAUSE;
	} // end else 
} //end of loadScores()