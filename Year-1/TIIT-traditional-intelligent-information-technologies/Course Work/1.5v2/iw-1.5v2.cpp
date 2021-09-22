#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string INPUT_FILE = "input.txt";
string OUTPUT_FILE = "output.txt";

class Graph {
private:
    int __nodes, __edges;
    vector <vector <int>> __list;

public:
    Graph();
    Graph(int nodes, int edges);

    void add_edge(int first_node, int second_node, int index);
    void add_node(int node);
    void print();
    friend Graph composition(Graph& first, Graph& second);
    int find_node(int first_node, int edge);
    bool check_relationship(int first_node, int second_node);
};


int main(int argc, char* argv[]) 
{
    if (argv[1])
        INPUT_FILE = argv[1];

    ofstream file(OUTPUT_FILE.c_str());
    freopen(INPUT_FILE.c_str(), "r", stdin);
    //freopen("output.txt", "w", stdout);

    int nodes, edges;
    //cout << "Number of nodes: "; 
    cin >> nodes;
    //cout << "Number of edges: "; 
    cin >> edges;
    Graph A(nodes, edges);
    //cout << "Number of nodes: "; 
    cin >> nodes;
    //cout << "Number of edges: ";
    cin >> edges;
    Graph B(nodes, edges);
    /* cout << "====================\n";
    cout << "First graph:\n";
    A.print();
    cout << "====================\n";
    cout << "Second graph:\n";
    B.print();
    cout << "====================\n";
    cout << "Composed graph:\n"; */

    Graph C = composition(A, B);
    C.print();

    return 0;
}


Graph composition(Graph& A, Graph& B)
{
    int i, j, ii, jj, edges_count = 0;
    Graph C;
    for (i = 0; i < A.__list.size(); i++)
    {
        for (j = 0; j < A.__list[i].size(); j++)
        {
            // Поиск соответсвующей вершины для ребра A.__list[i][j]
            int first_node = i;
            int second_node = A.find_node(first_node, A.__list[i][j]);

            // cout << "in A edge between: " << first_node << " " << second_node << "\n";
            if (B.__list.size() > first_node)
            {
                // cout << B.__list[first_node].size() << "\n";
                for (jj = 0; jj < B.__list[first_node].size(); jj++)
                {
                    int third_node = B.find_node(first_node, B.__list[first_node][jj]);
                    // cout << "in B 1edge between: " << first_node << " " << third_node << "\n";
                    int edges_before = C.__edges;
                    C.add_edge(second_node, third_node, edges_count);
                    if (C.__edges > edges_before)
                    {
                        // cout << "new edge in C: " << second_node << " " << third_node << "\n";
                        edges_count++;
                    }
                }
            }
            if (B.__list.size() > second_node)
            {
                for (jj = 0; jj < B.__list[second_node].size(); jj++)
                {
                    int third_node = B.find_node(second_node, B.__list[second_node][jj]);
                    // cout << "in B 2edge between: " << second_node << " " << third_node << "\n";
                    int edges_before = C.__edges;
                    C.add_edge(first_node, third_node, edges_count);
                    if (C.__edges > edges_before)
                    {
                        // cout << "new edge in C: " << first_node << " " << third_node << "\n";
                        edges_count++;
                    }
                }
            }
        }
    }
    return C;
}

Graph::Graph()
{
    __edges = 0;
    __nodes = 0;
}

Graph::Graph(int nodes, int edges)
{
    __nodes = nodes;
    __edges = 0;

    vector <int> edges_for_node;
    for (int i = 0; i < nodes; i++) {
        __list.push_back(edges_for_node);
    }

    int first_node, second_node;
    for (int i = 0; i < edges; i++)
    {
        cin >> first_node >> second_node;
        if (max(first_node, second_node) > __list.size())
            add_node(max(first_node, second_node));
        first_node--; second_node--;
        add_edge(first_node, second_node, i);
    }
}

void Graph::add_edge(int first_node, int second_node, int index)
{
    /*if (check_relationship(first_node, second_node) == true) {
      cout << first_node << " " << second_node << " :such relationship already exist\n";
      print();
    }*/
    if (first_node != second_node && check_relationship(first_node, second_node) == false)
    {
        if (max(first_node, second_node) + 1 > __list.size()) {
            add_node(max(first_node, second_node) + 1);
        }
        __edges++;
        __list[first_node].push_back(index);
        __list[second_node].push_back(index);
    }

}

void Graph::add_node(int node)
{
    vector <int> edges_for_node;
    while (__list.size() < node)
        __list.push_back(edges_for_node);
}

void Graph::print()
{
    ofstream out;
    out.open(OUTPUT_FILE.c_str(), ios::app);
    for (int i = 0; i < __list.size(); i++)
    {
        out << i + 1 << ": ";
        for (int j = 0; j < __list[i].size(); j++) {
            out << __list[i][j] + 1 << " ";
        }
        out << "\n";
    }
    out.close();
}

int  Graph::find_node(int first_node, int edge)
{
    for (int i = 0; i < __list.size(); i++)
    {
        for (int j = 0; j < __list[i].size(); j++)
        {
            if (__list[i][j] == edge && i != first_node)
                return i;
        }
    }
    return -1;
}

bool Graph::check_relationship(int first_node, int second_node)
{
    if (__list.size() > first_node && __list.size() > second_node)
    {
        for (int i = 0; i < __list[first_node].size(); i++) 
        {
            int connected = find_node(first_node, __list[first_node][i]);
            if (connected == second_node)
                return true;
        }
        return false;
    }
    else
        return false;
}