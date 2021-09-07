#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include "quadtree.h"

#define uns unsigned
//#define clout system("cls");
//#define clin  rewind(stdin);
//#define pause system("pause");

using namespace std;

int main(int argc, char* argv[])
{
	Quadtree quadtree;
	try {
		if (argv[1] == "test")
			system("test.bat");
	}
	catch(string exc){}
	if (!argv[1])
	{
		try {
			freopen("input.txt", "r", stdin);
			freopen("output.txt", "w", stdout);
		}
		catch (string exc) {}
	}
	else if(argv[1] && argv[1] != "test")
	{
		try {
			freopen(argv[1], "r", stdin);
			freopen("output.txt", "w", stdout);
		}
		catch (string exc) {
			cout << "No such test";
		}
	}
	//pause;
	while (true)
	{
		//clout;
		cout << "1) Build new tree from matrix\n" <<
			"2) Build new matrix from tree\n" <<
			"3) Print tree\n" <<
			"4) Print matrix\n" <<
			"5) Exit\n";

		string choice;
		cin >> choice;

		if (choice == "1")
			quadtree.buildTree();
		else if (choice == "2")
			quadtree.buildMatrix();
		else if (choice == "3")
			quadtree.printRoot();
		else if (choice == "4")
			quadtree.printMatrix();
		else if (choice == "5")
			break;
		else
			cout << "No such command\n";
		//pause;
	}
	fclose(stdin);
	fclose(stdout);
}