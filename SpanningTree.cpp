/*
 * SpanningTree.cpp
 *
 *  Created on: 2 cze 2018
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
    ListElement *e1, *e2;
    for (int i = 0; i <= list_size; i++) {
        e1 = list[i];
        while (e1) {
            e2 = e1;
            e1 = e1->next;
            delete e2;
        }
    }
    delete[] list;
}

void SpanningTree::addEdge(Edge e) {
    ListElement *elem;

    weight += e.weight;
    elem = new ListElement;
    elem->w = e.wk;
    elem->waga = e.weight;
    elem->next = list[e.wp];
    list[e.wp] = elem;

    elem = new ListElement;
    elem->w = e.wp;
    elem->waga = e.weight;
    elem->next = list[e.wk];
    list[e.wk] = elem;

    edge_list[a] = e;
    a++;
}

void SpanningTree::print() {
    std::cout << std::endl;
    for (int i = 0; i < a; i++) {

    	std::cout << "Krawedz " << i + 1 << ": ";

    	std::cout << edge_list[i].wp << "<-->" << edge_list[i].wk << " [" << edge_list[i].weight << "] ";

    	std::cout << std::endl;
    }
    std::cout << std::endl << std::endl << "Waga minimalnego drzewa rozpinajacego = " << weight << std::endl << std::endl;
}
