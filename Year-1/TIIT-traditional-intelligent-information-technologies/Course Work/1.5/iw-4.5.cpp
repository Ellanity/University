#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
	int n, m;
	vector<vector <int>> list;
public:
	// Getters
	int get_number_of_edges() { return this->n; }
	int get_number_of_nodes() { return this->m; }
	vector<vector <int>>* get_list_of_incidents() { return &list; }

	// Functions
	void add_edge(int node1, int node2);
	void add_node(int node);
	void print_list_of_incidents();
};

Graph create_graph();

Graph composition(Graph* A, Graph* B);


int main() {

	Graph A, B;

	cout << "Create first graph:\n";
	A = create_graph();
	cout << "Create second graph:\n";
	B = create_graph();

	cout << "====================\n";
	cout << "First graph:\n";
	A.print_list_of_incidents();
	cout << "====================\n";
	cout << "Second graph:\n";
	B.print_list_of_incidents();

	cout << "====================\n";
	cout << "Composed graph:\n";
	Graph C = composition(&A, &B);
	C.print_list_of_incidents();

	return 0;
}


void Graph::add_edge(int node1, int node2)
{
	if (node1 > 0 && node2 > 0 && node1 != node2) {
		this->m++;
		this->add_node(node1);
		this->add_node(node2);
		node1--;
		node2--;
		bool nw1 = false, nw2 = false; // node was
		for (int i = 0; i < this->list[node1].size(); i++)
			if (this->list[node1][i] == node2)
				nw2 = true; 
		for (int i = 0; i < this->list[node2].size(); i++)
			if (this->list[node2][i] == node1)
				nw1 = true; 
		if (!nw2)
			this->list[node1].push_back(node2);
		if (!nw1)
			this->list[node2].push_back(node1);
	}
}

void Graph::add_node(int node)
{
	if (node > 0) {
		if (this->n <= node) {
			this->n = node;
			for (int i = this->list.size(); i < node; i++) {
				vector <int> new_node;
				this->list.push_back(new_node);
			}
		}
	}
}

void Graph::print_list_of_incidents()
{
	for (int i = 0; i < this->list.size(); i++) {
		if (this->list[i].size() > 0)
			cout << i + 1 << ": ";
		for (int j = 0; j < this->list[i].size(); j++)
			cout << this->list[i][j] + 1 << " ";
		if (this->list[i].size() > 0)
			cout << "\n";
	}
}

Graph create_graph()
{
	int n, m;
	cout << "Number of nodes: ";
	cin >> n;
	cout << "Number of edges: ";
	cin >> m;

	int node1, node2; // Вершины связанные ребром
	Graph graph;
	// Запоминание первого графа в виде списка инцидентности
	for (int i = 0; i < m; i++) {
		cin >> node1 >> node2;
		graph.add_edge(node1, node2);
	}
	return graph;
}

Graph composition(Graph* A, Graph* B) {
	// First/second list pointers
	vector < vector <int> > *flistp = A->get_list_of_incidents();
	vector < vector <int> > *slistp = B->get_list_of_incidents();
	Graph C;

	for (int i = 0; i < flistp->size(); i++) { // Для каждой вершины из А
		//cout << i + 1 << "::\n";
		for (int j = 0; j < (*flistp)[i].size(); j++) { // Просматриваем соединенные с ней вершины
			//cout << j + 1 << ":\n";
			if (slistp->size() > (*flistp)[i][j]) { // Если номер соединяемой вершины есть и В
				//cout << (*flistp)[i][j] + 1 << " | ";
				for (int h = 0; h < (*slistp)[(*flistp)[i][j]].size(); h++) { // Для этой вершины в В смотрим все соединенные с ней
					//cout << h + 1 << " - ";
					if (flistp->size() > (*slistp)[(*flistp)[i][j]][h]) { // Если соединенная вершина в В с первоначальной в В есть и в А
						//cout << "<" << i + 1 << ", " << (*slistp)[(*flistp)[i][j]][h] + 1 << ">\n";
						C.add_edge(i + 1, (*slistp)[(*flistp)[i][j]][h] + 1); // Добавляем новое ребро в график композиции с вершиной из А и В
					}
				}
			}
		}
	}

	return C;
}