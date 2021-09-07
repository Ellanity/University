#include "employee.h"
const string SEPARATOR = "&&";

Employee::Employee()
{
	name = "Ivanov Ivan Ivanovich";
	faculty = "Faculty of Information Technology and Management";
	department = "Department of Computer Science";
	position = "Head";
	workload = 160;
}

Employee::Employee(string name_, string faculty_, string department_, string position_, int workload_)
{
	name = name_;
	faculty = faculty_;
	department = department_;
	position = position_;
	workload = workload_;
}


void Employee::print()
{
	cout << "Name: " << name <<
		"\nFaculty: " << faculty <<
		"\nDepartment: " << department <<
		"\nPosition: " << position <<
		"\nWorkload: " << workload;
}

void Employee::print(string separator)
{
	cout << "Full Name: " << name <<
		"\nFaculty: " << faculty <<
		"\nDepartment: " << department <<
		"\nPosition: " << position <<
		"\nWorkload: " << workload << separator;

	/*cout << "ФИО: " << name <<
		"\nФакультет: " << faculty <<
		"\nКафедра: " << department <<
		"\nДолжность: " << position <<
		"\nРабочая нагрузка(часы): " << workload << separator;*/
}


string Employee::getName()
{
	return string(name);
}
string Employee::getFaculty()
{
	return string(faculty);
}
string Employee::getDepartment()
{
	return string(department);
}
string Employee::getPosition()
{
	return string(position);
}
int Employee::getWorkload()
{
	return workload;
}


void Employee::setName(string name_)
{
	name = name_;
}
void Employee::setFaculty(string faculty_)
{
	faculty = faculty_;
}
void Employee::setDepartment(string department_)
{
	department = department_;
}
void Employee::setPosition(string position_)
{
	position = position_;
}
void Employee::setWorkload(int workload_)
{
	workload = workload_;
}


void createFile()
{
	ofstream fout("employees.txt");

	/*if (fout.is_open())
		cout << "File was created.\n";
	else
		cout << "File was not created.\n";*/

	fout.close();
}

void writeToFile(vector <Employee> *employees_)
{
	vector <Employee> employees = *employees_;
	ofstream fout("employees.txt");

	if (fout.is_open())
	{
		for (int employee = 0; employee < employees.size(); employee++)
		{
			string employee_str = encryptionEmployee(employees[employee]);
			fout << employee_str << "\n";
		}
		//cout << "Employees were written to a file.\n";
	}
	else
		cout << "Employees were not written to a file.\n";

	fout.close();
}

vector<Employee> readFile()
{
	ifstream fin("employees.txt");
	vector <Employee> employees;

	if (fin.is_open())
	{	
		string line;
		while (getline(fin, line))
		{
			Employee employee = decryptionEmployee(line);
			employees.push_back(employee);
		}
		//cout << "Employees were read from a file.\n";
	}
	else
		cout << "Employees were not read from a file.\n";

	fin.close();
	return employees;
}

string encryptionEmployee(Employee employee)
{
	string employee_str = employee.getName() + SEPARATOR +
		employee.getFaculty() + SEPARATOR +
		employee.getDepartment() + SEPARATOR + 
		employee.getPosition() + SEPARATOR + 
		to_string(employee.getWorkload()) + SEPARATOR;

	return string(employee_str);
}

Employee decryptionEmployee(string employee_str)
{
	Employee employee;
	int counter = 0;  // How many separators we met
	int last_argument_end = 0;
	for (int i = 0; i < employee_str.size(); i++)
	{
		// Checking the substring (SEPARATOR in employee_str)
		bool met = true;
		for (int sl = 0; sl < SEPARATOR.size(); sl++)
		{
			if (employee_str[i + sl] != SEPARATOR[sl])
				met = false;
		}

		// Argument allocation
		if (met == true)
		{
			counter++;

			string argument;
			for (int j = last_argument_end; j < i; j++)
				argument += employee_str[j];

			switch (counter)
			{
			case 1:
				employee.setName(argument);
				break;
			case 2:
				employee.setFaculty(argument);
				break;
			case 3:
				employee.setDepartment(argument);
				break;
			case 4:
				employee.setPosition(argument);
				break;
			case 5:
				employee.setWorkload(stoi(argument));
				break;
			default:
				break;
			}

			last_argument_end = i + SEPARATOR.size();
		}
	}
	return employee;
}