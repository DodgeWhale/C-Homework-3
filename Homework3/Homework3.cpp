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
	bool reset; // Whether or not the user wants another tree

	cout << "Marcus Wadge-Dale, SE3, 10:00am Tuesday 12th December 2017" << endl;

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

		// Prompt user to run the reset while loop again
		cout << "Would you like another tree? (Y/N): ";
		reset = agreeToContinue();
	} while (reset);
}

// Changes the console colour to the colour code specified
void setConsoleColour(int colour) {
	SetConsoleTextAttribute(hConsole, colour);
}

// Returns whether or not the int passed is
// within the range of min and max size
bool getValidHeight(int treeHeight) {
	return treeHeight >= MINSIZE && treeHeight <= MAXSIZE;
}

void drawAXmasTree(int treeHeight) {
	// Define local variables
	int difference = 1,
		leavesHeight = treeHeight - 2, // The logs always have a height of 2
		woodSpaces = 0,
		boundryLength = leavesHeight * 2 + 1;

	// Print the top border
	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;

	// Loop from 0 - the height of the tree passed
	for (int x = 0; x < treeHeight; x++) {
		if (x >= leavesHeight) {
			cout << BOUNDRY;
			drawTrunk(woodSpaces);
			cout << BOUNDRY;
		}
		else {
			int spaces = leavesHeight - difference;

			// Print left padding and border line
			cout << BOUNDRY;
			multiplyChars(BLANK, spaces);

			// 0 = the peak of the tree
			if (x == 0) {
				woodSpaces = spaces;
				setConsoleColour(12); // RED
				cout << randomDecoration();
				setConsoleColour(7); // WHITE
			}
			else {
				drawLineOfFoliage(x + difference);
			}

			// Print right padding and border line
			multiplyChars(BLANK, spaces);
			cout << BOUNDRY;

			difference++;
		}

		cout << endl;
	}

	// Print out bottom border
	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;
}

// Prints a character X amount of times
void multiplyChars(char c, int amount) {
	for (int i = 0; i < amount; i++) {
		// If the character passed is blank, there's a 1 in 8 chance it will show a 'snowflake'
		if (c == BLANK) {
			if (rand() % 8 == 0) {
				cout << '*';
				continue;
			}
		}
		cout << c;
	}
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
