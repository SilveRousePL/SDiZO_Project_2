/*
 * Graph.hpp
 *
 *  Created on: 2 cze 2018
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
#include "SpanningTree.hpp"
#include "ListElement.hpp"
#include "Edge.hpp"
#include "Timer.hpp"

class Graph {
public:
    Edge* K;
    Edge* KO;
    int** incidence_matrix;
    int** incidence_matrix_non_directed;
    ListElement** adjacency_list;
	ListElement** adjacency_list_non_directed;
    int vertex_number;
    int edge_number;
    int density;
	int krawedzieOdwrotne;
    ListElement* list_elem_1;
    ListElement* list_elem_2;
    bool* visited;

    Graph(int vertex_number, int edge_number);
    virtual ~Graph();

    void PrimaMatrix();
    void DijkstraMatrix(int w);
    void DFSMatrix(int w);

    void PrimaList();
    void DijkstraList(int w);
    void DFSList(int w);

    bool checkIntegrity();
    void randomGraph();
    void randomEdges();
    void changeToNonDirected();

    void print();
};

#endif /* GRAPH_HPP_ */
