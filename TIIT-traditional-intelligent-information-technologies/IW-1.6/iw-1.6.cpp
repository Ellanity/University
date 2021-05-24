#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>

// For algo
#include <vector>
#include <set>
// For tests
#include <string>
#include <cstring>
#include <fstream>

//using namespace std;
using std::string;
using std::vector;
using std::set;
//
using std::ifstream;
using std::ofstream;
using std::pair;
//
using std::to_string;
using std::strcpy;
using std::getline;
using std::make_pair;


bool run_tests();
bool dfs(int a, vector <set <int>>* adjacencies, set <int>* mark, int n);
pair <int, int> read_string(string pair);


int main(int argc, char *argv[]) {

	// For tests
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	
	bool stop_tests = false;
	if (argv[1] == NULL) {
		if (!run_tests())
			return 0;
		else {
			cin.close();
			stop_tests = true;
			cin.open("input.txt");
		}
//			cout << "Cool!\n";
	}
	
	if (argv[0] != NULL && !stop_tests) {
		try {
			ifstream file;
			file.open(argv[0]);
			if (!file)
				throw("Can't cind file");
			else {
				cin.close();
				cin.open(argv[0]);
			}
			file.close();
		}
		catch (string e) {
			cout << e << "\n";
		}
		
	}

	// Algo
	int n, m;
	string line;
	getline(cin, line);
	pair <int, int> p = read_string(line);
	n = p.first; m = p.second;

	//cout << n << " " << m << "\n";
	vector <set <int>> adjacencies;

	if (m < n) {
	cout << "No";
		cin.close();
		cout.close();
		return 0;
	}

	set <int> v;
	for (int i = 0; i < n; i++) {
		v.insert(i);
		adjacencies.push_back(v);
		v.clear();
	}

	int a, b;
	for (int i = 0; i < m; i++) {

		getline(cin, line);
		pair <int, int> p = read_string(line);
		a = p.first; b = p.second;

		a--; b--;
		if (a != b)
			adjacencies[a].insert(b);
		
		//cout << a << " " << b << "\n";
	}

	for (int i = 0; i < n; i++) {

		set <int> mark;
;		if (!dfs(i, &adjacencies, &mark, n)) {
			cout << "No";
			cin.close();
			cout.close();
			return 0;
		}
	}
	cout << "Yes";
	cin.close();
	cout.close();
	return 1;
}


bool dfs(int a, vector <set <int>>* adjacencies, set <int>* mark, int n) {

	bool was = false;
	for (int i : (*mark)) {
		if (a == i) {
			was = true;
			break;
		}
	}

	if (!was) {
		(*mark).insert(a);
		for (auto x : (*adjacencies)[a])
			if (dfs(x, adjacencies, mark, n))
				return true;
	}
	else {
		if ((*mark).size() == n)
			return true;
		else
			return false;
	}
}

bool run_tests() {

	//ofstream cout("output.txt");
	bool ok = true;
	for (int i = 1; i <= 5; i++)
	{
		ofstream cout(string(to_string(i) + "output.log" ));
		string test_name = string("tests/graph" + to_string(i) + ".txt");
		string result_name = string("tests/result" + to_string(i) + ".txt");
		try {
			cout << "test " << i << "\n";
			ifstream file;

			file.open(test_name);
			if (!file)
				throw(string("Can't find test #" + to_string(i) + "\n"));
			file.close();

			int rmb = 0;
			file.open(result_name);
			if (!file)
				throw(string("Can't find result for test #" + to_string(i) + "\n"));
			else {
				string line;
				getline(file, line);
				if (line == "Yes")
					rmb = 1;
			}
			file.close();

			cout << "Start test: " << test_name << "\n";
			char test_array[1024];
			strcpy(test_array, test_name.c_str());
			char* args[1];
			args[0] = test_array;
			int result = main(1, args);
			cout << result << " " << rmb << "\n";
			if (result != rmb) {
				cout << "Test " << i << " not passed.\n";
				return false;
			}
			cout << "end " << i << "\n";
			system("pause");
		}
		catch (string e) {
			cout << e << " ";
		}
		cout.close();
	}
	return ok;
}

pair <int, int> read_string(string p) {
	
	string f, s;
	int j = 0;
	while (p[j] != ' ')
	{
		f += p[j];
		j++;
	}
	j++;
	while (p[j] != '\0')
	{
		s += p[j];
		j++;
	}
	int n, m;
	n = stoi(f);
	m = stoi(s);
	pair <int, int> par = make_pair(n, m);
	return par;
}