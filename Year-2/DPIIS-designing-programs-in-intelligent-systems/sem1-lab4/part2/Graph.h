#pragma once

#ifndef Graph_H
#define Graph_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using std::cout;
using std::vector;
using std::string;
using std::ifstream;


#define nsize nodes.size()
#define esize edges.size()


template <typename VertexDataType>
class Graph
{
public:
	//// classes of node and edge
	template <typename VertexDataType>
	class Node
	{
	public:
		VertexDataType data;
		Node(VertexDataType _data) { data = _data; }
	};

	class Edge 
	{
	public:
		int from, to;
		Edge(int _from = 0, int _to = 0)
		{
			from = _from;
			to = _to;
		}
	};

	////
	vector< Node <VertexDataType> > nodes;
	vector< Edge > edges;

	Graph() {};
	~Graph() {};

	bool empty();
	void clear();
	void addNode(VertexDataType _nodeObject);
	void delete_node(VertexDataType _nodeObject);
	
	void add_edge(int i, int j);
	void add_edge(VertexDataType iObject, VertexDataType jObject);
	void delete_edge(int i, int j);
	void delete_edge(VertexDataType iObject, VertexDataType jObject);
	
	int  node_degree(VertexDataType _nodeObject);
	
	bool is_edge_exist(int i, int j);
	int  is_edge_exist(VertexDataType iObject, VertexDataType jObject);
	bool is_node_exist(int _nodeNumber);
	int  is_node_exist(VertexDataType _nodeObject);
	
	int  count_of_loops();
	int  count_of_nodes();
	int  count_of_edges();
	
	void show_nodes();
	void show_edges();

	class Node_Iterator
	{
	public:
		Graph<VertexDataType>* graph;
		int index;
	
		Node_Iterator(Graph<VertexDataType>& _graph)
		{
			graph = &_graph;
			index = 0;
		}

		bool next()
		{
			if (graph->nsize <= index + 1)
				return false;
			index++;
			return true;
		}
		bool previous()
		{
			if (index == 0)
				return false;
			index--;
			return true;
		}

		void get_adjacent_nodes()
		{
			int count_of_adjacent = 0;
			cout << "\n";
			for (int i = 0; i < graph->nsize; i++)
			{
				if (graph->is_edge_exist(index, i) == true)
				{
					count_of_adjacent++;
					cout << graph->nodes[i].data << ' ';
				}
			}
			if (count_of_adjacent == 0)
				cout << "No nodes adjacent to this node";
			cout << "\n";
		}
		void get_incident_edges()
		{
			cout << "\n";
			int count_of_incident = 0;
			for (int i = 0; i < graph->nsize; i++)
			{
				if (graph->is_edge_exist(index, i) == true)
				{
					count_of_incident++;
					cout << graph->nodes[index].data << " -> " << graph->nodes[i].data << "\n";
				}
			}
			if (count_of_incident == 0)
				cout << "No edges incident to this node";
			cout << "\n";
		}
	};

	class Edge_iterator
	{
	public:
		Graph<VertexDataType>* graph;
		int index;

		Edge_iterator(Graph<VertexDataType>& _graph)
		{
			graph = &_graph;
			index = 0;
		}
		bool next()
		{
			if (graph->esize <= index + 1)
				return false;
			index++;
			return true;
		}
		bool previous()
		{
			if (index == 0)
				return false;
			index--;
			return true;
		}
	};
};

#endif // ! 

