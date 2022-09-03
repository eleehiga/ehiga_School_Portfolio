/* Name: Ethan Higa
 * Class CPSC 121, Spring 2020
 * Date: April 6, 2020
 * Programming Assignment: PA8
 * Description: the game of battleship
 */

#include "ehiga_PA8.h"

void welcomeScreen() {
	string tempString;
	cout << "**** Welcome to Battleship! ****\nRules of the Game:\n1. This is a two player game.\n2. Player1 is you and Player2 is the computer\n3. The objective of the game is to destroy all the battleships on the opponents board before he does to yours\n4. when inputting your battleships do the row number and then a space and the a column number and then the next cell till you get the size of the battleship filled\n5. when targeting input a row number and then a space and then a column number\n\nHit enter to start the game!";
	getline(cin, tempString);
	system("clear");
}

void initializeBoard(char gameBoard1[10][10], char gameBoard2[10][10], char gameBoard3[10][10])
{
	fillArray(gameBoard1, 10, 10);
	fillArray(gameBoard2, 10, 10);
	fillArray(gameBoard3, 10, 10);	
}

bool selectwhoStartsFirst()
{
	srand(time(0));
	if(rand() % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void manuallyPlaceShipsOnBoard(const string shipNames[],const char shipSymbols[], const int shipSizes[], char board[10][10])
{
	string tempString;
	bool isHorizontal;
	bool invalid = false;

	for(int i = 0; i < 5; ++i)
	{
		int row[shipSizes[i]];
		int col[shipSizes[i]];
		cout << "Please enter the " << shipSizes[i] << " cells to place the " << shipNames[i] << " across:\n";
		for(int j = 0; j < shipSizes[i]; ++j)
		{
			cin >> row[j];
			cin >> col[j];
		}
		getline(cin, tempString);
		for(int j = 1; j < shipSizes[i]; ++j)
		{
			if(row[j] != row[j-1])
			{
				isHorizontal = false;
			}
			else if(col[j] != col[j-1])
			{
				isHorizontal = true;
			}
			if(row[j] < 0 || row[j] > 9 || col[j] < 0 || col[j] > 9 || isalpha(board[row[j]][col[j]]))
			{
				invalid = true;
				break;	
	
			}
		}
		if(invalid)
		{
			cout << "Invalid ship placement please enter again:\n";
			--i;
			continue;
		}
		if(isHorizontal)
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				if(row[j] != row[j-1] && col[j] != col[j-1] + 1)
				{
					invalid = true;
					break;	
				}
			}
		}
		else
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				if(col[j] != col[j-1] && row[j] != row[j-1] + 1)
				{
					invalid = true;
					break;	
				}
			}
		}
		if(invalid)
		{
			cout << "Invalid ship placement please enter again:\n";
			--i;
			continue;
		}
		for(int j = 0; j < shipSizes[i]; ++j)
		{
			board[row[j]][col[j]] = shipSymbols[i];
		}
	}
}
void randomlyPlaceShipsOnBoard(const char shipSymbols[],const int shipSizes[], char board[10][10])
{
	string tempString;
	bool isHorizontal;
	int numHorizontal;
	bool invalid = false;
	srand(time(0));

	for(int i = 0; i < 5; ++i)
	{
		int row[shipSizes[i]];
		int col[shipSizes[i]];
		row[0] = rand() % 10;
		col[0] = rand() % 10;
		numHorizontal = rand() % 2;
		if(numHorizontal == 0) //Not horizontal
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				row[j] = row[j-1] + 1;
				col[j] = col[0];
			}
			
		}
		else
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				row[j] = row[0];
				col[j] = col[j-1] + 1;
			}
		}
		for(int j = 0; j < shipSizes[i]; ++j)
		{
			invalid = board[row[j]][col[j]] == 'd'|| board[row[j]][col[j]] == 's' || board[row[j]][col[j]] == 'b'|| board[row[j]][col[j]] == 'r' || board[row[j]][col[j]] == 'c' || row[j] > 9 || col[j] > 9;
		}
		if(invalid)
		{
			--i;
			continue;
		}
		if(numHorizontal == 1)
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				if(row[j] != row[j-1] && col[j] != col[j-1] + 1)
				{
					invalid = true;
					break;	
				}
			}
		}
		else
		{
			for(int j = 1; j < shipSizes[i]; ++j)
			{
				if(col[j] != col[j-1] && row[j] != row[j-1] + 1)
				{
					invalid = true;
					break;	
				}
			}
		}
		if(invalid)
		{
			--i;
			continue;
		}
		for(int j = 0; j < shipSizes[i]; ++j)
		{
			board[row[j]][col[j]] = shipSymbols[i];
		}
	}
}

//for p2 take shot use display board
void takeShot(int& row, int& col, char board[10][10], bool p1Turn)
{
	string tempString;
	bool validShot = false;
	srand(time(0));

	while(!validShot)
	{
		if(p1Turn)
		{
			cin >> row;
			cin >> col;
			getline(cin, tempString);
		}
		else
		{
			row = rand() % 10;
			col = rand() % 10;
		}
		if(row < 0 || row > 9 || col < 0 || col > 9 || board[row][col] == '*' || board[row][col] == 'm' || board[row][col] == 'v' || board[row][col] == 'w' || board[row][col] == 'x' || board[row][col] == 'y' || board[row][col] == 'z')
		{
			if(p1Turn)
			{
				cout << "Invalid target\nEnter a target: ";
			}
			continue;
		}	
		else
		{
			validShot = true;
		}

	}
}
string checkShot(int row, int col, char board[10][10])
{
	if(board[row][col] == '-')
	{
		return "miss";
	}
	else
	{
		return "hit";
	}
}
int isWinner(char board[10][10],const char shipSymbols[],const char altSymbols[], bool p1Turn)
{
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			for(int k = 0; k < 5; ++k)
			{
				if(board[i][j] == shipSymbols[k])
				{
					return 0;
				}	
			}
		}
	}
	if(p1Turn)
	{
		return 1;
	}
	return 2;
}
// for p1's board
void updateBoard(int row, int col, char board[10][10])
{
	if(board[row][col] == '-')
	{
		board[row][col] = 'm';
	}
	else
	{
		board[row][col] = '*';
	}
}

// For p2's board because there are two boards to use
void updateBoard(int row, int col, char gameBoard[10][10], char displayBoard[10][10], const char shipSymbols[], const char altSymbols[], const int shipSizes[], bool& sunkShip)
{
	// update the count of how many letters there are after updating
	// If letter count a certain amount and symbol not filled in already to display then fill in to display the ship symbol
	int symbolCount[] = {0,0,0,0,0};
	if(gameBoard[row][col] == '-')
	{
		displayBoard[row][col] = 'm';
		gameBoard[row][col] = 'm';
		return;
	}
	displayBoard[row][col] = '*';
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; j++)
		{
			for(int k = 0; k < 5; ++k)
			{
				if(gameBoard[i][j] == altSymbols[k])
				{
					++symbolCount[k];
				}
			}
		}
	}
	for(int k = 0; k < 5; ++k)
	{
		cout << symbolCount[k] << endl;
		if(symbolCount[k] == shipSizes[k] - 1)
		{
			sunkShip = true;
			for(int i = 0; i < 10; ++i)
			{
				for(int j = 0; j < 10; ++j)
				{
					if(gameBoard[i][j] == altSymbols[k])
					{
						displayBoard[i][j] = shipSymbols[k];
					}
				}
			}
			displayBoard[row][col] = shipSymbols[k];
		}
	}
	for(int i = 0; i < 5; ++i)
	{
		if(gameBoard[row][col] == shipSymbols[i])
		{
			gameBoard[row][col] = altSymbols[i]; 
		}
	}
}
void displayBoard(char board[10][10])
{
	cout << "  ";
	for(int i = 0; i < 10; ++i)
	{
		cout << i << " "; 
	}
	cout << endl;
	for(int i = 0; i < 10; ++i)
	{
		cout << i << " ";
		for(int j = 0; j < 10; ++j)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void outputCurrentMove(ofstream& outFile, bool p1Turn, int row, int col, string shotStatus, string sunkShip)
{
	int player;
	if(p1Turn)
	{
		player = 1;
	}
	else
	{
		player = 2;
	}
	outFile << "Player" << player << row << "," << col << " \"" << shotStatus << "\" " << sunkShip << endl;
}

// for p1's board
string checkIfSunkShip(char gameBoard[10][10], const char shipSymbols[], const string shipNames[]){
	int shipCount[] = {0,0,0,0,0};
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			for(int k = 0; k < 5; ++k)
			{
				if(gameBoard[i][j] == shipSymbols[k])
				{
					++shipCount[k];
				}
			}
		}
	}
	for(int k = 0; k < 5; ++k)
	{
		if(shipCount[k] == 1)
		{
			return "sunk " + shipNames[k] + "!";
		}
	}
	return "";
}

// for p2's board using boolean
string checkIfSunkShip(bool& shipSunk, int row, int col, const string shipNames[], char gameBoard[10][10])
{
	if(shipSunk)
	{
		shipSunk = false;
		return "sunk " + shipNames[static_cast<int>(gameBoard[row][col]) - 118] + "!";
	}
	return " ";
}

void shotCommentary(int row, int col, string shotStatus, string sunkShip)
{
	cout << row << "," << col << " is a " << shotStatus;
	if(sunkShip != "")
	{
		cout << ", " << sunkShip;
	}
	cout << endl;
}
void outputStats(ofstream& outFile, int winPlayer, char p1GameBoard[10][10], char p2DisplayBoard[10][10])
{
	int p1Hits =0; int p1Misses = 0; int p2Hits = 0; int p2Misses =0;
	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			if(p2DisplayBoard[i][j] == 'm')
			{
				++p1Misses;
			}
			else if(isalpha(p2DisplayBoard[i][j]) && p2DisplayBoard[i][j] != 'm')
			{
				++p1Hits;
			}
			if(p1GameBoard[i][j] == 'm')
			{
				++p2Misses;
			}
			else if(p1GameBoard[i][j] == '*')
			{
				++p2Hits;
			}
		}
	}

	int losPlayer = -winPlayer + 3;
	outFile << "Player" << winPlayer << ", Player" << losPlayer << " loses\n*** Player1 Stats ***\n";
	outFile << "Number Hits: " << p1Hits << endl;
	outFile << "Number Misses: " << p1Misses << endl;
	outFile << "Total Shots: " << p1Hits + p1Misses << endl;
	outFile << "Hit/Miss Ratio: " << fixed << static_cast<double>(p1Hits) / p1Misses * 100 << endl << endl;

	outFile << "*** Player2 Stats ***\n";
	outFile << "Number Hits: " << p2Hits << endl;
	outFile << "Number Misses: " << p2Misses << endl;
	outFile << "Total Shots: " << p2Hits + p2Misses << endl;
	outFile << "Hit/Miss Ratio: " << fixed << static_cast<double>(p2Hits) / p2Misses * 100 << endl;
}

void printArray(const char arr[10][10], int rows, int cols) {
        int i, j;

        for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                        cout << arr[i][j] << " ";
                }
                cout << endl;
        }
}


void fillArray(char arr[10][10], int rows, int cols) {
        int i, j;

        // outer loop iterates over each row
        for (i = 0; i < rows; i++) {
                // inner loop iterates over int in arr[i] (row)
                for (j = 0; j < cols; j++) {
                        arr[i][j] = '-';
                }
        }
}

