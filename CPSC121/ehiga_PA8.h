/* Name: Ethan Higa
 * Class CPSC 121, Spring 2020
 * Date: April 6, 2020
 * Programming Assignment: PA8
 * Description: the game of battleship
 */

#ifndef EHIGA_PA8_H
#define EHIGA_PA8_H
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cctype>

using namespace std;

void welcomeScreen();
void initializeBoard(char[10][10], char[10][10], char[10][10]);
bool selectwhoStartsFirst();
void manuallyPlaceShipsOnBoard(const string[],const char[], const int[], char[10][10]);
void randomlyPlaceShipsOnBoard(const char[], const int[], char[10][10]);
void takeShot(int&, int&, char[10][10], bool);
string checkShot(int, int, char[10][10]);
int isWinner(char[10][10], const char[], const char[], bool);
void updateBoard(int, int, char[10][10]);
void updateBoard(int, int, char[10][10], char[10][10], const char[], const char[], const int[], bool&);
void displayBoard(char[10][10]);
void outputCurrentMove(ofstream& outFile, bool, int, int, string, string);
string checkIfSunkShip(char[10][10], const char[], const string[]);
string checkIfSunkShip(bool&, int, int, const string[], char[10][10]);
void shotCommentary(int, int, string, string);
void outputStats(ofstream& outFile, int, char[10][10], char[10][10]);

// TODO possibly remove the two below
void fillArray(char[10][10], int, int);
void printArray(const char[10][10], int, int);
#endif
