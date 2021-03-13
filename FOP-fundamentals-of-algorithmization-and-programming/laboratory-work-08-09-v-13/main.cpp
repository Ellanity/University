#include <iostream>
#include <fstream>   /*для работы с потоками*/
#include <Windows.h> /*Установка русского языка в консоли*/
#include <string>

#include <vector>
#include <set>
//#include <stdio.h>    /*описаны прототипы большинства*/
//#include <io.h>       /*функций по обработке файлов  */

#define clout system("cls"); //очистка потока вывода
#define clin  rewind(stdin); //очистка потока ввода
#define pause system("pause");

using namespace std;

struct Marks //структура = шаблон Оценок
{
private:
	int physics;
	int mathematics;
	int computerScience;
	int chemistry;
	float average;

public:
	Marks()  //конструктор по умолчанию 
	{
		physics = 10;
		mathematics = 10;
		computerScience = 10;
		chemistry = 10;
		average = 10;  //присваивает всем полям одинаковое значение
	}

	Marks(int phys, int math, int comp, int chem)  //конструктор, если значения были переданы
	{
		if (phys < 1) phys = 1; if (phys > 10) phys = 10;
		if (math < 1) math = 1; if (math > 10) math = 10;
		if (comp < 1) comp = 1; if (comp > 10) comp = 10;
		if (chem < 1) chem = 1; if (chem > 10) chem = 10;

		physics = phys;
		mathematics = math;
		computerScience = comp;
		chemistry = chem;
		average = (phys + math + comp + chem) / 4.0;  //присваивает полям, переданные значения
	}

	/* Так как все поля структуры имеют модификатор доступа private */
	/* Требуется создать getters и setters для изменения полей      */
	void changeAverage() { average = (physics + mathematics + computerScience + chemistry) / 4.0; }

	int getPhysics() { return physics; }
	int getMathematics() { return mathematics; }
	int getComputerScience() { return computerScience; }
	int getChemistry() { return chemistry; }
	float getAverage() { return average; }

	void setPhysics(int phys) { physics = phys; changeAverage(); }
	void setMathematics(int math) { mathematics = math; changeAverage(); }
	void setComputerScience(int comp) { computerScience = comp; changeAverage(); }
	void setChemistry(int chem) { chemistry = chem; changeAverage(); }
};
struct Student //структура = шаблон Студента
{
private:
	string name;
	string lastName;
	string middleName;

	int year;
	string group;

	Marks marks;

public:
	Student()
	{
		name = "Иван";
		lastName = "Иванов";
		middleName = "Иванович";

		year = 2002;
		group = "021703";
	}

	Student(string sName, string sLastName, string sMiddleName, int sYear, string sGroup, Marks sMarks)
	{
		name = sName;
		lastName = sLastName;
		middleName = sMiddleName;

		year = sYear;
		group = sGroup;

		marks = sMarks;
	}

	string getName() { return name; }
	string getLastName() { return lastName; }
	string getMiddleName() { return middleName; }
	int getYear() { return year; }
	string getGroup() { return group; }
	Marks getMarks() { return marks; }

	void setName(string sName) { name = sName; }
	void setLastName(string sLastName) { lastName = sLastName; }
	void setMiddleName(string sMiddleName) { middleName = sMiddleName; }
	void setYear(int sYear) { year = sYear; }
	void setGroup(string sGroup) { group = sGroup; }
	void setMarks(Marks sMarks) { marks = sMarks; }
};


void RussianLanguage();
int stringToInt(string str);

Student NewStudent();
void studentInformation(Student* student);

vector <Student> getInformationFile();
void setInformationFile(vector <Student>* studentsPtr);
void deleteStudent(vector <Student>* studentsPtr, int id);

void additionalTask(vector <Student>* studentsPtr);


int main()
{
	RussianLanguage();

	string menuButton;
	vector <Student> students;
	students = getInformationFile();

	while (true)
	{
		clout; clin;
		cout << "Выберите, что надо сделать: " << "\n" <<
			"1. Cоздать    нового студента" << "\n" <<
			"2. Просмотр   списка студентов" << "\n" <<
			"3. Коррекция  данных определенного студента" << "\n" <<
			"4. Удаление   студента из таблицы" << "\n" <<
			"5. Решение индивидуального задания" << "\n" <<
			"6. Выход из программы" << "\n";
		cin >> menuButton; clout;

		if (menuButton == "1")
		{
			clout;
			students.push_back(NewStudent());
			pause;
			setInformationFile(&students);
		}
		else if (menuButton == "2")
		{
			for (int i = 0; i < students.size(); i++)
			{
				cout << i + 1 << ") ";
				studentInformation(&students[i]);
				cout << '\n';
			}
			if (students.size() == 0)
				cout << "Нет добавленных студентов\n";
			pause;
		}
		else if (menuButton == "3")
		{
			int sNum;
			cout << "Введите номер студента, информация которого требует поправок(<" << (students.size() + 1) << "):\n";
			cin >> sNum; sNum--;
			if (sNum < 0 || sNum >= students.size())
				cout << "Такого студента нет\n";
			else
			{
				studentInformation(&students[sNum]);
				students[sNum] = NewStudent();
				setInformationFile(&students);
			}
			pause;
		}
		else if (menuButton == "4")
		{
			int sNum;
			cout << "Введите номер студента которого требуется удалить:\n";
			cin >> sNum; sNum--;
			if (sNum < 0 || sNum >= students.size())
				cout << "Такого студента нет\n";
			else
			{
				deleteStudent(&students, sNum);
				students = getInformationFile();
				cout << "Студент успешно удален\n";
			}
			pause;
		}
		else if (menuButton == "5")
		{
			additionalTask(&students);
		}
		else if (menuButton == "6") return 0;

		else { cout << "Нет такой команды\n"; pause; }
	}
	return 0;
}

/*Простые операции с классом Student*/
Student NewStudent()
{
	cout << "Создание нового студента, выполняйте инструкции ниже." << "\n";

	string sName, sLastName, sMiddleName;
	cout << "Введите имя, фамилию, отчество студента (все с новой строки):" << "\n";
	cin >> sName; clin; cin >> sLastName; clin; cin >> sMiddleName; clin;


	int sYear;
	cout << "Введите год рождения студента:" << "\n";
	cin >> sYear; clin;
	if (sYear < 1921) sYear = 1921; if (sYear > 2021) sYear = 2021;

	string sGroup;
	cout << "Введите группу студента:" << "\n";
	cin >> sGroup; clin;

	int phys, math, comp, chem;
	cout << "Введите оценки по физике, математике, информатике, химии (все с новой строки):" << "\n";
	cin >> phys; clin; cin >> math; clin; cin >> comp; clin; cin >> chem; clin;

	Marks sMarks(phys, math, comp, chem);
	Student student(sName, sLastName, sMiddleName, sYear, sGroup, sMarks);

	clout;
	cout << "Иформация о студенте, которого вы добавили:" << "\n";
	studentInformation(&student);
	return student;
}
void studentInformation(Student* studentPtr)
{
	Student student = *studentPtr;
	cout << student.getName() << " " << student.getLastName() << " " << student.getMiddleName() <<
		" Год рождения: " << student.getYear() << " Учебная группа: " << student.getGroup() << "\n" <<
		"Физика: " << student.getMarks().getPhysics() << " " <<
		"Математика: " << student.getMarks().getMathematics() << " " <<
		"Информатика: " << student.getMarks().getComputerScience() << " " <<
		"Химия: " << student.getMarks().getChemistry() << "\n" <<
		"Средняя оценка: " << student.getMarks().getAverage() << "\n";
}

/*Сложные операции с классом Student. Сохранение в файл. Парсинг файла в вектор*/
vector <Student> getInformationFile()  //Парсинг информации из файла в вектор
{
	vector <Student> students;

	ifstream fin("students.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			string sName, sLastName, sMiddleName, sGroup;
			int sYear, phys, math, comp, chem;

			int counter = 0, flag = 0;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					string str = "";
					for (int j = flag; j < i; j++)
					{
						str += line[j];
					}
					if (counter == 0) sName = str;
					if (counter == 1) sLastName = str;
					if (counter == 2) sMiddleName = str;
					if (counter == 3) sYear = stringToInt(str);
					if (counter == 4) sGroup = str;
					if (counter == 5) phys = stringToInt(str);
					if (counter == 6) math = stringToInt(str);
					if (counter == 7) comp = stringToInt(str);
					if (counter == 8) chem = stringToInt(str);
					counter++;
					flag = i + 1;
				}
			}
			Marks sMarks(phys, math, comp, chem);
			Student student(sName, sLastName, sMiddleName, sYear, sGroup, sMarks);
			students.push_back(student);
		}
	}
	else
	{
		cout << "Невозможно открыть файл\n";
	}
	fin.close();

	return students;
}
void setInformationFile(vector <Student>* studentsPtr)
{
	ofstream fout("students.txt");
	vector <Student> students = *studentsPtr;
	if (fout.is_open())
	{
		for (int i = 0; i < students.size(); i++)
		{
			string str = students[i].getName() + " " +
				students[i].getLastName() + " " +
				students[i].getMiddleName() + " " +
				to_string(students[i].getYear()) + " " +
				students[i].getGroup() + " " +
				to_string(students[i].getMarks().getPhysics()) + " " +
				to_string(students[i].getMarks().getMathematics()) + " " +
				to_string(students[i].getMarks().getComputerScience()) + " " +
				to_string(students[i].getMarks().getChemistry()) + " " +
				to_string(students[i].getMarks().getAverage()) + "\n";
			fout << str;
		}
	}
	fout.close();
}
void deleteStudent(vector <Student>* studentsPtr, int id)
{
	ofstream fout("students.txt");
	vector <Student> students = *studentsPtr;
	if (fout.is_open())
	{
		for (int i = 0; i < students.size(); i++)
		{
			if (i != id)
			{
				string str = students[i].getName() + " " +
					students[i].getLastName() + " " +
					students[i].getMiddleName() + " " +
					to_string(students[i].getYear()) + " " +
					students[i].getGroup() + " " +
					to_string(students[i].getMarks().getPhysics()) + " " +
					to_string(students[i].getMarks().getMathematics()) + " " +
					to_string(students[i].getMarks().getComputerScience()) + " " +
					to_string(students[i].getMarks().getChemistry()) + " " +
					to_string(students[i].getMarks().getAverage()) + "\n";
				fout << str;
			}
		}
	}
	fout.close();
}

/*Дополнительные функции*/
void RussianLanguage()
{
	//setlocale(LC_CTYPE, "rus"); // вызов функции настройки локали
	SetConsoleCP(1251);			// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);	// установка кодовой страницы win-cp 1251 в поток вывода
}
int stringToInt(string str)
{
	int ans = 0;
	for (int i = 0; i < str.size(); i++)
	{
		ans *= 10;
		ans += str[i] - '0';
	}
	return ans;
}

/*Вычислить общий средний балл студентов интересующей вас группы и
распечатать список студентов этой группы, имеющих средний балл выше общего.*/
void additionalTask(vector <Student>* studentsPtr)
{
	vector <Student> students = *studentsPtr;
	set <string> groups;  //список всех групп содержащихся в файеле

	for (int i = 0; i < students.size(); i++)
		groups.insert(students[i].getGroup());

	cout << "Введите группу, которая вас интересует:\n";

	set <string> ::iterator it = groups.begin();  //итератор для вывода значений из сета
	for (int i = 0; it != groups.end(); i++, it++)
		cout << *it << " ";
	cout << "\n";

	string group; //введенная группа
	cin >> group;

	float averageInGroup = 0;
	int studentsCount = 0;

	vector <Student> needStudents;
	for (int i = 0; i < students.size(); i++)
	{
		if (students[i].getGroup() == group)
		{
			needStudents.push_back(students[i]);
			studentsCount++;
			averageInGroup += students[i].getMarks().getAverage();
		}
	}
	averageInGroup /= studentsCount;

	if (studentsCount != 0)
		cout << "\nСредний балл в данной группе: " << averageInGroup << "\n\n";

	cout << "Список студентов, чей средний балл выше среднего(или равен): \n\n";
	int goodCount = 1;
	for (int i = 0; i < studentsCount; i++)
	{
		if (needStudents[i].getMarks().getAverage() >= averageInGroup)
		{
			cout << goodCount + ") ";
			studentInformation(&needStudents[i]);
			cout << "\n";
			goodCount++;
		}
	}

	if (studentsCount == 0)
		cout << "В этой группе нет студентов. Ну или нет такой группы вовсе.\n";
	pause;
}

/*Работа с файлом (синтаксис Си), не доделано, тк через потоки легче*/
/*и зачем отказывать от благ цивилизации*/
/*
{
	vector <Student> students;

	FILE* file;  //создание указателя на файл
	if (!(fopen_s(&file, "students.txt", "r")))  //открытие файла +
	{ cout << "Невозможно открыть файл \n"; }  //проверка
	else
	{
		char sNameC[50], sLastNameC[50], sMiddleNameC[50], sGroupC[10];
		string sName, sLastName, sMiddleName, sGroup;
		int sYear, phys, math, comp, chem;
		float average;

		int i = 0;
		while (fscanf_s(file, "%s%s%s%d%s%d%d%d%d%f",
			sNameC, sLastNameC, sMiddleNameC, &sYear, sGroupC,
			&phys, &math, &comp, &chem, &average) != EOF)
		{

			sName = string(sNameC);
			sLastName = string(sLastNameC);
			sMiddleName = string(sMiddleNameC);
			sGroup = string(sGroupC);

			Marks marks(phys, math, comp, chem);
			Student student(sName, sLastName, sMiddleName, sYear, sGroup, marks);
			students.push_back(student);
			studentInformation(students[i]);
			i++;
		}
		fclose(file);
		return students;
}*/