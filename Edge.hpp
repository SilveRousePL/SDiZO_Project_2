/*
 * Edge.hpp
 *
 *  Created on: 7 maj 2018
 *      Author: darek
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

class Edge {
public:
	int vertex_begin, vertex_end, weight;

	bool operator()(const Edge& k1, const Edge& k2) {
		if (k1.weight > k2.weight)
			return true;
		if (k1.weight < k2.weight)
			return false;
		return false;
	}
};

#endif /* EDGE_HPP_ */
