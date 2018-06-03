/*
 * SpanningTree.cpp
 *
 *  Created on: 9 maj 2018
 *      Author: darek
 */

#include "SpanningTree.hpp"

SpanningTree::SpanningTree(int vertex_number, int edge_number) {
	list = new ListElement *[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		list[i] = nullptr;
	}
	list_size = vertex_number - 1;
	weight = 0;
	this->edge_number = edge_number;
	edge_list = new Edge[edge_number];
	a = 0;
}

SpanningTree::~SpanningTree() {
	ListElement* elem_1;
	ListElement* elem_2;
	for (int i = 0; i <= list_size; i++) {
		elem_1 = list[i];
		while (elem_1) {
			elem_2 = elem_1;
			elem_1 = elem_1->next;
			delete elem_2;
		}
	}
	delete[] list;
}

void SpanningTree::addEdge(Edge e) {
	ListElement* elem;

	weight += e.weight;
	elem = new ListElement;
	elem->vertex = e.vertex_end;
	elem->weight = e.weight;
	elem->next = list[e.vertex_begin];
	list[e.vertex_begin] = elem;

	elem = new ListElement;
	elem->vertex = e.vertex_begin;
	elem->weight = e.weight;
	elem->next = list[e.vertex_end];
	list[e.vertex_end] = elem;

	edge_list[a] = e;
	a++;
}

void SpanningTree::print() {
	std::cout << std::endl;
	for (int i = 0; i < a; i++) {
		std::cout << "Krawędź " << i + 1 << ": " << edge_list[i].vertex_begin
				<< "-" << edge_list[i].vertex_end << "   W:"
				<< edge_list[i].weight << std::endl;
	}
	std::cout << "Waga minimalnego drzewa rozpinajacego: " << weight
			<< std::endl << std::endl;
}
