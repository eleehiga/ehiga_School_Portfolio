/* Name: Ethan Higa
 * Class CPSC 121, Spring 2020
 * Date: April 6, 2020
 * Programming Assignment: PA8
 * Description: the game of battleship
 */

#include "ehiga_PA8.h"

const int NUM_ROWS = 10;
const int NUM_COLS = 10;

const string shipNames[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"}; // 5 ship types
const char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
const char altSymbols[] = {'v','w','x','y','z'}; //Using alternate symbols to keep track of what type of ship hit on p2's board
const int shipSizes[] = {5, 4, 3, 3, 2};

int main() {
	string fileName = "battleship.log";
	ofstream outFile;	
	char p1ShipBoard[NUM_ROWS][NUM_COLS];
	char p2ShipBoard[NUM_ROWS][NUM_COLS];
	char p2DisplayBoard[NUM_ROWS][NUM_COLS];
	int selection;
	bool p1Turn;
	string tempString;
	int targetRow;
	int targetCol;
	int winPlayerNumber = 0;
	bool isShipSunk = false;
	int p1Hits = 0;
	int p1Misses = 0;
	int p2Hits = 0;
	int p2Misses = 0;
	string shotStatus;
	string shipSunk;

	outFile.open(fileName);
	if(!outFile.is_open())
	{
		cout << "Cannot open file, error\n";
		return -1;
	}
	welcomeScreen();
	initializeBoard(p1ShipBoard, p2ShipBoard, p2DisplayBoard);
	// how to place ship
	cout << "Please select from the following menu:\n 1. Enter positions of ships manually.\n2. Allow the program to randomly select positions of ships.\n\n"; 
	cin >> selection;
	getline(cin, tempString);
	p1Turn = selectwhoStartsFirst();
	if(selection == 1)
	{
		manuallyPlaceShipsOnBoard(shipNames, shipSymbols, shipSizes, p1ShipBoard);
	}
	else
	{
		randomlyPlaceShipsOnBoard(shipSymbols, shipSizes, p1ShipBoard, p1Turn);
	}
	randomlyPlaceShipsOnBoard(shipSymbols, shipSizes, p2ShipBoard, !p1Turn);
	cout << "Player2 (Computer's) board has been generated.\n\n";
	if(p1Turn)
	{
		cout << "Player 1 goes first\n";
	}
	else
	{
		cout << "Player 2 goes first \n";
	}
	// Win when the number of player who won is outputted by a function
	while(winPlayerNumber == 0)
	{
		cout << "Press Enter to Continue: ";
		getline(cin, tempString);
		system("clear");
		cout << "Player1's Board:\n\n";

		displayBoard(p1ShipBoard);
		cout << "Player2's Board:\n\n";
		displayBoard(p2DisplayBoard);
		
		if(p1Turn) // p1 affects p2's board
		{
			cout << "Enter a target: "; 
			takeShot(targetRow, targetCol, p2ShipBoard, p1Turn); // Validates target inputs
			shotStatus = checkShot(targetRow, targetCol, p2ShipBoard); // If miss or hit
			updateBoard(targetRow, targetCol, p2ShipBoard, p2DisplayBoard, shipSymbols, altSymbols, shipSizes, isShipSunk); // Put a asterik or ship letters on board, also used to output if the ship is sunk on p2's board
			shipSunk = checkIfSunkShip(isShipSunk, targetRow, targetCol, shipNames, p2ShipBoard); //Outputs what ship sunk
			winPlayerNumber = isWinner(p2ShipBoard, shipSymbols, altSymbols, p1Turn);// Win if p2's board only astericks and dashes, not letters
			outputCurrentMove(outFile, p1Turn, targetRow, targetCol, shotStatus, shipSunk);
			p1Turn = false;
		}
		else
		{
			takeShot(targetRow, targetCol, p1ShipBoard, p1Turn);
			shotStatus = checkShot(targetRow, targetCol, p1ShipBoard);
			shipSunk = checkIfSunkShip(p1ShipBoard, shipSymbols, shipNames, targetRow, targetCol);
			updateBoard(targetRow, targetCol, p1ShipBoard);
			winPlayerNumber = isWinner(p1ShipBoard, shipSymbols, altSymbols, p1Turn);
			outputCurrentMove(outFile, p1Turn, targetRow, targetCol, shotStatus, shipSunk);
			cout << "Player2 selects: ";
			p1Turn = true;
		}
		shotCommentary(targetRow, targetCol, shotStatus, shipSunk);
		
	}
	cout << "Player " << winPlayerNumber << " wins!\n";
	outputStats(outFile, winPlayerNumber, p1ShipBoard, p2DisplayBoard);

	outFile.close();

	return 0;
}

