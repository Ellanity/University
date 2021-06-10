#include <iostream>
#include <vector>
#include <cmath>

#define uns unsigned
#define clout system("cls");
#define clin  rewind(stdin);
#define pause system("pause");


using namespace std;

const uns CHILD_COUNT = 4;
const uns NEW_TABLE_CHILD_RC = int(sqrt(CHILD_COUNT) - 1);

uns stringToUns(string str);

struct Square
{
public:
	uns value;
	Square* child[CHILD_COUNT];
	Square* parent;
	bool have_child;
};

class Quadtree
{
private:
	struct Square* root;
	vector <vector <uns>> matrix;
	uns tree_lvl;
	uns max_tree_lvl;


	void freeMemory(Square* square)
	{
		if (square != NULL)
		{
			for (uns i = 0; i < CHILD_COUNT; i++)
				if (square->child[i] != NULL)
					freeMemory(square->child[i]);
			delete square;
		}
	}
	void clearFields()
	{
		tree_lvl = 0;
		max_tree_lvl = 0;
		freeMemory(this->root);
		root = new Square;
		root = NULL;
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].clear();
		matrix.clear();
	}

	struct Square* createTree(Square* parent, vector <vector <uns>> table)
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
					vector <vector <uns>> new_table;

					x = new_table_child_num_R * new_table_elements_RC_quantity;
					y = new_table_child_num_C * new_table_elements_RC_quantity;


					for (uns j = y; j < y + new_table_elements_RC_quantity; j++)
					{
						vector<uns> one_row;

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
	void printTree(Square* square)
	{
		if (square != NULL)
		{
			tree_lvl++;
			if (tree_lvl >= max_tree_lvl)
				max_tree_lvl = tree_lvl;

			cout << "       ";
			if (!square->have_child)
			{
				for (uns i = 0; i < tree_lvl - 1; i++)
					cout << "    ";
				cout << "|___" << square->value << "\n";
			}

			else
			{
				for (uns i = 0; i < tree_lvl - 1; i++)
					cout << "    ";
				cout << "|___" << "\n";

				for (uns i = 0; i < CHILD_COUNT; i++)
				{

					printTree((square->child[i]));
				}
			}
			tree_lvl--;
		}
	}
	struct Square* readTree(Square* parent, string action)
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
			string next;
			for (uns i = 0; i < CHILD_COUNT; i++)
			{
				if (parent->child[i] == NULL)
				{
					cin >> next;
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

	struct Square* clearTree(Square* parent)
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
				cout << common_value << "\n";
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
			parent = clearTree(parent);
		}
		return parent;
	}

	vector <vector <uns>> createMatrix(Square* parent, vector <vector <uns> > matrix, uns child_num, uns last_i, uns last_j)
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
	void printTable(vector <vector <uns>> matrix)
	{
		uns n = matrix.size();
		for (uns i = 0; i < n; i++)
		{
			for (uns j = 0; j < n; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << "\n";
		}
	}
	vector <vector <uns>> readMatrix(uns n)
		{
			uns elem;
			string elem_str;
			vector <vector <uns>> matrix;
			for (uns i = 0; i < n; i++)
			{
				vector <uns> row;
				for (uns j = 0; j < n; j++)
				{
					cin >> elem_str;
					elem = stringToUns(elem_str);
					row.push_back(elem);
				}
				matrix.push_back(row);
			}
			return matrix;
		}

public:
	Quadtree()
	{
		this->root = NULL;
		this->tree_lvl = 0;
		this->max_tree_lvl = 0;
	}

	~Quadtree()
	{
		this->freeMemory(this->root);
	}

	void buildTree()
	{
		cout << "Quadtree its a structure, that consist of squares\n" <<
				"Big Square must be N*N elements, where N is a power of two, enter N:\n";

		string N;
		cin >> N; clin;
		uns n = stringToUns(N);

		if (((n & (n - 1)) == 0) && n > 0)
		{
			this->clearFields();

			cout << "Its cool!\nNow enter matrix N*N:\n";
			this->matrix = this->readMatrix(n);
			clin;

			cout << "The matrix that could be read:\n";
			this->printTable(this->matrix);

			this->root = NULL;
			this->root = this->createTree(this->root, this->matrix);

			cout << "\nTree construction completed successfully\n\nroot___\n";
			this->printTree(this->root);
		}
		else
			cout << "It is NOT a power of two, try once more.\n";
	}

	void buildMatrix()
	{
		this->clearFields();

		cout << "Now enter new \"Quadtree\":\n" <<
			"1) symbol '-' will create new node with " << CHILD_COUNT << " childs\n" <<
			"then you need enter this childs\n" <<
			"if you want to enter number, just do it\n" <<
			"if you want creare in node new node read 1\n";

		string action;
		cin >> action;

		this->root = this->readTree(this->root, action);
		this->root = this->clearTree(this->root);

		cout << "\nTree that could be read:\nroot___\n";		
		this->printTree(this->root);

		uns size = pow(2, this->max_tree_lvl - 1);
		if (size < 1) size = 1;
		for (uns i = 0; i < size; i++)
		{
			vector <uns> row;
			for (uns i = 0; i < size; i++)
				row.push_back(0);

			this->matrix.push_back(row);
		}

		//cout << "\nMatrix sizes: " << this->matrix.size() << " " << this->matrix[0].size() << "\n";

		this->matrix = this->createMatrix(this->root, this->matrix, 0, 0, 0);
		this->printTable(this->matrix);
	}

	struct Square* getRoot()
	{
		return this->root;
	};
	vector <vector <uns>> getMatrix()
	{
		return this->matrix;
	}

	void printRoot()
	{
		cout << "\nroot___\n";
		this->printTree(this->root);
	};
	void printMatrix()
	{
		this->printTable(this->matrix);
	}
};

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

uns stringToUns(string str)
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