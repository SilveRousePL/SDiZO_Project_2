/*
 * SpanningTree.hpp
 *
 *  Created on: 9 maj 2018
 *      Author: darek
 */

#ifndef SPANNINGTREE_HPP_
#define SPANNINGTREE_HPP_
#include <iostream>
#include "Edge.hpp"
#include "ListElement.hpp"

class SpanningTree {
    ListElement** list;
    Edge* edge_list;
    int list_size;
	int edge_number;
    int weight;
    int a;

public:
    SpanningTree(int vertex_number, int edge_number);
    ~SpanningTree();
    void addEdge(Edge e);
    void print();
};

#endif /* SPANNINGTREE_HPP_ */
