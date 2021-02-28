#include <iostream>
#include <vector>
#include <cmath>
#include "quadtree.h"

#define uns unsigned
#define clout system("cls");
#define clin  rewind(stdin);
#define pause system("pause");

using namespace std;

int main()
{
	Quadtree quadtree;
	while (true)
	{
		clout;
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
			return 0;
		else
			cout << "No such command\n";
		pause;
	}
}