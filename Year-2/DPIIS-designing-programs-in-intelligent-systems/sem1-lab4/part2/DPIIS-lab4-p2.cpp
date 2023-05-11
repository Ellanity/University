#include <conio.h>
#include "Graph.cpp"
#include "Graph.h"

using std::cin;
using std::cout;

int menu() {
	int choice = 15;
	cout << "1.  Add node\n";
	cout << "2.  Does node exist\n";
	cout << "3.  Delete node\n";
	cout << "4.  Add edge\n";
	cout << "5.  Does edge exist\n";
	cout << "6.  Delete edge\n";
	cout << "7.  Number of edges and nodes\n";
	cout << "8.  Show nodes\n";
	cout << "9.  Show edges\n";
	cout << "10. Degree of the node\n";
	cout << "11. Iterator for nodes\n";
	cout << "12. Iterator for edges\n";
	cout << "13. Is container empty\n";
	cout << "14. Clear\n";
	cout << "15. Exit\n";
	cin >> choice;
	return choice;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int choice = 1;
	std::string node_1 = "";
	std::string node_2 = "";

	Graph<std::string>* G = new Graph<std::string>();

	while (true)
	{
		system("cls");
		choice = menu();
		switch (choice)
		{
		case 1:
		{
			cout << "\nEnter node name: ";
			cin >> node_1;
			system("cls");
			G->addNode(node_1);
			break;
		}
		case 2:
		{
			cout << "\nEnter node name: ";
			cin >> node_1;
			if (G->is_node_exist(node_1) != -1)
				cout << "\nThis node exists\n";
			else
				cout << "\nThis node doesn't exist\n";
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			cout << "\nEnter node name: ";
			cin >> node_1;
			system("cls");
			G->delete_node(node_1);
			break;
		}
		case 4:
		{
			cout << "\nEnter nodes names: ";
			cin >> node_1 >> node_2;
			system("cls");
			G->add_edge(node_1, node_2);
			break;
		}
		case 5:
		{
			cout << "\nEnter a nodes names: ";
			cin >> node_1 >> node_2;
			if (G->is_edge_exist(node_1, node_2) != -1)
				cout << "\nThis edge exist\n";
			else
				cout << "\nThis edge doesn't exist\n";
			_getch();
			system("cls");
			break;
		}
		case 6:
		{
			cout << "\nEnter nodes names: ";
			cin >> node_1 >> node_2;
			system("cls");
			G->delete_edge(node_1, node_2);
			break;
		}
		case 7:
		{
			cout << "\nNodes: " << G->count_of_nodes()
				 << "\nEdges: " << G->count_of_edges()
				 << "\n";
			_getch();
			system("cls");
			break;
		}
		case 8:
		{
			if (G->count_of_nodes() == 0)
			{
				cout << "No nodes\n";
				_getch();
				system("cls");
				break;
			}
			G->show_nodes();
			_getch();
			system("cls");
			break;
		}
		case 9:
		{
			if (G->count_of_edges() == 0)
			{
				cout << "No edges";
				_getch();
				system("cls");
				break;
			}
			G->show_edges();
			_getch();
			system("cls");
			break;
		}
		case 10:
		{
			cout << "\nEnter a node name: ";
			cin >> node_1;
			int degree = G->node_degree(node_1);
			if (degree <= -1)
				cout << "No node with this name\n";
			else
				cout << "Node degree: " << degree;
			_getch();
			system("cls");
			break;
		}
		case 11:
		{
			Graph<string>::Node_Iterator G_iterator(*G);
			while (choice != 5)
			{
				system("cls");
				cout << "\n";
				cout << "1. Next node\n";
				cout << "2. Previous node\n";
				cout << "3.Get adjacent nodes\n";
				cout << "4.Get incident edges\n";
				cout << "5.Exit\n";
				cin >> choice;

				switch (choice)
				{
				case 1:
				{
					if (G_iterator.next() == false)
						cout << "\nError\n";
					else
						cout << "\nIterator moved to next node\n";
					break;
				}
				case 2:
				{
					if (G_iterator.previous() == false)
						cout << "\nError\n";
					else
						cout << "\nIterator moved to previous node\n";
					break;
				}
				case 3:
				{
					G_iterator.get_adjacent_nodes();
					break;
				}
				case 4:
				{
					G_iterator.get_incident_edges();
					break;
				}
				default:
					_getch();
					system("cls");
					break;
				}
				system("pause");
			}
			break;
		}
		case 12:
		{
			Graph<string>::Node_Iterator G_iterator(*G);
			while (choice != 3)
			{
				//system("cls");
				cout << "\n";
				cout << "1. Next edge\n";
				cout << "2. Previous edge\n";
				cout << "3. Exit\n";
				cin >> choice;

				switch (choice)
				{
				case 1:
				{
					if (G_iterator.next() == false)
						cout << "\nError\n";
					else
						cout << "\nIterator moved to next edge\n";
					break;
				}
				case 2:
				{
					if (G_iterator.previous() == false)
						cout << "\nError\n";
					else
						cout << "\nIterator moved to previous edge\n";
					break;
				}
				default:
					_getch();
					system("cls");
					break;
				}
				system("pause");
			}
			break;
		}
		case 13:
		{
			(G->empty() == true) ? cout << "\nEmpty\n" : cout << "\nNot empty\n";
			_getch();
			system("cls");
			break;
		}
		case 14:
		{
			G->clear();
			cout << "Container cleaned!\n";
			_getch();
			system("cls");
			break;
		}
		case 15:
			return 0;
		default: 
			break;
		}
	}
}