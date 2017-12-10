#include "stdafx.h"
#include <ctype.h>
#include <iostream>
using namespace std;

const char BLANK = ' ', LEAF = '#', WOOD = '|', BOUNDRY = '.';
const int MINSIZE = 4, MAXSIZE = 20;

int main()
{
	bool getValidHeight(int);
	bool agreeToContinue();
	void multiplyChars(char, int);
	char randomDecoration();

	int treeHeight;

Draw_Tree:
	do {
		cout << "Enter the size of the tree (4-20): ";
		cin >> treeHeight;

		if (!getValidHeight(treeHeight)) {
			cout << "ERROR: Invalid height! ";
		}
	} while (!getValidHeight(treeHeight));
	// Tree height is now valid, between min and max value

	int difference = 1,
		leavesHeight = treeHeight - 2,
		woodSpaces = 0,
		boundryLength = leavesHeight * 2 + 1;

	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;

	for (int x = 0; x < treeHeight; x++) {
		if (x >= leavesHeight) {
			cout << BOUNDRY;
			multiplyChars(BLANK, woodSpaces);
			cout << WOOD;
			multiplyChars(BLANK, woodSpaces);
			cout << BOUNDRY;
		}
		else {
			int spaces = leavesHeight - difference;

			cout << BOUNDRY;
			multiplyChars(BLANK, spaces);
			if (x == 0) {
				woodSpaces = spaces;
				cout << randomDecoration();
			}
			else {
				multiplyChars(LEAF, x + difference);
			}
			multiplyChars(BLANK, spaces);
			cout << BOUNDRY;

			difference++;
		}

		cout << endl;
	}
	
	multiplyChars(BOUNDRY, boundryLength);
	cout << endl;

	cout << "Would you like another tree? (Y/N): ";
	if (agreeToContinue()) {
		goto Draw_Tree;
	}
	else {
		return 0;
	}
}

bool getValidHeight(int treeHeight) {
	return treeHeight >= MINSIZE && treeHeight <= MAXSIZE;
}

void multiplyChars(char c, int amount) {
	for (int i = 0; i < amount; i++)
		cout << c;
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