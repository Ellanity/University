#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "employee.h"


using namespace std;


void showMenu();
void addEmployee();
void showEmployees(vector<Employee> *employees_);
void linearSearch(vector<Employee>* employees_);
void directSelection(vector<Employee>* employees_);
void quickSort(vector<Employee>* employees_);
void quickSortIteration(vector<Employee>* employees_, int begin, int end);
void binarySearch(vector<Employee>* employees_);


int main()
{
	setlocale(LC_ALL, "Russian");
	
	vector<Employee> employees = readFile();
	
	int choice = 0;
	while (choice != 8)
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			createFile();
			employees = readFile();
			cout << "File created\n";
			break;
		case 2:
			addEmployee();
			employees = readFile();
			break;
		case 3:
			showEmployees(&employees);
			break;
		case 4:
			linearSearch(&employees);
			break;
		case 5:
			directSelection(&employees);
			break;
		case 6:
			quickSort(&employees);
			break;
		case 7:
			binarySearch(&employees);
			break;
		case 8:
			cout << "[Exit]\n";
			break;
		default:
			choice = 8;
			break;
		}
		
		if (choice != 8)
		{
			system("pause");
			system("cls");
		}
	}
	return 0;
}


void showMenu() 
{
	cout << "[1] Creating a file with University employees.\n" <<
		"[2] Adding a University employee.\n" <<
		"[3] View University employees.\n" <<
		"[4] Linear Search.\n" <<
		"[5] Sorting by direct selection method.\n" <<
		"[6] Quicksort sorting method.\n" <<
		"[7] Binary Search in a sorted array.\n" <<
		"[8] Exit.\n";
}

void showEmployees(vector<Employee>* employees_)
{
	//vector<Employee> employees = *employees_;
	for (int employee = 0; employee < (*employees_).size(); employee++)
	{
		cout << employee + 1 << ". ";
		(*employees_)[employee].print("\n\n");
	}
}

void addEmployee()
{
	string name, faculty, department, position;
	int workload;
	cout << "Add employee:\n";
	cout << "Enter Full Name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Faculty: ";
	getline(cin, faculty);
	cout << "Enter Department: ";
	getline(cin, department);
	cout << "Enter Position: ";
	getline(cin, position);
	cout << "Enter workload: ";
	cin >> workload;
	Employee employee(name, faculty, department, position, workload);
	cout << "Employee: \n";
	employee.print("\n\n");
	vector <Employee> employees = readFile();
	employees.push_back(employee);
	writeToFile(&employees);
}

void linearSearch(vector<Employee>* employees_)
{
	vector<Employee> employees = *employees_;
	string name;
	cout << "Search by Fullname, enter fullname you want to find: ";
	cin.ignore();
	getline(cin, name);

	bool found = false;

	for (int employee = 0; employee < employees.size(); employee++)
		if (employees[employee].getName() == name)
		{
			employees[employee].print("\n\n");
			found = true;
		}
	if (!found)
		cout << "Employee not found.\n";
}

void directSelection(vector<Employee>* employees_)
{
	//vector<Employee> employees = *employees_;
	string department;
	cout << "Enter department: ";
	cin.ignore();
	getline(cin, department);
	int n = (*employees_).size();

	for (int i = 0; i < n - 1; i++)
	{
		int m = i;
		for (int j = i + 1; j < n; j++)
			if ((*employees_)[m].getWorkload() < (*employees_)[j].getWorkload())
				m = j;
		Employee e = (*employees_)[i];
		(*employees_)[i] = (*employees_)[m];
		(*employees_)[m] = e;
	}
	
	for (int i = 0; i < n; i++)
		if ((*employees_)[i].getDepartment() == department)
			(*employees_)[i].print("\n\n");
}

void quickSort(vector<Employee>* employees_)
{
	string department;
	cout << "Enter department: ";
	cin.ignore();
	getline(cin, department);
	
	int n = (*employees_).size();
	quickSortIteration(employees_, 0, n - 1);
	
	for (int i = 0; i < n; i++)
		if ((*employees_)[i].getDepartment() == department)
			(*employees_)[i].print("\n\n");
}

void quickSortIteration(vector<Employee>* employees_, int begin, int end)
{
	int l = begin, r = end;
	Employee employee = (*employees_)[int((l + r) / 2)];

	do
	{
		while ((*employees_)[l].getWorkload() > employee.getWorkload()) l++;
		while ((*employees_)[r].getWorkload() < employee.getWorkload()) r--;

		if (l <= r)
		{
			Employee k = (*employees_)[r];
			(*employees_)[r] = (*employees_)[l];
			(*employees_)[l] = k;

			l++;
			r--;
		}

	} while (l <= r);

	if (begin < r)
		quickSortIteration(employees_, begin, r);
	if (end > l)
		quickSortIteration(employees_, l, end);
}

void binarySearch(vector<Employee>* employees_)
{
	vector<Employee> employees = *employees_;
	int workload;
	cout << "Search by workload, enter workload of employee: ";
	cin >> workload;
	int n = employees.size();

	int l = 0, r = n - 1;
	
	while (l < r)
	{
		int m = int((l + r) / 2);
		Employee employee = employees[m];
		//cout << employee.getWorkload() << endl;
		if (employee.getWorkload() > workload)
		{
			//cout << "more " << m + 1 << " " << employees[(m + 1 + r) / 2].getWorkload() << endl;
			l = m + 1;

		}
		else
		{
			//cout << "less " << m << " " << employees[(m + l) / 2].getWorkload() << endl;
			r = m;
		}
		/*if (employees[m].getWorkload() == workload)
			employees[m].print("\n\n");*/
	}

	if (employees[l].getWorkload() == workload)
		employees[l].print("\n\n");
	else
		cout << "Employee not found. \n";
}

//Нет проверки на то, отсортирован ли массив для бинарного поиска
