#include <iostream>

using namespace std;

struct queue{
	int key;
	queue* next;
	queue* prev;

	queue();
	~queue();
	
	void push_back(int key);
	void push_front(int key);

	void print_queue();
	void print_queue_back();
	void print_element();
	
	queue* begin();
	queue* end();

	queue* find(int key);
	bool check_element(int key);
	int get_index();
	double arithmetic_mean();
};

void replacing_even_values(queue* qu, int n);


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	queue *qu = new queue; // Создание

	// Заполнение случайными числами
	int n;
	cout << "Введите длину очереди: ";  cin >> n;
	for (int i = 0; i < n; i++)
	{
		if (rand() % 2 == 0)
			qu->push_back(rand() % 200 - 100);
		else
			qu->push_front(rand() % 200 - 100);
	}

	int choice;
	do {
		system("cls");
		// Просмотр очереди
		cout << "Полученная очередь (с начала в конец): "; qu->print_queue(); cout << "\n";
		cout << "Полученная очередь (с конца в начало): "; qu->print_queue_back(); cout << "\n";

		cout << "Выберите задачу: \n" <<
			"1. Добавление элемента в начало очереди.\n" <<
			"2. Добавление элемента в конец очереди.\n" <<
			"3. Поиск элемента в очереди.\n" <<
			"4. Индивидуальное задание.\n" <<
			"5. Выход.\n";
		cout << "Выбор: "; cin >> choice;
			
		if (choice == 1) {
			int el;
			cout << "Введите элемент, для добавление в начало очереди: "; 
			cin >> el;
			qu->push_front(el);
			cout << "Элемент успешно добавлен\n";
		}
		if (choice == 2) {
			int el;
			cout << "Введите элемент, для добавление в конец очереди: "; 
			cin >> el;
			qu->push_back(el);
			cout << "Элемент успешно добавлен\n";
		}
		if (choice == 3) {
			// Поиск элемента в очереди
			int m;
			cout << "Введите значения элемента, который требуется найти: "; cin >> m;
			queue* found = qu->find(m);
			if (found != NULL)
				cout << "Найден элемент " << found->key << " с индексом " << found->get_index() << "\n";
			else
				cout << "Элемент не найден\n";
		}
		if (choice == 4) {
			double am = qu->arithmetic_mean();
			cout << "Среднее значение в очереди: " << am << "\n";
			replacing_even_values(qu, int(am));
			cout << "Все четные значения в очереди успешно заменены.\n";
		}

		system("pause");

	} while (choice != 5);
}


queue::queue() {
	key = 0;
	next = NULL;
	prev = NULL;
}
queue::~queue() {
	delete next;
	delete prev;
}

void queue::push_back(int key) {
	if (this->next == NULL) {
		queue* n = new queue;
		n->key = key;
		n->next = NULL;
		n->prev = this;
		this->next = n;
	}
	else
		this->next->push_back(key);
}
void queue::push_front(int key) {
	if (this->prev == NULL) {
		queue* n = new queue;	
		n->next = this;
		n->prev = NULL;
		this->key = key;
		this->prev = n;
	}
	else
		this->prev->push_front(key);
}

queue* queue::begin() {
	if (this->prev == NULL)
		return this;
	else
		this->prev->begin();
}
queue* queue::end() {
	if (this->next == NULL)
		return this;
	else
		this->next->end();
}

void queue::print_queue() {
	// Pointer to print
	queue* ptr = this->begin()->next;

	// Print all elements
	while (ptr != NULL) {
		ptr->print_element();
		cout << " ";
		ptr = ptr->next;
	}
}
void queue::print_queue_back() {
	// Pointer to print
	queue* ptr = this->end();

	// Print all elements
	while (ptr->prev != NULL) {
		ptr->print_element();
		cout << " ";
		ptr = ptr->prev;
	}
}
void queue::print_element() {
	cout << this->key;
}

queue* queue::find(int key) {
	if (this->begin()->next != NULL) {
		queue* ptr = this->begin()->next;
		if (ptr->check_element(key))
			while (ptr->next != NULL) {
				if (ptr->key == key)
					return ptr;
				ptr = ptr->next;
			}
	}
	else
		return NULL;
}
bool queue::check_element(int key) {
	if (this->key == key)
		return this;
	if (this->next != NULL)
		return this->next->check_element(key);
	
	return false;
}
int queue::get_index() {
	queue* ptr = this->begin();
	int i = -1;
	while (ptr != this) {
		i++;
		ptr = ptr->next;
	}
	return i;
}
double queue::arithmetic_mean() {
	queue* ptr = this->begin();
	int i = 0, sum = 0;
	while (ptr != NULL) {
		i++;
		sum += ptr->key;
		ptr = ptr->next;
	}
	return (sum / i);
}

void replacing_even_values(queue* qu, int n) {
	qu = qu->begin();
	while (qu != NULL) {
		if (qu->key % 2 == 0)
			qu->key = n;
		qu = qu->next;
	}
}