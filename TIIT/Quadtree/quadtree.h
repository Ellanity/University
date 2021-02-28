#pragma once
#ifndef quadtree_H
#define quadtree_H

#define uns unsigned

#include <vector>
#include <string>

const uns CHILD_COUNT = 4;
const uns NEW_TABLE_CHILD_RC = int(sqrt(CHILD_COUNT) - 1);

uns stringToUns(std::string str);

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
	std::vector <std::vector <uns>> matrix;
	uns tree_lvl;
	uns max_tree_lvl;

	void freeMemory(Square* square);
	void clearFields();

	struct Square* createTree(Square* parent, std::vector <std::vector <uns>> table);
	void printTree(Square* square);
	struct Square* readTree(Square* parent, std::string action);

	struct Square* clearTree(Square* parent);

	std::vector <std::vector <uns>> createMatrix(Square* parent, std::vector <std::vector <uns> > matrix, uns child_num, uns last_i, uns last_j);
	void printTable(std::vector <std::vector <uns>> matrix);
	std::vector <std::vector <uns>> readMatrix(uns n);

public:
	Quadtree();

	~Quadtree();

	void buildTree();

	void buildMatrix();


	struct Square* getRoot();
	std::vector <std::vector <uns>> getMatrix();

	void printRoot();
	void printMatrix();
};

#endif // !1


