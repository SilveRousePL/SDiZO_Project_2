/*
 * Queue.hpp
 *
 *  Created on: 3 cze 2018
 *      Author: darek
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_
#include <iostream>
#include <vector>
#include "Edge.hpp"

class Queue
{
	std::vector<Edge> tab; //kolejka
	std::vector<Edge> count_tab; //przechwuje elementy, które już wystšpiły
	bool heap;

public:
	Queue();
	virtual ~Queue();

	void addEdge(Edge edge); //dodaje krawedzi
	bool add(Edge edge); //dodaje krawedz po sprawdzeniu czy wystapila
	void addAppeared(Edge edge); // dodaje krawedz do listy wystapien
	void sortHeap(); //przywracania wlasnosci kopca min
	Edge removeEdge(); //usuwa element

	int size(); // rozmiar kolejki krawedzi
	void showQueue();
};

#endif /* QUEUE_HPP_ */
