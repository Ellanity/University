#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class leaf {
private:
	int id;
	string information;
	leaf *left, *right;

public:
	leaf();
	leaf(int id_, string information_);
	~leaf();

	// Setters
	void set_id(int id_) { this->id = id_; }
	void set_information(string information_) { this->information = information_; }
	void set_left(leaf* left_) { this->left = left_; }
	void set_right(leaf* right_) { this->right = right_; }

	// Getters
	int get_id() { return this->id; }
	string get_information() { return this->information; }
	leaf*  get_left() { return this->left; }
	leaf*  get_right() { return this->right; }

	// Functions
	void  add_leaf(int id_, string information_);
	void  print_tree(int level = 0);
	leaf* find_by_id(int id_);
	leaf* find_min();
	leaf* find_max();
	void  delete_element(int id_);
	void  clear_tree();
	void  get_all_elements(vector <pair<int, string>>* vec);
	void  make_avl_tree(leaf* root, int n, int k, vector <pair<int, string>>* vec);
	void  inverse_order(int level = 0);
	int   number_of_leaves(int n = 0);
	int   tree_depth(int level = 0);

};


int main() {
	setlocale(LC_ALL, "Russina");
	srand(time(0));
	leaf *root = new leaf;
	vector <pair <int, string>> vec;

	int n;
	cout << "Number of elements in tree: "; cin >> n;
	int id_; 
	string information_;
	for (int i = 0; i < n; i++) {
		
		id_ = rand() % 99 + 1;
		information_ = to_string(id_) + to_string(id_)[0] + to_string(rand() % 10000);

		if (id_ > 0)
			root->add_leaf(id_, information_);
	}
	cout << "Tree created.\n";

	int choice = 0;
	do
	{
		system("cls");
		cout << "[1] Print tree\n"
 			 << "[2] Get info by id\n"
		 	 << "[3] Delete element by id\n"
			 << "[4] Add new element\n"
			 << "[5] Make avl tree\n"
			 << "[6] Number of leaves in left subtree\n"
			 << "[7] Elements in ascending order\n"
			 << "[8] Inverse order of elements\n"
			 << "[9] Exit\n";

		if (root->get_id() == 0)
			cout << "Tree is empty.\n";
		else
			root->print_tree();
		cout << "\n-----------------------\n";
		cin >> choice;
		cout << "-----------------------\n";

		if (choice == 1) {
			if (root->get_id() == 0)
				cout << "Tree is empty.\n";
			else
				root->print_tree();
		}
		if (choice == 2) {
			cout << "Enter ID: "; cin >> id_;
			leaf* found = root->find_by_id(id_);
			if (found != NULL)
				cout << "ID: " << found->get_id() << " INFO: " << found->get_information() << "\n";
			else
				cout << "Such ID doesn't exist.\n";
		}
		if (choice == 3) {
			cout << "Enter ID: "; cin >> id_;
			leaf* found = root->find_by_id(id_);
			if (found != NULL) {
				root->delete_element(id_);
			}
			else
				cout << "Such ID doesn't exist.\n";
		}
		if (choice == 4) {
			cout << "Create new element: \n";
			cout << " ID: "; cin >> id_;
			cout << " Information: "; cin >> information_;
			if (id_ > 0)
				root->add_leaf(id_, information_);
			if (root->find_by_id(id_) != NULL)
				cout << "Element added.\n";
		}
		if (choice == 5) {
			vec.clear();
			root->get_all_elements(&vec);
			root->clear_tree();
			root->make_avl_tree(root, 0, vec.size(), &vec);
		}
		if (choice == 6) {
			int a = root->get_left()->number_of_leaves();
			cout << "Number of leaves in left subtree: " << a << "\n";
		}
		if (choice == 7) {
			vec.clear();
			root->get_all_elements(&vec);
			for (int i = 0; i < vec.size(); i++) {
				cout << vec[i].first << " " << vec[i].second << "\n";
			} // All elements from tree
		}
		if (choice == 8) {
			root->inverse_order(root->tree_depth());
		}
		if (choice == 9) {
			choice == 0;
		}

		system("pause");

	} while (choice != 0 && choice != 9);

	root->print_tree();
	delete root;
	return 0;
}


leaf::leaf() {
	this->id = 0;
	this->information = "";
	//this->left = this->right = this->previous = NULL;
}

leaf::leaf(int id_, string information_)
{
	this->id = id_;
	this->information = information_;
	//this->left = this->right = this->previous = NULL;
}

leaf::~leaf() {
	if (this->left)
		delete this->left;
	if (this->left)
		delete this->right;
}

void  leaf::add_leaf(int id_, string information_)
{
	leaf *prev = NULL, *new_leaf = this;
	bool find = true;

	if (this->id == 0) {
		this->id = id_;
		this->information = information_;
		return;
	}
	
	while (new_leaf && find) {
		if (id_ == new_leaf->get_id()) {
			find = false;
			cout << "Dublucate Key!\n";
			break;
		}
		else {
			prev = new_leaf;
			if (id_ < new_leaf->get_id())
				new_leaf = new_leaf->left;
			else
				new_leaf = new_leaf->right;
		}
	}
	
	if (find) {
		if (prev != NULL) {
			new_leaf = new leaf;
			new_leaf->set_id(id_);
			new_leaf->set_information(information_);
			if (id_ < prev->get_id())
				prev->left = new_leaf;
			else
				prev->right = new_leaf;
		}
		else {;
			this->id = id_;
			this->information = information_;
		}
	}
}

void  leaf::print_tree(int level)
{
	if (this) {
		// Right subtree
		if (this->right != NULL)
			this->right->print_tree(level + 1);
		
		// Print actual id
		for (int i = 0; i < level; i++) 
			cout << "    ";
		cout << this->id << "\n";

		// Left subtree
		if (this->left != NULL)
			this->left->print_tree(level + 1);
	}
}

leaf* leaf::find_by_id(int id_)
{
	leaf* ret = NULL;
	if (this) {	
		// cout << this->id << "\n"; // Way to element
		if (this->id == id_)
			ret = this;

		else if (this->id > id_)
			ret = this->left->find_by_id(id_);
		else
			ret = this->right->find_by_id(id_);	
	}
	return ret;
}

leaf* leaf::find_min()
{
	if (this) {
		leaf* p = this;
		while (p->get_left() != NULL)
			p = p->get_left();
		return p;
	}
}

leaf* leaf::find_max()
{
	if (this) {
		leaf* p = this;
		while (p->get_right() != NULL)
			p = p->get_right();
		return p;
	}
}

void  leaf::delete_element(int id_)
{
	// Del, Prev_Del – удаляемый узел и его предыдущий (предок); 
	leaf *Del = this, *Prev_Del = NULL; 
	// R, Prev_R – элемент, на который заменяется удаляемый, и его предок;
	leaf *R, *Prev_R;

	/*****************_Поиск_удаляемого_элемента_и_его_предка_по_ключу_id_*****************/
	while (Del != NULL && Del->get_id() != id_) {
		Prev_Del = Del;
		if (Del->get_id() > id_)
			Del = Del->get_left();
		else
			Del = Del->get_right();
	}
	// Элемент не найден
	if (Del == NULL) { 
		cout << "Such ID doesn't exist!";
		return;
	}

	/**********************_Поиск_элемента_R_для_замены_**********************/
	if (Del->get_right() == NULL)		// Если в поддереве есть только левая ветвь
		R = Del->get_left();			// Поднимаем на 1 уровень ветвь
	else {
		if (Del->get_left() == NULL)	// Если в поддереве есть только правая ветвь
			R = Del->get_right();
		
		else {							// В поддереве есть обе ветви
			
			/****_Ищем_самый_правый_узел_в_левом_поддереве_и_его_предок_****/
			Prev_R = Del;
			R = Del->get_left();
			while (R->get_right() != NULL) {
				Prev_R = R;
				R = R->get_right();
			}

			/****_Формируем_связи_элемента_R_и_его_предка_Prev_R_****/
			if (Prev_R == Del)
				R->set_right(Del->get_right());
			else {
				R->set_right(Del->get_right());
				Prev_R->set_right(R->get_left());
				R->set_left(Del->get_left());
			}
		}
	}

	if (Del == this) { // Удаляя корень, заменяем его на R
		if (R) {
			this->id = R->get_id();
			this->information = R->get_information();
			this->left = R->get_left();
			this->right = R->get_right();
		}
		else {
			this->id = 0;
			this->information = "";
			this->left = this->right = NULL;
		}
		return;
	}

	else {
		//--------------- Поддерево R присоединяем к предку удаляемого узла ----------------
		if (Del->get_id() < Prev_Del->get_id())
			Prev_Del->set_left(R);	// На левую ветвь
		else
			Prev_Del->set_right(R);	// На правую ветвь
	}
	
	delete Del;
}

void  leaf::clear_tree()
{
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;

	this->id = 0;
	this->information = "";
	this->left = NULL;
	this->right = NULL;
}

void  leaf::get_all_elements(vector<pair<int, string>>* vec)
{
	if (this) {
		// Left subtree
		if (this->left != NULL)
			this->left->get_all_elements(vec);
		
		// Add element to vector
		pair <int, string> p = make_pair(this->id, this->information);
		vec->push_back(p);
		
		// Right subtree
		if (this->right != NULL)
			this->right->get_all_elements(vec);
	}
}

void  leaf::make_avl_tree(leaf* root, int n, int k, vector<pair<int, string>>* vec)
{
	if (n == k) {
		return;
	}
	else {
		int m = (n + k) / 2;

		this->add_leaf((*vec)[m].first, (*vec)[m].second);

		make_avl_tree(root, n, m, vec);
		make_avl_tree(root, m + 1, k, vec);
	}
}

void  leaf::inverse_order(int level)
{
	if (!this)
		return;
	
	if (this->right)
		this->right->inverse_order(level - 1);
	
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << this->id << "\n";
	
	if (this->left)
		this->left->inverse_order(level - 1);
	
	
}

int   leaf::number_of_leaves(int n)
{
	n = 0;
	if (this->left == NULL && this->right == NULL)
		n++;
	if (this->left != NULL)
		n += this->left->number_of_leaves();
	if (this->right != NULL)
		n += this->right->number_of_leaves();
	return n;
}

int   leaf::tree_depth(int level)
{
	int n = 1;
	if (this) {
		if (this->left && !this->right)
			n += this->left->tree_depth();
		else if (!this->left && this->right)
			n += this->right->tree_depth();
		else if (this->left && this->right)
			n += max(this->right->tree_depth(), this->left->tree_depth());
	}
	return n;
}
 