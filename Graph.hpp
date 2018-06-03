/*
 * Graph.hpp
 *
 *  Created on: 7 maj 2018
 *      Author: darek
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <values.h>
#include "Stack.hpp"
#include "Queue.hpp"
#include "SpanningTree.hpp"
#include "ListElement.hpp"
#include "Edge.hpp"
#include "Timer.hpp"

class Graph {
public:
	Edge* edges;
	Edge* non_directed_edges;
	int** incidence_matrix;
	int** incidence_matrix_non_directed;
	ListElement** adjacency_list;
	ListElement** adjacency_list_non_directed;
	int vertex_number;
	int edge_number;
	int non_directed_edge_number;
	ListElement* list_elem_1;
	ListElement* list_elem_2;
	bool* visited;

	Graph(int vertex_number, int edge_number);
	virtual ~Graph();

	void PrimaMatrix();
	void KruskalMatrix(); //TODO
	void DijkstraMatrix(int vertex);
	void FordBellmanMatrix(int vertex); //TODO

	void PrimaList();
	void KruskalList(); //TODO
	void DijkstraList(int vertex);
	void FordBellmanList(int vertex); //TODO

	bool checkIntegrity();
	void randomGraph();
	void randomEdges();
	void changeToNonDirected();

	void print();
};

#endif /* GRAPH_HPP_ */
