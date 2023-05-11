#include "Graph.h"


template <typename VertexDataType>
bool Graph<VertexDataType>::empty()
{
	if (nsize == 0)
		return true;
	return false;
};

template <typename VertexDataType>
void Graph<VertexDataType>::clear()
{
	nodes.clear();
	edges.clear();
}

template <typename VertexDataType>
void Graph<VertexDataType>::addNode(VertexDataType _nodeObject)
{
	if (is_node_exist(_nodeObject) == -1)
		nodes.push_back(Node<VertexDataType>(_nodeObject));
}

template <typename VertexDataType>
void Graph<VertexDataType>::delete_node(VertexDataType _nodeObject)
{
	int _nodeNumber = is_node_exist(_nodeObject);
	if (_nodeNumber != -1)
	{
		nodes.erase(nodes.begin() + _nodeNumber);
		for (int i = 0; i < esize; i++)
		{
			for (int i = 0; i < esize; i++)
				if (is_edge_exist(i, _nodeNumber))
					delete_edge(i, _nodeNumber);

			if (edges[i].from >= _nodeNumber)
				edges[i].from = (edges[i].from - 1);
			if (edges[i].to >= _nodeNumber)
				edges[i].to = (edges[i].to - 1);
		}
	}
}

template <typename VertexDataType>
void Graph<VertexDataType>::add_edge(int i, int j)
{
	if (is_edge_exist(i, j) == false)
		edges.push_back(Edge(i, j));
}

template <typename VertexDataType>
void Graph<VertexDataType>::add_edge(VertexDataType iObject, VertexDataType jObject)
{
	int i = is_node_exist(iObject), j = is_node_exist(jObject);
	if (i != -1 && j != -1 && is_edge_exist(i, j) == false)
		edges.push_back(Edge(is_node_exist(iObject), is_node_exist(jObject)));
}

template <typename VertexDataType>
void Graph<VertexDataType>::delete_edge(int i, int j)
{
	for (int k = 0; k < esize; k++)
	{
		if (is_edge_exist(i, j) || is_edge_exist(j, i))
		{
			edges.erase(edges.begin() + k);
			for (int m = k; m < esize - 1; m++)
				edges[m] = edges[m + 1];
			edges.pop_back();
			if (esize != 0)
				edges.pop_back();
		}
	}
}

template <typename VertexDataType>
void Graph<VertexDataType>::delete_edge(VertexDataType iObject, VertexDataType jObject)
{
	for (int k = 0; k < esize; k++)
		if (is_edge_exist(iObject, jObject) != -1)
			edges.erase(edges.begin() + k);
}

template <typename VertexDataType>
int  Graph<VertexDataType>::node_degree(VertexDataType _nodeObject)
{
	int degree = 0;
	int nodeNumber = is_node_exist(_nodeObject);
	if (nodeNumber != -1)
	{
		for (int i = 0; i < nsize; i++)
		{
			bool isExist = is_edge_exist(i, nodeNumber);
			degree += isExist == true ? 1 : 0;
		}
		return is_edge_exist(nodeNumber, nodeNumber) == true ? ++degree : degree;
	}
	else
		return -1;
}

template <typename VertexDataType>
bool Graph<VertexDataType>::is_edge_exist(int i, int j)
{
	for (int k = 0; k < esize; k++)
	{
		if ((edges[k].from == i && edges[k].to == j) || (edges[k].from == j && edges[k].to == i))
		{
			return true;
		}
	}
	return false;
}

template <typename VertexDataType>
int  Graph<VertexDataType>::is_edge_exist(VertexDataType iObject, VertexDataType jObject)
{
	for (int k = 0; k < esize; k++)
	{
		if ((nodes[edges[k].from].data == iObject && nodes[edges[k].to].data == jObject) ||
			(nodes[edges[k].from].data == jObject && nodes[edges[k].to].data == iObject))
		{
			return k;
		}
	}
	return -1;
}

template <typename VertexDataType>
int  Graph<VertexDataType>::is_node_exist(VertexDataType _nodeObject)
{
	for (int i = 0; i < nsize; i++)
	{
		if (nodes[i].data == _nodeObject)
		{
			return i;
		}
	}
	return -1;
}

template <typename VertexDataType>
bool Graph<VertexDataType>::is_node_exist(int _nodeNumber)
{
	return _nodeNumber < nsize;
}

template <typename VertexDataType>
int  Graph<VertexDataType>::count_of_loops()
{
	int count = 0;
	for (int i = 0; i < nsize; i++)
	{
		count += is_edge_exist(i, i) == true ? 1 : 0;
	}
	return count;
}

template <typename VertexDataType>
int  Graph<VertexDataType>::count_of_nodes()
{
	return nsize;
}

template <typename VertexDataType>
int  Graph<VertexDataType>::count_of_edges()
{
	return esize;
}

template <typename VertexDataType>
void Graph<VertexDataType>::show_nodes()
{
	cout << "\n";
	for (int i = 0; i < nsize; i++)
	{
		cout << nodes[i].data << "\n";
	}
}

template <typename VertexDataType>
void Graph<VertexDataType>::show_edges()
{
	cout << "\n";
	for (int i = 0; i < esize; i++)
	{
		cout << nodes[edges[i].from].data << " - " << nodes[edges[i].to].data << "\n";
	}
}
