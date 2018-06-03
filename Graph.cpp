/*
 * Graph.cpp
 *
 *  Created on: 7 maj 2018
 *      Author: darek
 */

#include "Graph.hpp"

Graph::Graph(int vertex_number, int edge_number) {
	this->vertex_number = vertex_number;
	this->edge_number = edge_number;
	incidence_matrix = new int*[vertex_number];
	incidence_matrix_non_directed = new int*[vertex_number];
	adjacency_list = new ListElement*[vertex_number];
	adjacency_list_non_directed = new ListElement*[vertex_number];
	E = new Edge[edge_number];
	EO = new Edge[edge_number];
	non_directed_edge_number = 0;
	list_elem_1 = NULL;
	list_elem_2 = NULL;
	visited = NULL;
}

Graph::~Graph() {
	for (int i = 0; i < vertex_number; i++) {
		list_elem_1 = adjacency_list[i];
		while (list_elem_1) {
			list_elem_2 = list_elem_1;
			list_elem_1 = list_elem_1->next;
			delete list_elem_2;
		}
	}
	delete[] adjacency_list;

	for (int i = 0; i < vertex_number; i++)
		delete[] incidence_matrix[i];
	delete[] incidence_matrix;

}

void Graph::PrimaMatrix() {
	int vertex, g;
	Timer timer;
	Edge edge;
	std::priority_queue<Edge, std::vector<Edge>, Edge> queue;
	SpanningTree* tree = new SpanningTree(vertex_number, edge_number);
	visited = new bool[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}
	std::cout << "Graf nieskierowany:" << std::endl;
	std::cout << "   V | E";
	for (int i = 0; i < non_directed_edge_number; i++) {
		std::cout << std::setw(4) << i;
	}
	std::cout << std::endl << "  ------";
	for (int i = 0; i < non_directed_edge_number * 4; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 0; i < vertex_number; i++) {
		std::cout << std::setw(4) << i << " |  ";
		for (int j = 0; j < non_directed_edge_number; j++)
			std::cout << std::setw(4) << incidence_matrix_non_directed[i][j];
		std::cout << std::endl;
	}
	std::cout << "  ------";
	for (int i = 0; i < non_directed_edge_number * 4; i++) {
		std::cout << "-";
	}
	std::cout << std::endl << "   W:   ";
	for (int i = 0; i < non_directed_edge_number; i++) {
		std::cout << std::setw(4) << EO[i].weight;
	}
	std::cout << std::endl << std::endl;
	timer.startTimer();

	vertex = 0;
	visited[vertex] = true;
	for (int i = 1; i < vertex_number; i++) {
		for (g = 0; g < non_directed_edge_number; g++) {

			if (incidence_matrix_non_directed[vertex][g] != 0)
				for (int j = 0; j < vertex_number; j++)
					if (j != vertex && incidence_matrix_non_directed[j][g] != 0
							&& !visited[j]) {
						edge.vertex_begin = vertex;
						edge.vertex_end = j;
						edge.weight = EO[g].weight;
						queue.push(edge);

					}
		}
		do {
			edge = queue.top();
			queue.pop();

		} while (visited[edge.vertex_end]);

		tree->addEdge(edge);
		visited[edge.vertex_end] = true;
		vertex = edge.vertex_end;

	}
	timer.stopTimer();
	std::cout << "Czas wykonania: " << timer.getTimeNs() << std::endl;
	std::cout << "Minimalne drzewo rozpinające:";
	tree->print();
	delete tree;
}

void Graph::DijkstraMatrix(int vertex) {
	int root, node, heap_size, parent, left_child, right_child, min_cost,
			child_min, child, *costs, *prevs, *heap, *heap_position;
	Timer timer;
	Stack stack;
	int width;
	costs = new int[vertex_number];
	prevs = new int[vertex_number];
	visited = new bool[vertex_number];
	heap = new int[vertex_number];
	heap_position = new int[vertex_number];

	for (int i = 0; i < vertex_number; i++) {
		costs[i] = MAXINT;
		prevs[i] = -1;
		visited[i] = false;
		heap[i] = heap_position[i] = i;
	}

	timer.startTimer();
	heap_size = vertex_number;

	costs[vertex] = 0;
	node = heap[0];
	heap[0] = heap[vertex];
	heap[vertex] = node;
	heap_position[vertex] = 0;
	heap_position[0] = vertex;

	for (int i = 0; i < vertex_number; i++) {
		root = heap[0];

		heap[0] = heap[--heap_size];
		heap_position[heap[0]] = parent = 0;
		while (true) {
			left_child = parent + parent + 1;
			right_child = left_child + 1;
			if (left_child >= heap_size)
				break;
			min_cost = costs[heap[left_child]];
			child_min = left_child;
			if ((right_child < heap_size)
					&& (min_cost > costs[heap[right_child]])) {
				min_cost = costs[heap[right_child]];
				child_min = right_child;
			}
			if (costs[heap[parent]] <= min_cost)
				break;
			node = heap[parent];
			heap[parent] = heap[child_min];
			heap[child_min] = node;
			heap_position[heap[parent]] = parent;
			heap_position[heap[child_min]] = child_min;
			parent = child_min;
		}

		visited[root] = true;

		for (int i = 0; i < edge_number; i++) {
			if (incidence_matrix[root][i] != 0)
				for (int j = 0; j < vertex_number; j++)
					if (j != root && incidence_matrix[j][i] == -1 && !visited[j]
							&& (costs[j] > costs[root] + E[i].weight)) {
						costs[j] = costs[root] + E[i].weight;
						prevs[j] = root;

						for (child = heap_position[j]; child; child = parent) {
							parent = child / 2;
							if (costs[heap[parent]] <= costs[heap[child]])
								break;
							node = heap[parent];
							heap[parent] = heap[child];
							heap[child] = node;
							heap_position[heap[parent]] = parent;
							heap_position[heap[child]] = child;
						}
					}
		}
	}
	timer.stopTimer();
	std::cout << std::endl << "Czas wykonania: " << timer.getTimeNs()
			<< std::endl;
	std::cout << "Najkrótsza ścieżka z wierzchołka " << vertex << ":"
			<< std::endl;
	for (int i = 0; i < vertex_number; i++) {
		width = -2;
		std::cout << i << ": ";
		if (costs[i] == MAXINT || costs[i] < 0)
			std::cout << "Brak" << std::endl;
		else {
			for (int j = i; j > -1; j = prevs[j]) {
				stack.push(j);
				width = width + 2;
			}
			while (!stack.empty()) {
				std::cout << stack.top();
				stack.pop();
				if (!stack.empty())
					std::cout << "-";
			}
			for (int j = 0; j < vertex_number - width; j++)
				std::cout << " ";
			std::cout << std::setw(5) << "W:" << costs[i] << std::endl;
		}
	}
	std::cout << std::endl;
}

void Graph::PrimaList() {
	int vertex;
	Timer timer;
	Edge e;
	std::priority_queue<Edge, std::vector<Edge>, Edge> queue;
	SpanningTree *tree = new SpanningTree(vertex_number, edge_number);
	visited = new bool[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}
	std::cout << std::endl << "Graf nieskierowany: " << std::endl;
	for (int i = 0; i < vertex_number; i++) {
		std::cout << "V[" << i << "]: ";
		list_elem_1 = adjacency_list_non_directed[i];
		while (list_elem_1) {
			std::cout << std::setw(3) << list_elem_1->vertex << "("
					<< list_elem_1->weight << ") ";
			list_elem_1 = list_elem_1->next;
		}
		std::cout << std::endl;
	}
	timer.startTimer();
	vertex = 0;
	visited[vertex] = true;
	for (int i = 1; i < vertex_number; i++) {
		for (list_elem_1 = adjacency_list_non_directed[vertex]; list_elem_1;
				list_elem_1 = list_elem_1->next) {
			if (!visited[list_elem_1->vertex]) {
				e.vertex_begin = vertex;
				e.vertex_end = list_elem_1->vertex;
				e.weight = list_elem_1->weight;
				queue.push(e);
			}
		}
		do {
			e = queue.top();
			queue.pop();
		} while (visited[e.vertex_end]);
		tree->addEdge(e);
		visited[e.vertex_end] = true;
		vertex = e.vertex_end;

	}

	timer.stopTimer();
	std::cout << std::endl << "Czas wykonania: " << timer.getTimeNs()
			<< std::endl;
	std::cout << "Minimalne drzewo rozpinające:";
	tree->print();
	delete tree;
}

void Graph::DijkstraList(int vertex) {
	int root, node, heap_size, parent, left_child, right_child, min_cost,
			child_min, child, *costs, *prevs, *heap, *heap_position;
	Timer timer;
	Stack stack;
	int width;
	costs = new int[vertex_number];
	prevs = new int[vertex_number];
	visited = new bool[vertex_number];
	heap = new int[vertex_number];
	heap_position = new int[vertex_number];

	for (int i = 0; i < vertex_number; i++) {
		costs[i] = MAXINT;
		prevs[i] = -1;
		visited[i] = false;
		heap[i] = heap_position[i] = i;
	}
	timer.startTimer();
	heap_size = vertex_number;

	costs[vertex] = 0;
	node = heap[0];
	heap[0] = heap[vertex];
	heap[vertex] = node;
	heap_position[vertex] = 0;
	heap_position[0] = vertex;

	for (int i = 0; i < vertex_number; i++) {
		root = heap[0];

		heap[0] = heap[--heap_size];
		heap_position[heap[0]] = parent = 0;
		while (true) {
			left_child = parent + parent + 1;
			right_child = left_child + 1;
			if (left_child >= heap_size)
				break;
			min_cost = costs[heap[left_child]];
			child_min = left_child;
			if ((right_child < heap_size)
					&& (min_cost > costs[heap[right_child]])) {
				min_cost = costs[heap[right_child]];
				child_min = right_child;
			}
			if (costs[heap[parent]] <= min_cost)
				break;
			node = heap[parent];
			heap[parent] = heap[child_min];
			heap[child_min] = node;
			heap_position[heap[parent]] = parent;
			heap_position[heap[child_min]] = child_min;
			parent = child_min;
		}

		visited[root] = true;

		if (adjacency_list[root] != NULL)
			for (list_elem_1 = adjacency_list[root]; list_elem_1; list_elem_1 =
					list_elem_1->next)
				if (!visited[list_elem_1->vertex]
						&& (costs[list_elem_1->vertex]
								> costs[root] + list_elem_1->weight)) {
					costs[list_elem_1->vertex] = costs[root]
							+ list_elem_1->weight;
					prevs[list_elem_1->vertex] = root;

					for (child = heap_position[list_elem_1->vertex]; child;
							child = parent) {
						parent = child / 2;
						if (costs[heap[parent]] <= costs[heap[child]])
							break;
						node = heap[parent];
						heap[parent] = heap[child];
						heap[child] = node;
						heap_position[heap[parent]] = parent;
						heap_position[heap[child]] = child;
					}
				}
	}
	timer.stopTimer();
	std::cout << std::endl << "Czas wykonania: " << timer.getTimeNs()
			<< std::endl;
	std::cout << "Najkrótsza ścieżka z wierzchołka " << vertex << ":"
			<< std::endl;
	for (int i = 0; i < vertex_number; i++) {
		width = -2;

		std::cout << i << ": ";

		if (costs[i] == MAXINT || costs[i] < 0)
			std::cout << "Brak" << std::endl;
		else {
			for (int j = i; j > -1; j = prevs[j]) {
				stack.push(j);
				width = width + 2;
			}

			while (!stack.empty()) {
				std::cout << stack.top();
				stack.pop();
				if (!stack.empty())
					std::cout << "-";
			}
			for (int j = 0; j < vertex_number - width; j++)
				std::cout << " ";
			std::cout << std::setw(5) << "W:" << costs[i] << std::endl;
		}
	}
	std::cout << std::endl;
}

bool Graph::checkIntegrity() {
	Stack stack;
	int vertex, u;
	int count = 0;

	visited = new bool[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}

	stack.push(0);
	visited[0] = true;

	while (!stack.empty()) {
		vertex = stack.top();
		stack.pop();
		count++;
		for (list_elem_1 = adjacency_list_non_directed[vertex]; list_elem_1;
				list_elem_1 = list_elem_1->next) {
			u = list_elem_1->vertex;
			if (!visited[u]) {
				visited[u] = true;
				stack.push(u);
			}
		}
	}
	delete[] visited;
	if (count == vertex_number)
		return true;

	else
		return false;
}

void Graph::randomGraph() {
	for (int i = 0; i < vertex_number; i++)
		incidence_matrix[i] = new int[edge_number];
	for (int i = 0; i < vertex_number; i++)
		for (int j = 0; j < edge_number; j++) {
			incidence_matrix[i][j] = 0;
		}

	for (int i = 0; i < vertex_number; i++)
		adjacency_list[i] = NULL;

	randomEdges();
	changeToNonDirected();
	for (int i = 0; i < edge_number; i++) {
		int vertex_begin = E[i].vertex_begin;
		int vertex_end = E[i].vertex_end;
		int weight = E[i].weight;
		list_elem_1 = new ListElement;
		list_elem_1->vertex = vertex_end;
		list_elem_1->weight = weight;
		list_elem_1->next = adjacency_list[vertex_begin];
		adjacency_list[vertex_begin] = list_elem_1;

		incidence_matrix[vertex_begin][i] = 1;
		incidence_matrix[vertex_end][i] = -1;
	}
}

void Graph::randomEdges() {
	int* T;
	int to_add_1;
	int to_add_2;
	int a = 0;
	int b = 0;
	int c = 0;
	int count_degree = 0;
	int* in_tree;
	int* not_in_tree;
	a = vertex_number;
	not_in_tree = new int[a];
	for (int i = 0; i < a; i++) {
		not_in_tree[i] = i;
	}
	in_tree = new int[a];
	b = rand() % a;
	to_add_1 = not_in_tree[b];
	not_in_tree[b] = not_in_tree[a - 1];
	a--;
	in_tree[c] = to_add_1;
	c++;

	for (int i = 0; i < (vertex_number - 1); i++) {
		b = rand() % c;
		to_add_1 = in_tree[b];

		b = rand() % a;
		to_add_2 = not_in_tree[b];
		not_in_tree[b] = not_in_tree[a - 1];
		a--;
		in_tree[c] = to_add_2;
		c++;
		E[i].vertex_begin = to_add_1;
		E[i].vertex_end = to_add_2;
	}
	for (int i = 0; i < (vertex_number - 1); i++) {

		b = rand() % vertex_number;
		std::swap(E[b].vertex_end, E[b].vertex_begin);

	}

	for (int i = vertex_number - 1; i < edge_number; i++) {
		a = vertex_number;
		T = new int[a];
		for (int k = 0; k < a; k++) {
			T[k] = k;
		}

		b = rand() % a;
		to_add_1 = T[b];
		T[b] = T[a - 1];
		a--;
		while (true) {

			count_degree = 0;
			for (int j = 0; j < i; j++) {
				if (E[j].vertex_begin == to_add_1)
					count_degree++;
				if (count_degree == vertex_number - 1)
					break;
			}

			if (count_degree == vertex_number - 1) {
				b = rand() % a;
				to_add_1 = T[b];
				T[b] = T[a - 1];
				a--;
			} else
				break;
		}

		a = vertex_number;
		for (int k = 0; k < a; k++) {
			T[k] = k;
		}

		T[to_add_1] = T[a - 1];
		a--;

		b = rand() % a;
		to_add_2 = T[b];
		T[b] = T[a - 1];
		a--;

		for (int j = 0; j < i; j++) {
			while (to_add_1 == E[j].vertex_begin && to_add_2 == E[j].vertex_end) {
				b = rand() % a;
				to_add_2 = T[b];
				T[b] = T[a - 1];
				a--;
				j = 0;
			}
		}
		E[i].vertex_begin = to_add_1;
		E[i].vertex_end = to_add_2;
		delete[] T;
	}

	for (int i = 0; i < edge_number; i++)
		E[i].weight = (rand() % 9) + 1;

	delete[] not_in_tree;
	delete[] in_tree;
}

void Graph::changeToNonDirected() {
	for (int i = 0; i < vertex_number; i++)
		incidence_matrix_non_directed[i] = new int[edge_number];
	for (int i = 0; i < vertex_number; i++)
		for (int j = 0; j < edge_number; j++) {
			incidence_matrix_non_directed[i][j] = 0;
		}

	for (int i = 0; i < vertex_number; i++)
		adjacency_list_non_directed[i] = NULL;

	for (int i = 0; i < edge_number; i++) {
		int j = 0;
		while (j < non_directed_edge_number) {

			if (EO[j].vertex_begin == E[i].vertex_begin
					&& EO[j].vertex_end == E[i].vertex_end) {
				break;
			} else
				j++;
		}
		if (j == non_directed_edge_number) {
			EO[non_directed_edge_number].vertex_begin = E[i].vertex_end;
			EO[non_directed_edge_number].vertex_end = E[i].vertex_begin;
			EO[non_directed_edge_number].weight = E[i].weight;
			non_directed_edge_number++;
		}
	}

	int vertex_begin, vertex_end, weight;
	for (int i = 0; i < non_directed_edge_number; i++) {
		vertex_begin = EO[i].vertex_begin;
		vertex_end = EO[i].vertex_end;
		weight = EO[i].weight;
		list_elem_1 = new ListElement;
		list_elem_1->vertex = vertex_end;
		list_elem_1->weight = weight;
		list_elem_1->next = adjacency_list_non_directed[vertex_begin];
		adjacency_list_non_directed[vertex_begin] = list_elem_1;
		list_elem_2 = new ListElement;
		vertex_begin = EO[i].vertex_end;
		vertex_end = EO[i].vertex_begin;
		weight = EO[i].weight;
		list_elem_2->vertex = vertex_end;
		list_elem_2->weight = weight;
		list_elem_2->next = adjacency_list_non_directed[vertex_begin];
		adjacency_list_non_directed[vertex_begin] = list_elem_2;

		incidence_matrix_non_directed[EO[i].vertex_begin][i] = 1;
		incidence_matrix_non_directed[EO[i].vertex_end][i] = 1;
	}
}

void Graph::print() {
	std::cout << "Macierz incydencji:" << std::endl;
	std::cout << "   V | E";
	for (int i = 0; i < edge_number; i++) {
		std::cout << std::setw(4) << i;
	}

	std::cout << std::endl << "  -------";
	for (int i = 0; i < edge_number * 4; i++) {
		std::cout << "-";
	}

	std::cout << std::endl;
	for (int i = 0; i < vertex_number; i++) {
		std::cout << std::setw(4) << i << " |  ";
		for (int j = 0; j < edge_number; j++)
			std::cout << std::setw(4) << incidence_matrix[i][j];
		std::cout << std::endl;
	}
	std::cout << "  -------";
	for (int i = 0; i < edge_number * 4; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	std::cout << "   W:   ";
	for (int i = 0; i < edge_number; i++) {
		std::cout << std::setw(4) << E[i].weight;
	}

	std::cout << std::endl << std::endl << "Lista poprzedników i następników:"
			<< std::endl;
	for (int i = 0; i < vertex_number; i++) {
		std::cout << "V[" << i << "]:";
		list_elem_1 = adjacency_list[i];
		while (list_elem_1) {
			std::cout << std::setw(3) << list_elem_1->vertex << "("
					<< list_elem_1->weight << ") ";
			list_elem_1 = list_elem_1->next;
		}
		std::cout << std::endl;
	}
}
