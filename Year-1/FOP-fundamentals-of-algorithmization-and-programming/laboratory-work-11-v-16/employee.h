#pragma once
#ifndef employee_H
#define employee_H

// Standard libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

using std::to_string;
using std::cout;
using std::cin;


class Employee
{
private:
	string name;
	string faculty;
	string department;
	string position;
	int workload;

public:
	Employee();
	Employee(string name_, string faculty_, string department_, string position_, int workload_);

	void print();
	void print(string separator);


	string getName();
	string getFaculty();
	string getDepartment();
	string getPosition();
	int getWorkload();

	void setName(string name_);
	void setFaculty(string faculty_);
	void setDepartment(string department_);
	void setPosition(string position_);
	void setWorkload(int workload_);
};


void createFile();

void writeToFile(vector <Employee> *employees_);

vector <Employee> readFile();

string encryptionEmployee(Employee employee);

Employee decryptionEmployee(string employee_str);

#endif // !1