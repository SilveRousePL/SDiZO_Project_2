/*
 * ConsoleSupport.hpp
 *
 *  Created on: 4 maj 2018
 *      Author: darek
 */

#ifndef CONSOLESUPPORT_HPP_
#define CONSOLESUPPORT_HPP_
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Graph.hpp"

class ConsoleSupport {
public:
	ConsoleSupport();
	virtual ~ConsoleSupport();

	bool to_begin = true;
	int vertex_begin;
	Graph* graph;

	void start();
	void randomGraph();
	void algorithms();
	void loadFile();
};

#endif /* CONSOLESUPPORT_HPP_ */
