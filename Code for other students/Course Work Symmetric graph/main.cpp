#include <iostream>
#include <vector>

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");
	int n, m;
	cout << "Количество вершин: ";	cin >> n;
	cout << "Количество ребер: ";	cin >> m;

	// Заполнение двумерного вектора нулями
	vector <vector <int>> graph(m, vector <int>(n, 0));

	// Заполнение матрицы инцидентности
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
	/*for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << graph[i][j] << " ";
		cout << "\n";
	}*/

	// Вершины[x], к которым существуют ребра из всех вершин[y],
	// К которым существуют ребра из вершин[x]
	vector<int> bfn;
	
	for (int i = 0; i < n; i++) { // Из каждой вершины цикл проверки
		//vector<int> fn; // Вершины к которым есть ребра из вершины i

		bool bfnb = true; // Подтверждение, что из всех вершин, 
						 // к которым есть ребра из i, есть обратные ребра 
		for (int j = 0; j < m; j++) { // Для каждого ребра мы проверяем
			if (graph[j][i] == 1) { // Если оно ведет из вершины i 
				for (int k = 0; k < n; k++) { // Находим в какую именно вершину k ведет
					if (graph[j][k] == 2) { // Когда находим, проверяем есть ли ребро из k в вершину i
						for (int h = 0; h < m; h++) { // Для каждого ребра смотрим 
							if (graph[h][k] == 1 && graph[h][i] == 2) {// Есть ли ребро из k, ведет ли оно в i
								bfnb = true;
								break;
							}
							bfnb = false;
						}
					}
					if (!bfnb)
						break;
				}
			}
			if (!bfnb)
				break;
		}
		
		// Если подтверждение сохранено, запоминаем вершину
		if (bfnb)
			bfn.push_back(i);
	}

	if (bfn.size() == 0)
		cout << "Граф антисимметричный";
	else if (bfn.size() != n)
		cout << "Граф частично симметричный";
	else if (bfn.size() == n)
		cout << "Граф симметричный";

	return 0;
}
