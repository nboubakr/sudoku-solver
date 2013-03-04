#include <stdio.h>		/* Standard Library of Input and Output */
#include <stdlib.h>		/* Standart Library for System */
#include <stdbool.h>	/* Standard Library of Bool */
#include <ctype.h>		/* Manipulation with characters */
#include <string.h>		/* Manipulation with strings */

// Filename: main.c

// The Sudoku Solver
// University of Djillali Liabes (UDL) - Sidi Bel Abbes
// Faculty of Sciences - Computer Science (LMD1) 2011/2012 
// Professeur: Mr. HAMRI Mohamed Mahdi
// Student: Boubakr NOUR <n.boubakr@gmail.com>

// License: Academic Free License (AFL)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// THE BASIC FUNCTIONS /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/*
	Type:		Procedure
	Objet:		Clear the terminal using Processus works on MacOS, *Unix, Windows
*/

void clear() {
	#if defined __APPLE__ || defined linux
		system("clear");
	#elif defined(WIN32) || defined(WIN64)
		system("cls");
	#endif
}

/*
	Type:		Procedure
	Objet:		Print the content of a file
	Arguments:	file: Target file
*/
void read_file(FILE *file) {
	char ch;

	while((ch = fgetc(file)) != EOF)
		printf("%c", ch);

	fclose(file);
}

/*
	Type:		Procedure
	Objet:		Display the main menu
*/
void main_menu(void) {
	clear();
	printf("\n\t| * * * * * * WELCOME TO THE SUDOKU SOLVER * * * * * * |\n");
	printf("\t ______________________ MAIN MENU _____________________ \n");
	printf("\t|                                                      |\n");
	printf("\t|                                                      |\n");
	printf("\t|    (*) To solve a Sudoku, Press <S>                  |\n");
	printf("\t|    (*) To quit the Sudoku, Press <Q>                 |\n");
	printf("\t|                                                      |\n");
	printf("\t|______________________________________________________|\n");
}

/*
	Type:		Procedure
	Objet:		Display solver menu choice
*/
void solve_menu(void) {
	clear();
	printf("\n\t ___________________ SELECT A CHOICE __________________ \n");
	printf("\t|                                                      |\n");
	printf("\t|                                                      |\n");
	printf("\t|    (*) To fill your own grid, Press (1)              |\n");
	printf("\t|    (*) To load a grid from a file, Press (2)         |\n");
	printf("\t|                                                      |\n");
	printf("\t|______________________________________________________|\n");
}

/*
	Type:		Procedure
	Objet:		Display the quit message
*/
void quit(void) {
	clear();
	printf("\n\t#######################################################\n");
	printf("\t#                                                     #\n");
	printf("\t#       THANK YOU FOR USING THIS PROGRAM !            #\n");
	printf("\t#       ----------------------------------            #\n");
	printf("\t#                                                     #\n");
	printf("\t#   University of Djillali Liabes - UDL               #\n");
	printf("\t#                                                     #\n");
	printf("\t#   Sidi Bel Abbes 2012/2013                          #\n");
	printf("\t#                                                     #\n");
	printf("\t#   Professeur: Mr. HAMRI Mohamed Mahdi               #\n");
	printf("\t#                                                     #\n");
	printf("\t#   Student: Boubakr NOUR                             #\n");
	printf("\t#                                                     #\n");
	printf("\t#######################################################\n");
	

}

/*
	Type:		Procedure
	Objet:		Display Error message
	Arguments:	msg: Error's message content
*/
void error(char msg[255]) {
	FILE* error_file = fopen("error", "r");;		// error file
	
	clear();
	read_file(error_file); 	// Read the error file
	printf(msg);
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// THE SUDOKU FUNCTIONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/*

	Typical Grid:

	+----------+----------+----------+
	| A1 A2 A3 | A4 A5 A6 | A7 A8 A9 |
	| B1 B2 B3 | B4 B5 B6 | B7 B8 B9 |
	| C1 C2 C3 | C4 C5 C6 | C7 C8 C9 |
	| ---------+----------+----------+
	| D1 D2 D3 | D4 D5 D6 | D7 D8 D9 |
	| E1 E2 E3 | E4 E5 E6 | E7 E8 E9 |
	| F1 F2 F3 | F4 F5 F6 | F7 F8 F9 |
	| ---------+----------+----------+
	| G1 G2 G3 | G4 G5 G6 | G7 G8 G9 |
	| H1 H2 H3 | H4 H5 H6 | H7 H8 H9 |
	| I1 I2 I3 | I4 I5 I6 | I7 I8 I9 |
	+----------+----------+----------+

*/

int Grid[9][9];			// Original Grid
int outputGrid[9][9];	// Solved Grid

/*
	Type:		Function
	Objet:		Check a value in the row, column and region
	Arguments:	row: Check on this row
				column: Check on this column
				value: Cheking this value
	Return:		0: If the value is repeated on the row, column or on the region
				value: else
*/
int inputValue(int row, int column, int value) {
	int i, j;
	
	// Scan each row and column
	for(i = 0; i < 9; i++) {
		if((value == outputGrid[i][column]) || (value == outputGrid[row][i])) {
			return 0;
		}
	}

	// Scan all region
	if(row < 3) {	// 1st three regions

		if(column < 3) {	// Scan the 1st region: A1 ~ C3
			for(i = 0; i < 3; i++) {
				for(j = 0; j < 3; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else if(column < 6) {		// Scan the 2nd region: D1 ~ F3
			for(i = 0; i < 3; i++) {
				for(j = 3; j < 6; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else {	// Scan the 3rd region: G1 ~ I3
			for(i = 0; i < 3; i++) {
				for(j = 6; j < 9; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		}
	
	} else if(row < 6) {	// 2nd three regions
		
		if(column < 3) {	// Scan the 1st region: A4 ~ C6
			for(i = 3; i < 6; i++) {
				for(j = 0; j < 3; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else if(column < 6) {	// Scan the 2nd region: D4 ~ F6
			for(i = 3; i < 6; i++) {
				for(j = 3; j < 6; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else {		// Scan the 3rd region: G4 ~ I6
			for(i = 3; i < 6; i++) {
				for(j = 6; j < 9; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		}
	
	} else {	// 3rd three regions

		if(column < 3) {	// Scan the 1st region: A7 ~ C9
			for(i = 6; i < 9; i++) {
				for(j = 0; j < 3; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else if(column < 6) {		// Scan the 2nd region: D7 ~ F9
			for(i = 6; i < 9; i++) {
				for(j = 3; j < 6; j++) {
					if (value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		} else {	// Scan the 3rd region: G7 ~ I9
			for(i = 6; i < 9; i++) {
				for(j = 6; j < 9; j++) {
					if(value == outputGrid[i][j]) {
						return 0;
					}
				}
			}
		}
	}

	return value;
}

/*
	Type:		Function - Recursive
	Objet:		Backtracking the grid and brute forcing solutions
	Arguments:	row: Backtrcking on this row
				column: Backtrcking on this column
	Help:		http://en.wikipedia.org/wiki/Sudoku_algorithms#Backtracking
*/
bool backtrack(int row, int column) {
	int i, tmp;

	if(outputGrid[row][column] == 0) {	// a blank cell
		
		for(i = 1; i < 10; i++) {	// [1, 10[ to never use 0 as solution
			tmp = inputValue(row, column, i);
			
			if(tmp > 0) {
				outputGrid[row][column] = tmp;
				if((row == 8) && (column == 8)) {
					return true;
				} else if(row == 8) {
					if(backtrack(0, column + 1))
						return true;
				} else {
					if(backtrack(row + 1, column))
						return true;
				}
			}
		}
		
		if(i == 10) {
			if(outputGrid[row][column] != Grid[row][column])
				outputGrid[row][column] = 0;
			return false;
		}
	
	} else {
		if((row == 8) && (column == 8)) {
			return true;
		} else if(row == 8) {
			if(backtrack(0, column + 1))
				return true;
		} else {
			if(backtrack(row + 1, column))
				return true;
		}
	}

}

/*
	Type:		Procedure
	Objet:		Initialise all cells on the grid to 0
	Argument:	grid: The grid that will be initialised
*/
void initGrid(int grid[9][9]) {
	int row, column;
	for(row = 0; row < 9; row++)
		for(column = 0; column < 9; column++)
				grid[row][column] = 0;
}

/*
	Type:		Procedure
	Objet:		Print contents of a grid
	Argument:	grid: The grid that will be printed
*/
void printGrid(int grid[9][9]) {
	int row, column;

	for(row = 0; row < 9; row++) {
		if(row % 3 == 0) printf("+-------+-------+-------+\n");
		for(column = 0; column < 9; column++) {
			if(column % 3 == 0) printf("| ");
				printf("%d ", grid[row][column]);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}

/*
	Type:		Procedure
	Objet:		Export a grid in a file
	Arguments:	grid: The grid will be exported
				filename: The filename that will be contains the grid
*/
void exportGrid(int grid[9][9], char filename[255]) {
	int row;

	// Opening the export filename on mode write
	FILE * file = fopen(filename, "w");

	// Writing the grid on the file
	for(row = 0; row < 9; row++)
		fprintf(file, "%d %d %d %d %d %d %d %d %d\n",
					grid[row][0], grid[row][1], grid[row][2],
					grid[row][3], grid[row][4], grid[row][5],
					grid[row][6], grid[row][7], grid[row][8]);

	fclose(file);	// Closing the export file
}

/*
	Type:		Procedure
	Objet:		Fill a grid by the user
	Arguments:	grid: The grid will be create
*/
void fillGrid(void) {
	int row, column, tmp;

	initGrid(outputGrid);

	while(true) {
		clear();
		printGrid(outputGrid);
		printf("\nEnter the coordinates:\n");
		printf("Row: ");
		scanf("%d", &row);
		printf("Column: ");
		scanf("%d", &column);
		printf("Type the value of case [%dx%d] (99 To quit): ", row, column);
		scanf("%d", &tmp);

		if(tmp == 99) {	// Quit the filling form
			break;

		} else if(tmp < 0 || tmp > 10) {	// Out the rang [1, 9]
			printf("\nPlease, fill a number from 1 through 9... ");
			getchar(); getchar();

		} else if(inputValue(row - 1, column - 1, tmp) == tmp) {	// True input
			outputGrid[row - 1][column - 1] = tmp;

		} else {	// Wrong input
			printf("\nError: This value is already inputted... ");
			getchar(); getchar();
			continue;
		}
	}

	// Export the grid as: grid.sdk
	clear();
	printf("\nThe grid was exported as: \"grid.sdk\"... \n\nPress <Enter> to start solving the grid... ");
	exportGrid(outputGrid, "grid.sdk");
	getchar(); getchar();

	// Copy the outputGrid to Grid (Preparing to solveFrid())
	for(row = 0; row < 9; row++) {
		for(column = 0; column < 9; column++) {
			Grid[row][column] = outputGrid[row][column];
		}
	}

	/*char export_choice;
	printf("\nDo you want to export the grid, (Y)es or (N)o ? ");
	scanf("%c", &export_choice);
	export_choice = tolower(export_choice);

	if(export_choice == 'y') {	// Yes, I want to export the solution
		clear();
		char export_filename[20];
		printf("\n[+] Enter the filename: ");
		scanf("%s", export_filename);

		// Adding the extention .sdk to the filename :=> sdk = SuDoKu
		strcat(export_filename, ".sdk");

		exportGrid(Grid, export_filename);

		clear();
		printf("\nExporting the grid... Done\n");
		printf("\nPress <Enter> to return to the main menu... ");
					
	} else {	// No, I don't want to export it
		printf("\nPress <Enter> to return to the main menu... ");
	}*/

}

/*
	Type:		Procedure
	Objet:		Solve the grid: Grid[9][9]
*/
void solveGrid(void) {
	int row, column;

	clear();
	// Print the original grid
	printf("\nThe Original Grid: \n\n");
	printGrid(Grid);

	printf("\nPress <Enter> to start solving the puzzle... ");
	getchar(); getchar();

	// Copy the original grid to outputGrid
	for(row = 0; row < 9; row++) {
		for(column = 0; column < 9; column++) {
			outputGrid[row][column] = Grid[row][column];
		}
	}

	// BackTracking from row 0, column 0
	if(backtrack(0, 0)) {
		clear();
		// Print the solution
		printf("\nThe Solution is :\n\n");
		printGrid(outputGrid);
							
		char export_choice;
		printf("\nDo you want to export the solution, (Y)es or (N)o ? ");
		scanf("%c", &export_choice);
		export_choice = tolower(export_choice);

		if(export_choice == 'y') {	// Yes, I want to export the solution
			clear();
			char export_filename[20];
			printf("\n[+] Enter the filename that will save the solution: ");
			scanf("%s", export_filename);

			// Adding the extention .sdk to the filename :=> sdk = SuDoKu
			strcat(export_filename, ".sdk");

			exportGrid(outputGrid, export_filename);

			clear();
			printf("\nExportation the solution... Done\n");
			printf("\nPress <Enter> to return to the main menu... ");
			getchar();
						
		} else {	// No, I don't want to export it
			printf("\nPress <Enter> to return to the main menu... ");
			getchar();
		}
						
	} else {	// No solution, exit
		printf("\nNo Solution...\n");
		getchar();
	}
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MAIN PROGRAM ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


int main() {
	char main_choice;		// main menu choice
	int solve_choice;		// solve menu choice

	do { 	// Do this, while we didn't quit
		main_menu();	// Display the main menu
		printf("\v\t[+] Enter your choice: ");
		scanf("%c", &main_choice);
		main_choice = tolower(main_choice);		// Convert the main_choice to lowercase
		getchar();

		switch(main_choice) {
			case 's':	// Solve a Sudoku
				do {
					solve_menu();	// Solve Menu
					printf("\v\t[+] Enter your choice (1 ~ 2): ");
					scanf("%d", &solve_choice);
					
					if(solve_choice == 1) {		// Fill a new grid
						clear();
						fillGrid();
						solveGrid();
						getchar();
						break;	// Go back to main menu

					} else if(solve_choice == 2) {	// Solve a Sudoku by loading the grid from a file
						clear();
						char filename[25];		// Grid's filename
						
						// Available sudoku files
						printf("\nAvailable sudoku files on this directory:\n\n");
						
						#if defined __APPLE__ || defined linux
							system("ls grids/*.sdk");
						#elif defined ( WIN32 ) || defined ( WIN64 )
							system("dir grids\\*.sdk");
						#endif

						printf("\n[+] Enter the filename: ");
						scanf("%s", filename);

						int row;
						FILE * gridFile;

						if((gridFile = fopen(filename, "r")) == NULL) {	// Grid file non-existant
							error("\tSudoku file non-existant... \n\n\tPress <Enter> to try again...");
							getchar();
						
						} else {
							// Start solving the puzzle
							// Loading each cell from the gridFile
							for(row = 0; row < 9; row++) {
								fscanf(gridFile, "%d %d %d %d %d %d %d %d %d",
												&Grid[row][0], &Grid[row][1], &Grid[row][2],
												&Grid[row][3], &Grid[row][4], &Grid[row][5],
												&Grid[row][6], &Grid[row][7], &Grid[row][8]);
							}
							fclose(gridFile);	// Closing gridFile

							solveGrid();
						}

						getchar();
						break;	// Go back to main menu
					
					} else {	// Solve choice isn't neither 1 neither 2
						error("\tI didn't understand your choice !\n\n\tPress <Enter> to try again... ");
						getchar();
						getchar();
						continue;
					}

				} while((solve_choice != 1) && (solve_choice != 2));

				break;	// Return to main menu
			
			case 'q':	// Just quit the program
				quit();
				printf("\t-------------------------------------------------------");
				getchar();
				return 0;
			
			default:
				error("\tI didn't understand your choice !\n\n\tPress <Enter> to try again... ");
				getchar();
				break;
		}

	} while(main_choice != 'q');
	
}
// EOF