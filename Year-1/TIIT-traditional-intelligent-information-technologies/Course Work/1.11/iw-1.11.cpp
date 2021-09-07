#include <iostream>
#include <vector>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");
	int n, m;
	cout << "Количество вершин: ";	cin >> n;
	cout << "Количество ребер: ";	cin >> m;
	// cout << "Nodes quantity: ";	cin >> n;
	// cout << "Edges quantity: ";	cin >> m;

	// Заполнение двумерного вектора нулями
	// Filling a two-dimensional vector with zeros
	vector <vector <int>> graph(m, vector <int>(n, 0));

	// Заполнение матрицы инцидентности
	// Filling the incidence matrix
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--; b--;
		if (a != b && a < n && b < n && a >= 0 && b >= 0) {
			graph[i][a] = 1;
			graph[i][b] = 2;
		}
	}

	// Вывод матрицы инцидентности
	// Output of the incidence matrix
	/*for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << graph[i][j] << " ";
		cout << "\n";
	}*/

	vector <int> symmetric_edges;
	for (int i = 0; i < m; i++) {
		int p1 = 0, p2 = 0;
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == 1)
				p1 = j;
			if (graph[i][j] == 2)
				p2 = j;
		}
		if (p1 != p2)
			for (int j = 0; j < m; j++)
				if (graph[j][p1] == 2 && graph[j][p2] == 1) {
					symmetric_edges.push_back(i);
					//cout << j << " " << p1 << " " << p2 << "\n";
					break;
				}
	}

	/*for (int i = 0; i < symmetric_edges.size(); i++)
		cout << symmetric_edges[i] + 1 << " ";
	cout << "\n";*/

	int nse = symmetric_edges.size();
	if (nse == 0)
		cout << "Граф антисимметричный\n";
		// cout << "Antisymmetric graph\n";
	else if (nse != m)
		cout << "Граф частично симметричный\n";
		// cout << "Partially symmetric graph\n";
	else if (nse == m)
		cout << "Граф симметричный\n";
		// cout << "Symmetric graph\n";

	return 0;
}

/******************|
_______TESTS_______|
				   |
_PARTLY__SYMMETRIC_|
5 5
1 2
2 3
4 3
5 4
3 4 
				   |
_____SYMMETRIC_____|
4 8
1 2
2 3
3 4
4 1
1 4
4 3
3 2
2 1
				   |
___ANTISYMMETRIC___|
3 2
1 2
3 2
				   |
_____LITERATURE____|
https://habr.com/ru/post/519998/
http://khpi-iip.mipk.kharkiv.edu/library/datastr/book_sod/kgsu/din_0087.html
*******************/