/*Tick Tack Toe
Mathias Jönsson

Player = 1, PC = 2*/

/*GENERAL STUFF TO FIX, CHECK BEFORE 1.0

# Maybe display table more often ?
# Change display of 1 and 0 to |X| | | |O| (easier on the eye, might not be neccessary)
# Add actual win condition checking
# PC sometimes doesn't add to board (board detection related maybe)
# Players choice doesn't get added after re-selection post duplicate placement detection. Related to PC not adding after similar
# PC and Player not getting rounds is due to IF-ELSE loop. Use while maybe ?
# Switch Column and Row placement in re-enter placement to match overall structure. Now they are the wrong way around (Column first instead of reverse)


*/

#include <stdio.h>
#include <stdlib.h>
#define BOARDSIZE 3											/*To allow for possible scaling. Not sure if going to be implemented*/

int XOSelection();											/*Player selects weapon. X = 1, O = 2*/
int RowSelection();		
int ColumntSelection();
int DisplayBoard();

int main(void)
{
	unsigned Seed;
	Seed = (unsigned)time(NULL);							/*RNG for computer opponents selections*/
	srand(Seed);

	int RunCount = 0;										/*Counts numbers of rounds, ends when board filled (at 9)*/
	int Win = 0;											/*Win condition yay or nay*/

	int PlayerSelection = 0;								/*Exit condition for progam if 2, ask after game*/
	int PlayerWeapon, Row, Column, Counter1, Counter2;		/*Player weapon choice. 1 for X, 2 for O*/
	
	int Board[BOARDSIZE][BOARDSIZE] = { 0 };				/*Play board (Also Array)*/
	
	while (PlayerSelection != 2)							/*Run until player selects 2 to exit after a round*/
	{								
		PlayerWeapon = XOSelection();						/*Set players weapon to X or O depending on selection from XOSelection()*/
		
		while (RunCount <= 4 || Win==1)						/*Run until board is filled or a winner is found*/
		{

			DisplayBoard(Board);							/*Display the current state of the board*/
			Row = RowSelection();							/*Run function for player row selection*/
			Column = ColumnSelection();						/*Run function for player column selection*/						
			
			if (Board[Row][Column] == 1 || Board[Row][Column] == 2)		/*Checks if slot is taken ether by player or PC*/
			{
				printf("\nERROR: Slot taken, Select a new slot\n");	
				Column = ColumnSelection();
				Row = RowSelection();
			}
			if (Board[Row][Column] == 0 )
			{
				Board[Row][Column] = 1;							/*Set players slot choice to 1*/
			}

			int PCRow = (rand() % 3);							/*Set PC row choice to something between 1 and 3*/
			int PCColumn = (rand() % 3);						/*Set PC column choice to something between 1 and 3*/

			if (Board[PCRow][PCColumn] == 1 || Board[PCRow][PCColumn] == 2)		/*Checks if selected slot is already taken, runs RNG again to find free slot*/
			{
				printf("\n\n**PC has selected a filled slot, will run again**\n\n");	/*DEBUG, REMOVE BEFORE 1.0*/
				int PCRow = (rand() % 3);						/*Set PC row choice to something between 1 and 3*/
				int PCColumn = (rand() % 3);					/*Set PC column choice to something between 1 and 3*/
				printf("Row %d", PCRow);							/*DEBUG, REMOVE BEFORE 1.0*/
				printf("Column %d", PCColumn);							/*DEBUG, REMOVE BEFORE 1.0*/
			}
			if (Board[PCRow][PCColumn] == 0)
			{
				Board[PCRow][PCColumn]=2;					/*Set PC slot choice to 2*/
			}
			RunCount++;										/*Increase count one step closer to max (9)*/
		}
		printf("\n\nGame has ended\n\n");
		DisplayBoard(Board);
		printf("\n\nPress 1 to play again\nPress 2 to exit\n");
		scanf_s("%d", &PlayerSelection);
	}
	return 0;												/*That's all folks*/
}

int PlayerSelection(void)									/*Player input function*/
{
	int PSelect;
	printf("\nGame board placements. Select your placement. Enter 10 to exit");
	printf("\n1 2 3\n4 5 6\n7 8 9\n\n");
	scanf_s("%d", &PSelect);
	if (PSelect<1 || PSelect>10)							/*Make sure number is within range*/
	{
		printf("\nERROR: Select valid placement\nEnter a new number\n");
		scanf_s("%d", &PSelect);
	}
	else
	{
		return PSelect;										/*If valid, return number to Main()*/
	}
}

int DisplayBoard(int Board[BOARDSIZE][BOARDSIZE])			/*Allow for board expansion using #define values*/
{
	int Counter1, Counter2;
	printf("\nCurrent Board:\n");
	for (Counter1 = 0; Counter1 < BOARDSIZE; Counter1++)	/*Print board*/
	{															
		for (Counter2 = 0; Counter2 < BOARDSIZE; Counter2++)	/*Runs every 3 rounds to make the print "step down"*/
		{
			printf(" %d ", Board[Counter1][Counter2]);
		}
		printf("\n");										/*Step down one row for each 3 columns read. Creates the nice 3x3 board*/
	}
}

int XOSelection(void)										/*Player selects to play as X or O*/
{
	int PlayerWeapon;
	printf("\nWhat do you want to play as ? \nX = 1, O = 2\n");
	scanf_s("%d", &PlayerWeapon);
	
	while (PlayerWeapon != 1 || PlayerWeapon != 2)			/*Run while valid weapon isn't selected*/
	{
		if (PlayerWeapon == 1 || PlayerWeapon == 2)		/*Break and return value when valid is entered*/
		{
			break;
		}
		else
		{
			printf("ERROR: Select valid choice\n");		/*Return error as normal if the value isn't allowed*/
			scanf_s("%d", &PlayerWeapon);
		}
	}
	return PlayerWeapon;								/*Back to main we go*/
}

int RowSelection(void)
{
	int Pass = 0, Row = 0;		
	while (Pass != 1)									/*While value representing valid choice isn't 1, run loop*/
	{
		printf("Select Row:");
		scanf_s("%d", &Row);

		if (Row<1 || Row >3)							/*Check for valid row choice, display error if needed*/
		{
			printf("ERROR: Select valid row");
		}
		else
		{		
			Pass = 1;									/*Represents a valid row choice (1 is valid, anything else is not). Used to control the while loop*/
		}
	}
	return Row-1;										/*Adjust for array starting at 0 and then back to main*/
}

int ColumnSelection(void)								/*Same as RowSeleciton, See it*/
{
	int Pass = 0, Column = 0;
	while (Pass != 1)
	{
		printf("Select Column:");
		scanf_s("%d", &Column);

		if (Column<1 || Column >3)
		{
			printf("ERROR: Select valid Column");
		}
		else
		{
			Pass = 1;
		}
	}
	return Column-1;									/*Adjust for array starting at 0 and then back to main*/
}	


