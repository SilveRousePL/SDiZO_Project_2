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
	std::vector<Edge> tab;
	std::vector<Edge> count_tab;
	bool heap;

public:
	Queue();
	virtual ~Queue();

	void addEdge(Edge edge);
	bool add(Edge edge);
	void addAppeared(Edge edge);
	void sortHeap();
	Edge removeEdge();

	int size();
	void showQueue();
};

#endif /* QUEUE_HPP_ */
