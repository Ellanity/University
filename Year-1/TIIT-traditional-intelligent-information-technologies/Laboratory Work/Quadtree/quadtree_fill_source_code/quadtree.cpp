#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define uns unsigned
#define clout system("cls");
#define clin  rewind(stdin);
#define pause system("pause");

#include "quadtree.h"


uns stringToUns(std::string str)
{
	uns ans = 0;
	for (uns i = 0; i < str.size(); i++)
	{
		ans *= 10;
		if (str[i] - '0' >= 0 && str[i] - '0' < 10)
			ans += str[i] - '0';
		else if (str[i] - '0' > 50)
			ans -= 38;
		else
			ans /= 10;
		if (i == 0 && str[i] == '-')
			ans = 0;
	}
	return ans;
}

//private methods
void Quadtree::freeMemory(Square* square)
{
	if (square != NULL)
	{
		for (uns i = 0; i < CHILD_COUNT; i++)
			if (square->child[i] != NULL)
				freeMemory(square->child[i]);
		delete square;
	}
}
void Quadtree::clearFields()
	{
		tree_lvl = 0;
		max_tree_lvl = 0;
		freeMemory(root);
		root = new Square;
		root = NULL;
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].clear();
		matrix.clear();
	}

struct Square* Quadtree::createTree(Square* parent, std::vector <std::vector <uns>> table)
{
	uns in_column = table.size();
	uns in_row = table[0].size();

	if (parent == NULL)
	{
		//Create childs for root
		parent = new Square;
		for (uns i = 0; i < CHILD_COUNT; i++)
			parent->child[i] = NULL;

		if (in_column > 1 && in_row > 1)
		{
			//R-row C-column RC-row or column
			uns x = 0, y = 0, new_table_child_num_R = 0, new_table_child_num_C = 0;
			uns new_table_elements_RC_quantity = in_column / 2;

			for (uns i = 0; i < CHILD_COUNT; i++)
			{
				parent->child[i] = NULL;
				std::vector <std::vector <uns>> new_table;

				x = new_table_child_num_R * new_table_elements_RC_quantity;
				y = new_table_child_num_C * new_table_elements_RC_quantity;


				for (uns j = y; j < y + new_table_elements_RC_quantity; j++)
				{
					std::vector<uns> one_row;

					for (uns k = x; k < x + new_table_elements_RC_quantity; k++)
						one_row.push_back(table[j][k]);

					new_table.push_back(one_row);
				}

				if (new_table_child_num_R == NEW_TABLE_CHILD_RC)
				{
					new_table_child_num_R = 0;
					new_table_child_num_C++;
				}
				else
					new_table_child_num_R++;

				parent->child[i] = createTree(parent->child[i], new_table);
				parent->have_child = true;
				parent->value = 0;
			}

			//Make from same childs one node
			if (parent != NULL)
			{
				bool common_bool = true;
				uns common_value = parent->child[0]->value;

				for (uns i = 0; i < CHILD_COUNT; i++)
					if (parent->child[i]->value != common_value || parent->child[i]->have_child == true)
						common_bool = false;


				if (common_bool)
				{
					for (uns i = 0; i < CHILD_COUNT; i++)
					{
						freeMemory(parent->child[i]);
						parent->child[i] = NULL;
					}

					parent = NULL;
					parent = new Square;

					parent->value = common_value;
					parent->have_child = false;
					for (uns i = 0; i < CHILD_COUNT; i++)
						parent->child[i] = NULL;
				}
			}
		}
		else
		{
			parent->value = table[0][0];
			parent->have_child = false;
			for (uns i = 0; i < CHILD_COUNT; i++)
				parent->child[i] = NULL;
		}
	}
	return parent;
}
void Quadtree::printTree(Square* square)
{
	if (square != NULL)
	{
		tree_lvl++;
		if (tree_lvl >= max_tree_lvl)
			max_tree_lvl = tree_lvl;

		std::cout << "       ";
		if (!square->have_child)
		{
			for (uns i = 0; i < tree_lvl - 1; i++)
				std::cout << "    ";
			std::cout << "|___" << square->value << "\n";
		}

		else
		{
			for (uns i = 0; i < tree_lvl - 1; i++)
				std::cout << "    ";
			std::cout << "|___" << "\n";

			for (uns i = 0; i < CHILD_COUNT; i++)
			{

				printTree((square->child[i]));
			}
		}
		tree_lvl--;
	}
}
struct Square* Quadtree::readTree(Square* parent, std::string action)
{
	if (parent == NULL)
	{
		parent = new Square;
		for (uns i = 0; i < CHILD_COUNT; i++)
			parent->child[i] = NULL;
		parent->value = 0;
		parent->have_child = false;
	}

	if (action == "-")
	{
		std::string next;
		for (uns i = 0; i < CHILD_COUNT; i++)
		{
			if (parent->child[i] == NULL)
			{
				std::cin >> next;
				parent->child[i] = readTree(parent->child[i], next);
			}
		}
		parent->have_child = true;
	}

	else
	{
		uns num = stringToUns(action);
		parent->value = num;
	}

	return parent;
}
struct Square* Quadtree::clearTree(Square* parent)
{
	if (parent->have_child)
	{
		bool common_bool = true;
		uns common_value = parent->child[0]->value;

		for (uns i = 0; i < CHILD_COUNT; i++)
			if (parent->child[i]->value != common_value || parent->child[i]->have_child == true)
				common_bool = false;

		if (common_bool)
		{
			freeMemory(parent);

			parent = new Square;
			//std::cout << common_value << "\n";
			parent->value = common_value;

			parent->have_child = false;
			for (uns i = 0; i < CHILD_COUNT; i++)
				parent->child[i] = NULL;
		}

		if (parent->have_child)
		{
			for (uns i = 0; i < CHILD_COUNT; i++)
				parent->child[i] = clearTree(parent->child[i]);
		}

		if (parent->have_child)
		{
			bool common_bool = true;
			uns common_value = parent->child[0]->value;

			for (uns i = 0; i < CHILD_COUNT; i++)
				if (parent->child[i]->value != common_value || parent->child[i]->have_child == true)
					common_bool = false;

			if (common_bool)
				parent = clearTree(parent);
		}
	}
	return parent;
}

std::vector <std::vector <uns>> Quadtree::createMatrix(Square* parent, std::vector <std::vector <uns> > matrix, uns child_num, uns last_i, uns last_j)
{
	int lvl = (max_tree_lvl - tree_lvl - 1);
	if (lvl < 0) lvl = 0;

	uns elems_quantity = lvl * (CHILD_COUNT / 2);
	if (elems_quantity <= 0)
		elems_quantity = 1;

	uns local_i = uns(child_num / (CHILD_COUNT / 2) * elems_quantity);
	uns local_j = (child_num % (CHILD_COUNT / 2)) * elems_quantity;

	int i_start = local_i + last_i;
	int j_start = local_j + last_j;

	if (parent->have_child == false)
	{
		for (uns i = i_start; i < i_start + elems_quantity; i++)
		{
			for (uns j = j_start; j < j_start + elems_quantity; j++)
			{
				matrix[i][j] = parent->value;
			}
		}
	}
	else
	{
		tree_lvl++;
		for (uns i = 0; i < CHILD_COUNT; i++)
			matrix = createMatrix(parent->child[i], matrix, i, i_start, j_start);
		tree_lvl--;
	}
	return matrix;
}
void Quadtree::printTable(std::vector <std::vector <uns>> matrix)
{
	uns n = matrix.size();
	for (uns i = 0; i < n; i++)
	{
		for (uns j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}
std::vector <std::vector <uns>> Quadtree::readMatrix(uns n)
{
	uns elem;
	std::string elem_str;
	std::vector <std::vector <uns>> matrix;
	for (uns i = 0; i < n; i++)
	{
		std::vector <uns> row;
		for (uns j = 0; j < n; j++)
		{
			std::cin >> elem_str;
			elem = stringToUns(elem_str);
			row.push_back(elem);
		}
		matrix.push_back(row);
	}
	return matrix;
}

//public methods
Quadtree::Quadtree()
{
	this->root = NULL;
	this->tree_lvl = 0;
	this->max_tree_lvl = 0;
}
Quadtree::~Quadtree()
{
	this->freeMemory(this->root);
}

void Quadtree::buildTree()
{
	std::cout << "Quadtree its a structure, that consist of squares\n" <<
		"Big Square must be N*N elements, where N is a power of two, enter N:\n";

	std::string N;
	std::cin >> N; //clin;
	uns n = stringToUns(N);

	if (((n & (n - 1)) == 0) && n > 0 && n <= pow(2, 15))
	{
		this->clearFields();

		std::cout << "Its cool!\nNow enter matrix N*N:\n";
		this->matrix = this->readMatrix(n);
		//clin;

		std::cout << "The matrix that could be read:\n";
		this->printTable(this->matrix);

		this->root = NULL;
		this->root = this->createTree(this->root, this->matrix);

		std::cout << "\nTree construction completed successfully\n\nroot___\n";
		this->printTree(this->root);
	}
	else if (((n & (n - 1)) != 0))
		std::cout << "It is NOT a power of two, try once more.\n";
	else if (n > pow(2, 15))
		std::cout << "To big number, try make matrix smaller\n";
}
void Quadtree::buildMatrix()
{
	this->clearFields();

	std::cout << "Now enter new \"Quadtree\":\n" <<
		"1) symbol '-' will create new node with " << CHILD_COUNT << " childs\n" <<
		"then you need enter this childs\n" <<
		"if you want to enter number, just do it\n" <<
		"if you want creare in node new node read 1\n";

	std::string action;
	std::cin >> action;

	this->root = this->readTree(this->root, action);
	this->root = this->clearTree(this->root);

	std::cout << "\nTree that could be read:\nroot___\n";
	this->printTree(this->root);

	uns size = pow(2, this->max_tree_lvl - 1);
	if (size < 1) size = 1;
	for (uns i = 0; i < size; i++)
	{
		std::vector <uns> row;
		for (uns i = 0; i < size; i++)
			row.push_back(0);

		this->matrix.push_back(row);
	}

	//std::cout << "\nMatrix sizes: " << this->matrix.size() << " " << this->matrix[0].size() << "\n";
	this->matrix = this->createMatrix(this->root, this->matrix, 0, 0, 0);
	this->printTable(this->matrix);
}

struct Square* Quadtree::getRoot()
{
	return this->root;
};
std::vector <std::vector <uns>> Quadtree::getMatrix()
{
	return this->matrix;
}

void Quadtree::printRoot()
{
	if (root != NULL)
	{
		std::cout << "\nroot___\n";
		this->printTree(this->root);

	}
	else
		std::cout << "No tree\n";
}
void Quadtree::printMatrix()
{
	if (this->matrix.size() > 0)
		this->printTable(this->matrix);
	else
		std::cout << "No matrix\n";
}
