#include <iostream>

using namespace std;


struct stack
{
	int key;
	stack* prev;

	stack();
	~stack();

	void push(int key);
	int peek();
	int pop();
	int size();

	void slow_sort();
	void slow_sort_step();
};

void fast_sort(stack* st);
void fast_sort_step(stack* st);
void print_stack(stack* st);

bool check_stack();
double arithmetic_mean(stack* st);
void replacing_even_values(stack* st, int n);


int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	if (!check_stack()) {
		cout << "Stack doesn't work correctly";
		return 0;
	}

	// Programm main part
	int a, b;
	cout << "Введите размер стека: "; cin >> a;
	stack st;

	for (int i = 0; i < a; i++)
	{
		//cin >> b;
		b = rand() % 200 - 100;
		st.push(b);
	}

	int choice = 0;
	do {
		system("cls");

		// Output of the resulting stack
		cout << "Cтек: "; print_stack(&st); cout << "\n";
		cout << "Размер: " << st.size() << "\n";

		// Sort stack
		cout << "Выберите задачу:\n" <<
			"1. Добавить элемент в стек.\n" <<
			"2. Удалить элемент из стека.\n" <<
			"3. Сортировка. Обмен элементов ключами.\n" <<
			"4. Сортировка. Обмен ссылок на элементы\n" <<
			"5. Индивидуальное задание.\n" <<
			"6. Выход.\n";
		cout << "Выбор: ";  cin >> choice;

		if (choice == 1) {
			int el;
			cout << "Введите элемент: "; 
			cin >> el;
			st.push(el);
			cout << "Элемент добавлен в стек\n";
		}
		if (choice == 2) {
			cout << "Элемент " << st.pop() << " удален из стека\n";
		}
		if (choice == 3 && st.size() > 0) {
			st.slow_sort();	// Sort TYPE-1
			cout << "Стек отсортирован\n";
		}
		if (choice == 4 && st.size() > 0) {
			fast_sort(&st); // Sort TYPE-2
			cout << "Стек отсортирован\n";
		}
		if (choice == 5) {
			// Get arithmetic mean from stack values
			double arithmetic_mean_num = arithmetic_mean(&st);
			cout << "Среднее арифметическое в стеке: " << arithmetic_mean_num << "\n";

			// Replace even values in stack with arithmetic mean
			replacing_even_values(&st, int(arithmetic_mean_num));
			//cout << "Стек с замененными значениями: "; print_stack(&st); cout << "\n";
			cout << "Значения в стеке заменены\n";
		}
		system("pause");

	} while (choice != 6);
	
	return 0;
}


// Implementing stack functions
stack::stack() {
	this->key = 0;
	this->prev = NULL;
}
stack::~stack() {
	/*if (this->prev != NULL)
		this->prev->~stack();*/
	delete this->prev;
}

void stack::push(int key) {
	stack* n = new stack;
	n->key = this->key;
	n->prev = this->prev;
	this->key = key;
	this->prev = n;
	//cout << "n: " << n->key << " " << n->prev << " this: " << this << " ";
}
int stack::peek() {
	return this->key;
}
int stack::pop() {
	if (this->prev != NULL) {
		int key = this->key;
		this->key = this->prev->key;
		this->prev = this->prev->prev;
		return key;
	}
	else {
		int	key = this->key;
		//this = NULL;
		return key;
	}
}
int stack::size() {
	int n = 0;
	if (this->prev != NULL) {
		n++;
		n += this->prev->size();
	}
	return n;
}
void stack::slow_sort() {
	for (int i = 0; i < this->size(); i++)
		this->slow_sort_step();
}
void stack::slow_sort_step() {
	if (this->prev->prev != NULL) {
		if (this->key > this->prev->key) {
			int key = this->key;
			this->key = this->prev->key;
			this->prev->key = key;
		}
		//cout << this->key << " " << this->prev->key << "\n";
		this->prev->slow_sort_step();
	}
}

void fast_sort(stack* st) {
	// Without an additional element
	// the first element of the stack will not be sorted
	st->push(0);

	for (int i = 0; i < st->size(); i++)
		fast_sort_step(st);

	// Delete extra element
	st->pop();
}
void fast_sort_step(stack* st) {
	if (st->prev->prev->prev != NULL) {
		if (st->prev->key > st->prev->prev->key) {
			//cout << st->key << " " << st->prev->key << " " << st->prev->prev->key << "\n";
			stack* p1 = st->prev;
			st->prev = st->prev->prev;
			stack* p3 = st->prev->prev;
			st->prev->prev = p1;
			st->prev->prev->prev = p3;
			//cout << st->key << " " << st->prev->key << " " << st->prev->prev->key << "\n\n";
		}
		fast_sort_step(st->prev);
	}
}
void print_stack(stack* st) {
	if (st->prev != NULL) {
		cout << st->key << " ";
		print_stack(st->prev);
	}
}
bool check_stack() {

	stack st;

	st.push(9); st.push(1); st.push(4);  st.push(3); st.push(5);
	st.push(6); st.push(7); st.push(10); st.push(2); st.push(8);

	//print_stack(&st);
	//cout << "\n";
	if (st.size() != 10)
		return false;

	for (int i = 0; i < 3; i++)
		st.pop();
	//cout << st.pop() << " ";
//cout << "\n";

//cout << st.size() << "\n";
	if (st.size() != 7)
		return false;

	//cout << st.peek() << "\n";
	if (st.peek() != 7)
		return false;
	st.slow_sort();

	//cout << st.peek() << "\n";
	if (st.peek() != 1)
		return false;

	//print_stack(&st);
	//cout << "\n";
	return true;
}

// Additional task
double arithmetic_mean(stack* st){
	double n = st->key;
	if (st->prev != NULL) {
		double a = arithmetic_mean(st->prev);
		int elc = st->prev->size();
		n = (a * elc + n) / (elc + 1);
	}
	return n;
}
void replacing_even_values(stack* st, int n) {
	if (st->key % 2 == 0)
		st->key = n;
	if (st->prev != NULL)
		replacing_even_values(st->prev, n);
}