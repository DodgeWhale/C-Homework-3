#include "stdafx.h"
#include <ctime>
#include <windows.h>
#include <iostream>
using namespace std;

// Constant variables
const char BLANK = ' ', LEAF = '#', WOOD = '|', BOUNDRY = '.';
const int MINSIZE = 4, MAXSIZE = 20;

// Console colours
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setConsoleColour(int);
bool getValidHeight(int);
bool agreeToContinue();
void multiplyChars(char, int);
char randomDecoration();
void drawLineOfFoliage(int);
void drawTrunk(int);
void drawAXmasTree(int);

int main()
{
	int treeHeight;
	bool reset;

	cout << "Marcus Wadge-Dale, SE3, Tuesday 12th December 10:00am" << endl;

	do {
		do {
			cout << "Enter the size of the tree (4-20): ";
			cin >> treeHeight;

			if (!getValidHeight(treeHeight)) {
				cout << "ERROR: Invalid height! ";
			}
		} while (!getValidHeight(treeHeight));
		// Tree height is now valid, between min and max value

		drawAXmasTree(treeHeight);

		cout << "Would you like another tree? (Y/N): ";
		reset = agreeToContinue();
	} while (reset);
}

void setConsoleColour(int colour) {
	SetConsoleTextAttribute(hConsole, colour);
}

// Returns whether or not the int passed is
// within the range of min and max size
bool getValidHeight(int treeHeight) {
	return treeHeight >= MINSIZE && treeHeight <= MAXSIZE;
}

void drawAXmasTree(int treeHeight) {
	int difference = 1,
		leavesHeight = treeHeight - 2,
		woodSpaces = 0,
		boundryLength = leavesHeight * 2 + 1;

	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;

	for (int x = 0; x < treeHeight; x++) {
		if (x >= leavesHeight) {
			cout << BOUNDRY;
			drawTrunk(woodSpaces);
			cout << BOUNDRY;
		}
		else {
			int spaces = leavesHeight - difference;

			cout << BOUNDRY;
			multiplyChars(BLANK, spaces);

			if (x == 0) {
				woodSpaces = spaces;
				setConsoleColour(12); // RED
				cout << randomDecoration();
				setConsoleColour(7); // WHITE
			}
			else {
				drawLineOfFoliage(x + difference);
			}

			multiplyChars(BLANK, spaces);
			cout << BOUNDRY;

			difference++;
		}

		cout << endl;
	}

	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;
}

// Prints the characters 
void multiplyChars(char c, int amount) {
	for (int i = 0; i < amount; i++)
		cout << c;
}

void drawLineOfFoliage(int length) {
	setConsoleColour(2); // GREEN
	multiplyChars(LEAF, length);
	setConsoleColour(7); // WHITE
}

void drawTrunk(int spaces) {
	multiplyChars(BLANK, spaces);
	setConsoleColour(6); // DARK YELLOW
	cout << WOOD;
	setConsoleColour(7); // WHITE
	multiplyChars(BLANK, spaces);
}

bool agreeToContinue() {
	char input;
	cin >> input;

	return toupper(input) == 'Y';
}

char randomDecoration() {
	int random = rand() % 4;

	char decoration;
	switch (random) {
		case 0:
			decoration = '*';
			break;
		case 1:
			decoration = '&';
			break;
		case 2:
			decoration = '@';
			break;
		case 3:
			decoration = '0';
			break;
	}
	return decoration;
}