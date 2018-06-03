/*
 * Queue.cpp
 *
 *  Created on: 3 cze 2018
 *      Author: darek
 */

#include "Queue.hpp"

Queue::Queue() {
	heap = false;
}

Queue::~Queue() {
	// TODO Auto-generated destructor stub
}

void Queue::addEdge(Edge edge) {
	heap = false;
	tab.push_back(edge);
}

bool Queue::add(Edge edge) {
	heap = false;
	for (int i = 0; i < count_tab.size(); i++) {
		if ((count_tab[i].vertex_end == edge.vertex_end
				&& count_tab[i].vertex_begin == edge.vertex_begin)
				|| (count_tab[i].vertex_end == edge.vertex_begin
						&& count_tab[i].vertex_begin == edge.vertex_end)) {
			return false;
		}
	}

	addAppeared(edge);
	tab.push_back(edge);
	return true;
}

void Queue::addAppeared(Edge edge) {
	count_tab.push_back(edge);
}

void Queue::sortHeap() {
	heap = true;
	int parent;
	Edge edge;

	for (int i = 1; i < tab.size(); i++) {
		parent = ((i - 1) / 2);
		edge = tab[i];

		if (edge.weight < tab[parent].weight && parent >= 0) {
			tab[i] = tab[parent];
			tab[parent] = edge;
		}

	}
}

Edge Queue::removeEdge() {
	heap = false;
	Edge first;

	first = tab.front();
	tab.erase(tab.begin());
	sortHeap();

	return first;
}

int Queue::size() {
	return tab.size();
}

void Queue::showQueue() {
	for (int i = 0; i < tab.size(); i++) {
		std::cout << "Poczatek krawedzi: " << tab[i].vertex_begin
				<< " Koniec Krawedzi: " << tab[i].vertex_end << " Waga krawdzi"
				<< tab[i].weight << std::endl;
	}
}
