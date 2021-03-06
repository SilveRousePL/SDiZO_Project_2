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
	edges = new Edge[edge_number];
	non_directed_edges = new Edge[edge_number];
	non_directed_edge_number = 0;
	list_elem_1 = NULL;
	list_elem_2 = NULL;
	visited = NULL;
	recently_time = 0;
	density = -1;
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
		std::cout << std::setw(4) << non_directed_edges[i].weight;
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
						edge.weight = non_directed_edges[g].weight;
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
	recently_time = timer.getTimeNs();
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
							&& (costs[j] > costs[root] + edges[i].weight)) {
						costs[j] = costs[root] + edges[i].weight;
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
	recently_time = timer.getTimeNs();
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
	recently_time = timer.getTimeNs();
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
	recently_time = timer.getTimeNs();
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
		int vertex_begin = edges[i].vertex_begin;
		int vertex_end = edges[i].vertex_end;
		int weight = edges[i].weight;
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
		edges[i].vertex_begin = to_add_1;
		edges[i].vertex_end = to_add_2;
	}
	for (int i = 0; i < (vertex_number - 1); i++) {

		b = rand() % vertex_number;
		std::swap(edges[b].vertex_end, edges[b].vertex_begin);

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
				if (edges[j].vertex_begin == to_add_1)
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
			while (to_add_1 == edges[j].vertex_begin
					&& to_add_2 == edges[j].vertex_end) {
				b = rand() % a;
				to_add_2 = T[b];
				T[b] = T[a - 1];
				a--;
				j = 0;
			}
		}
		edges[i].vertex_begin = to_add_1;
		edges[i].vertex_end = to_add_2;
		delete[] T;
	}

	for (int i = 0; i < edge_number; i++)
		edges[i].weight = (rand() % 9) + 1;

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

			if (non_directed_edges[j].vertex_begin == edges[i].vertex_begin
					&& non_directed_edges[j].vertex_end
							== edges[i].vertex_end) {
				break;
			} else
				j++;
		}
		if (j == non_directed_edge_number) {
			non_directed_edges[non_directed_edge_number].vertex_begin =
					edges[i].vertex_end;
			non_directed_edges[non_directed_edge_number].vertex_end =
					edges[i].vertex_begin;
			non_directed_edges[non_directed_edge_number].weight =
					edges[i].weight;
			non_directed_edge_number++;
		}
	}

	int vertex_begin, vertex_end, weight;
	for (int i = 0; i < non_directed_edge_number; i++) {
		vertex_begin = non_directed_edges[i].vertex_begin;
		vertex_end = non_directed_edges[i].vertex_end;
		weight = non_directed_edges[i].weight;
		list_elem_1 = new ListElement;
		list_elem_1->vertex = vertex_end;
		list_elem_1->weight = weight;
		list_elem_1->next = adjacency_list_non_directed[vertex_begin];
		adjacency_list_non_directed[vertex_begin] = list_elem_1;
		list_elem_2 = new ListElement;
		vertex_begin = non_directed_edges[i].vertex_end;
		vertex_end = non_directed_edges[i].vertex_begin;
		weight = non_directed_edges[i].weight;
		list_elem_2->vertex = vertex_end;
		list_elem_2->weight = weight;
		list_elem_2->next = adjacency_list_non_directed[vertex_begin];
		adjacency_list_non_directed[vertex_begin] = list_elem_2;

		incidence_matrix_non_directed[non_directed_edges[i].vertex_begin][i] =
				1;
		incidence_matrix_non_directed[non_directed_edges[i].vertex_end][i] = 1;
	}
}

void Graph::testAll(int vertex) {
	std::fstream handle;
	std::stringstream filename;
	filename << "wyniki" << "V" << vertex_number << "D" << density << ".txt";
	handle.open(filename.str(), std::ios::out);
	if (!handle) {
		std::cout << "Błąd zapisu do pliku!" << std::endl << std::endl;
		return;
	}
	handle << std::endl << "PrimaMatrix: " << "V = " << vertex_number
			<< "  D = " << density << std::endl;
	for (int i = 0; i < 100; i++) {
		this->PrimaMatrix();
		handle << recently_time << std::endl;
	}
	handle << std::endl << "PrimaList: " << "V = " << vertex_number << "  D = "
			<< density << std::endl;
	for (int i = 0; i < 100; i++) {
		this->PrimaList();
		handle << recently_time << std::endl;
	}
	handle << std::endl << "DijkstraMatrix: " << "V = " << vertex_number
			<< "  D = " << density << std::endl;
	for (int i = 0; i < 100; i++) {
		this->DijkstraMatrix(vertex);
		handle << recently_time << std::endl;
	}
	handle << std::endl << "DijkstraList: " << "V = " << vertex_number
			<< "  D = " << density << std::endl;
	for (int i = 0; i < 100; i++) {
		this->DijkstraList(vertex);
		handle << recently_time << std::endl;
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
		std::cout << std::setw(4) << edges[i].weight;
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

/*
 void Graph::KruskalMatrix() {
 Edge edge;
 Queue queue;
 SpanningTree* tree = new SpanningTree(vertex_number, edge_number);

 for (int i = 0; i < non_directed_edge_number; i++) {
 for (int j = 0; j < vertex_number; j++) {
 if (incidence_matrix_non_directed[j][i] == 1) {
 for (int n = j + 1; n < vertex_number; n++) {
 if (incidence_matrix_non_directed[n][i] == 1) {
 queue.add(Edge(j, n, edges[i].weight));
 n = vertex_number;
 }
 }
 }
 }
 }

 std::cout << std::endl << "ALGORYTM KRUSKALA" << std::endl;
 queue.sortHeap();
 while (tree->completedTree(vertex_number) == false) {
 edge = queue.removeEdge();
 tree->addEdge(edge);
 std::cout << edge.vertex_begin << "-" << edge.vertex_end << ": "
 << edge.weight << std::endl;
 }
 std::cout << std::endl << "Suma wag:" << std::endl;
 std::cout << tree->sumValues() << std::endl;
 }

 void Graph::FordBellmanMatrix(int vertex) {
 int* tab = new int[vertex_number];	// wektor aktulanych wag
 Edge edge;
 for (int i = 0; i < vertex_number; i++) {
 tab[i] = INT_MAX;
 }

 tab[vertex] = 0;
 for (int i = 0; i < vertex_number - 1; i++) //tyle razy zeby znalezc jak najkrótsz¹ scie¿kê, -1 bo pomijamy startowy wierzcholek
 {
 for (int p = 0; p < vertex_number; p++)
 for (int j = 0; j < edge_number; j++) {
 if (incidence_matrix[p][j] == 1) {
 for (int k = 0; k < vertex_number; k++) {
 if (incidence_matrix[k][j] == -1) {
 edge = Edge(p, k, edges[i].weight);

 if (tab[edge.vertex_end]
 > tab[edge.vertex_begin] + edge.weight) // jezeli dlugosc sciezki krotszej jest wieksza niz dlugosc sciezki po wiekszej ilosci krawedzi
 {
 tab[edge.vertex_end] = tab[edge.vertex_begin]
 + edge.weight;
 }
 k = vertex_number;
 }
 }
 }
 }
 }
 std::cout << std::endl << "ALGORYTM FORDA BELLMANA" << std::endl;
 std::cout << std::endl << "Najkrotsze sciezki: " << std::endl;
 for (int i = 0; i < vertex_number; i++) {
 std::cout << std::setw(3) << vertex << "-" << i << ":";
 if (tab[i] == 1000000) {
 std::cout << std::setw(3) << "*" << std::endl;
 } else {
 std::cout << std::setw(3) << tab[i] << std::endl;
 }
 }
 delete[] tab;
 }

 void Graph::KruskalList() {

 }

 void Graph::FordBellmanList(int vertex) {

 }
 */
