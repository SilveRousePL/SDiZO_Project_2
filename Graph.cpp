/*
 * Graph.cpp
 *
 *  Created on: 2 cze 2018
 *      Author: darek
 */

#include "Graph.hpp"

Graph::Graph(int vertex_number, int edge_number) {
	this->vertex_number = vertex_number;
	this->edge_number = edge_number;
	incidence_matrix = new int *[vertex_number];
	incidence_matrix_non_directed = new int *[vertex_number];
	adjacency_list = new ListElement *[vertex_number];
	adjacency_list_non_directed = new ListElement *[vertex_number];
	K = new Edge[edge_number];
	KO = new Edge[edge_number];
	krawedzieOdwrotne = 0;
}

Graph::~Graph() {
	int i;
	for (int i = 0; i < vertex_number; i++) {
		list_elem_1 = adjacency_list[i];
		while (list_elem_1) {
			list_elem_2 = list_elem_1;
			list_elem_1 = list_elem_1->next;
			delete list_elem_2;
		}
	}
	delete[] adjacency_list;

	for (i = 0; i < vertex_number; i++)
		delete[] incidence_matrix[i];
	delete[] incidence_matrix;

}

void Graph::changeToNonDirected() {
	int i, j;
	for (i = 0; i < vertex_number; i++)
		incidence_matrix_non_directed[i] = new int[edge_number];
	for (i = 0; i < vertex_number; i++)
		for (j = 0; j < edge_number; j++) {
			incidence_matrix_non_directed[i][j] = 0;
		}

	for (i = 0; i < vertex_number; i++)
		adjacency_list_non_directed[i] = NULL;

	for (i = 0; i < edge_number; i++) {
		j = 0;
		while (j < krawedzieOdwrotne) {

			if (KO[j].wp == K[i].wp && KO[j].wk == K[i].wk) {
				break;
			} else
				j++;
		}
		if (j == krawedzieOdwrotne) {
			KO[krawedzieOdwrotne].wp = K[i].wk;
			KO[krawedzieOdwrotne].wk = K[i].wp;
			KO[krawedzieOdwrotne].weight = K[i].weight;
			krawedzieOdwrotne++;
		}
	}

	int wp, wk, waga;
	for (int i = 0; i < krawedzieOdwrotne; i++) {
		wp = KO[i].wp;
		wk = KO[i].wk;
		waga = KO[i].weight;
		list_elem_1 = new ListElement;
		list_elem_1->w = wk;
		list_elem_1->waga = waga;
		list_elem_1->next = adjacency_list_non_directed[wp];
		adjacency_list_non_directed[wp] = list_elem_1;
		list_elem_2 = new ListElement;
		wp = KO[i].wk;
		wk = KO[i].wp;
		waga = KO[i].weight;
		list_elem_2->w = wk;
		list_elem_2->waga = waga;
		list_elem_2->next = adjacency_list_non_directed[wp];
		adjacency_list_non_directed[wp] = list_elem_2;

		incidence_matrix_non_directed[KO[i].wp][i] = 1;
		incidence_matrix_non_directed[KO[i].wk][i] = 1;
	}

}

void Graph::randomEdges() {
	int c = 0;
	int *T;
	int b, doDodania1, doDodania2, a, i, j;
	int liczStopien = 0;
	int *wDrzewie;
	int *nieWDrzewie;
	a = vertex_number;
	nieWDrzewie = new int[a];
	for (i = 0; i < a; i++) {
		nieWDrzewie[i] = i;
	}
	wDrzewie = new int[a];
	b = rand() % a;
	doDodania1 = nieWDrzewie[b];
	nieWDrzewie[b] = nieWDrzewie[a - 1];
	a--;
	wDrzewie[c] = doDodania1;
	c++;

	for (i = 0; i < (vertex_number - 1); i++) {
		b = rand() % c;
		doDodania1 = wDrzewie[b];

		b = rand() % a;
		doDodania2 = nieWDrzewie[b];
		nieWDrzewie[b] = nieWDrzewie[a - 1];
		a--;
		wDrzewie[c] = doDodania2;
		c++;
		K[i].wp = doDodania1;
		K[i].wk = doDodania2;
	}
	for (i = 0; i < (vertex_number - 1); i++) {

		b = rand() % vertex_number;
		std::swap(K[b].wk, K[b].wp);

	}

	for (i = vertex_number - 1; i < edge_number; i++) {
		a = vertex_number;
		T = new int[a];
		for (int k = 0; k < a; k++) {
			T[k] = k;
		}

		b = rand() % a;
		doDodania1 = T[b];
		T[b] = T[a - 1];
		a--;
		while (true) {

			liczStopien = 0;
			for (j = 0; j < i; j++) {
				if (K[j].wp == doDodania1)
					liczStopien++;
				if (liczStopien == vertex_number - 1)
					break;
			}

			if (liczStopien == vertex_number - 1) {
				b = rand() % a;
				doDodania1 = T[b];
				T[b] = T[a - 1];
				a--;
			} else
				break;
		}

		a = vertex_number;
		for (int k = 0; k < a; k++) {
			T[k] = k;
		}

		T[doDodania1] = T[a - 1];
		a--;

		b = rand() % a;
		doDodania2 = T[b];
		T[b] = T[a - 1];
		a--;

		for (j = 0; j < i; j++) {
			while (doDodania1 == K[j].wp && doDodania2 == K[j].wk) {
				b = rand() % a;
				doDodania2 = T[b];
				T[b] = T[a - 1];
				a--;
				j = 0;
			}
		}
		K[i].wp = doDodania1;
		K[i].wk = doDodania2;
		delete[] T;
	}

	for (i = 0; i < edge_number; i++)
		K[i].weight = (rand() % 9) + 1;

	delete[] nieWDrzewie;
	delete[] wDrzewie;
}

void Graph::randomGraph() {
	int i, j;
	for (i = 0; i < vertex_number; i++)
		incidence_matrix[i] = new int[edge_number];
	for (i = 0; i < vertex_number; i++)
		for (j = 0; j < edge_number; j++) {
			incidence_matrix[i][j] = 0;
		}

	for (i = 0; i < vertex_number; i++)
		adjacency_list[i] = NULL;

	randomEdges();
	changeToNonDirected();
	for (i = 0; i < edge_number; i++) {
		int wp = K[i].wp;
		int wk = K[i].wk;
		int waga = K[i].weight;
		list_elem_1 = new ListElement;
		list_elem_1->w = wk;
		list_elem_1->waga = waga;
		list_elem_1->next = adjacency_list[wp];
		adjacency_list[wp] = list_elem_1;

		incidence_matrix[wp][i] = 1;
		incidence_matrix[wk][i] = -1;
	}

}

bool Graph::checkIntegrity() {
	Stack stos;
	int w, u, i;
	int licz = 0;

	visited = new bool[vertex_number];
	for (i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}

	stos.push(0);
	visited[0] = true;

	while (!stos.empty()) {
		w = stos.top();
		stos.pop();
		licz++;
		for (list_elem_1 = adjacency_list_non_directed[w]; list_elem_1;
				list_elem_1 = list_elem_1->next) {
			u = list_elem_1->w;
			if (!visited[u]) {
				visited[u] = true;
				stos.push(u);
			}
		}
	}
	delete[] visited;
	if (licz == vertex_number)
		return true;

	else
		return false;
}

void Graph::DFSMatrix(int w) {
	int i, j;
	Timer czas;
	Stack stos;
	visited = new bool[vertex_number];
	for (i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}
	std::cout << "Graf nieskierowany:" << std::endl;

	std::cout << "      ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << i;

	}
	std::cout << std::endl << "      ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << "-";

	}

	std::cout << std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << std::setw(3) << i << " | ";
		for (int j = 0; j < krawedzieOdwrotne; j++)
			std::cout << std::setw(3) << incidence_matrix_non_directed[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Wagi: ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << KO[i].weight;
	}
	std::cout << std::endl << std::endl;
	std::cout << "Odwiedzone wierzchołki:" << std::endl;
	czas.startTimer();
	stos.push(w);
	while (!stos.empty()) {

		w = stos.top();
		stos.pop();

		if (!visited[w]) {
			visited[w] = true;
			for (i = edge_number - 1; i >= 0; i--) {
				if (incidence_matrix_non_directed[w][i] != 0)
					for (j = 0; j < vertex_number; j++)
						if (j != w
								&& incidence_matrix_non_directed[j][i] != 0) {
							if (!visited[j]) {
								stos.push(j);
							}
						}

			}
			std::cout << w << ", ";
		}
	}
	std::cout << std::endl << std::endl;

	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	delete[] visited;
	stos.~Stack();
}

void Graph::DFSList(int w) {
	Timer czas;
	Stack stos;
	int u, i;

	visited = new bool[vertex_number];
	for (i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}
	std::cout << std::endl << "Graf nieskierowany: " << std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << "[" << i << "] =";
		list_elem_1 = adjacency_list_non_directed[i];
		while (list_elem_1) {
			std::cout << std::setw(3) << list_elem_1->w << "("
					<< list_elem_1->waga << ") ";
			list_elem_1 = list_elem_1->next;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	std::cout << "Odwiedzone wierzchołki:" << std::endl << std::endl;
	czas.startTimer();
	stos.push(w);

	while (!stos.empty()) {
		w = stos.top();
		stos.pop();

		if (!visited[w]) {
			visited[w] = true;
			for (list_elem_1 = adjacency_list_non_directed[w]; list_elem_1;
					list_elem_1 = list_elem_1->next) {
				u = list_elem_1->w;
				if (!visited[u]) {
					stos.push(u);
				}
			}
			std::cout << w << ", ";
		}

	}
	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	delete[] visited;
	stos.~Stack();
}

void Graph::DijkstraMatrix(int w) {
	int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin,
			synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;
	Timer czas;
	Stack stos;
	int szerokosc, i, j, l;
	koszta = new int[vertex_number];
	poprzednicy = new int[vertex_number];
	visited = new bool[vertex_number];
	kopiec = new int[vertex_number];
	pozycjaKopiec = new int[vertex_number];

	for (i = 0; i < vertex_number; i++) {
		koszta[i] = MAXINT;
		poprzednicy[i] = -1;
		visited[i] = false;
		kopiec[i] = pozycjaKopiec[i] = i;
	}

	czas.startTimer();
	rozmiarKopca = vertex_number;

	koszta[w] = 0;
	wezel = kopiec[0];
	kopiec[0] = kopiec[w];
	kopiec[w] = wezel;
	pozycjaKopiec[w] = 0;
	pozycjaKopiec[0] = w;

	for (i = 0; i < vertex_number; i++) {
		korzen = kopiec[0];

		kopiec[0] = kopiec[--rozmiarKopca];
		pozycjaKopiec[kopiec[0]] = ojciec = 0;
		while (true) {
			lewySyn = ojciec + ojciec + 1;
			prawySyn = lewySyn + 1;
			if (lewySyn >= rozmiarKopca)
				break;
			kosztMin = koszta[kopiec[lewySyn]];
			synMin = lewySyn;
			if ((prawySyn < rozmiarKopca)
					&& (kosztMin > koszta[kopiec[prawySyn]])) {
				kosztMin = koszta[kopiec[prawySyn]];
				synMin = prawySyn;
			}
			if (koszta[kopiec[ojciec]] <= kosztMin)
				break;
			wezel = kopiec[ojciec];
			kopiec[ojciec] = kopiec[synMin];
			kopiec[synMin] = wezel;
			pozycjaKopiec[kopiec[ojciec]] = ojciec;
			pozycjaKopiec[kopiec[synMin]] = synMin;
			ojciec = synMin;
		}

		visited[korzen] = true;

		for (l = 0; l < edge_number; l++) {
			if (incidence_matrix[korzen][l] != 0)
				for (j = 0; j < vertex_number; j++)
					if (j != korzen && incidence_matrix[j][l] == -1
							&& !visited[j]
							&& (koszta[j] > koszta[korzen] + K[l].weight)) {
						koszta[j] = koszta[korzen] + K[l].weight;
						poprzednicy[j] = korzen;

						for (syn = pozycjaKopiec[j]; syn; syn = ojciec) {
							ojciec = syn / 2;
							if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
								break;
							wezel = kopiec[ojciec];
							kopiec[ojciec] = kopiec[syn];
							kopiec[syn] = wezel;
							pozycjaKopiec[kopiec[ojciec]] = ojciec;
							pozycjaKopiec[kopiec[syn]] = syn;
						}
					}
		}
	}
	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	std::cout << std::endl;

	std::cout << "Najkrótsza ścieżka z wierzchołka " << w << ":" << std::endl;
	for (i = 0; i < vertex_number; i++) {
		szerokosc = -2;

		std::cout << i << ": ";

		if (koszta[i] == MAXINT || koszta[i] < 0)
			std::cout << "Brak" << std::endl;
		else {
			for (j = i; j > -1; j = poprzednicy[j]) {
				stos.push(j);
				szerokosc = szerokosc + 2;
			}

			while (!stos.empty()) {
				std::cout << stos.top() << " ";
				stos.pop();
			}
			for (j = 0; j < vertex_number - szerokosc; j++)
				std::cout << " ";
			std::cout << std::setw(5) << "(" << koszta[i] << ")" << std::endl;
		}
	}
	std::cout << std::endl << std::endl;
}

void Graph::DijkstraList(int w) {
	int korzen, wezel, rozmiarKopca, ojciec, lewySyn, prawySyn, kosztMin,
			synMin, syn, *koszta, *poprzednicy, *kopiec, *pozycjaKopiec;
	Timer czas;
	Stack stos;
	int szerokosc, i, j;
	koszta = new int[vertex_number];
	poprzednicy = new int[vertex_number];
	visited = new bool[vertex_number];
	kopiec = new int[vertex_number];
	pozycjaKopiec = new int[vertex_number];

	for (i = 0; i < vertex_number; i++) {
		koszta[i] = MAXINT;
		poprzednicy[i] = -1;
		visited[i] = false;
		kopiec[i] = pozycjaKopiec[i] = i;
	}
	czas.startTimer();
	rozmiarKopca = vertex_number;

	koszta[w] = 0;
	wezel = kopiec[0];
	kopiec[0] = kopiec[w];
	kopiec[w] = wezel;
	pozycjaKopiec[w] = 0;
	pozycjaKopiec[0] = w;

	for (i = 0; i < vertex_number; i++) {
		korzen = kopiec[0];

		kopiec[0] = kopiec[--rozmiarKopca];
		pozycjaKopiec[kopiec[0]] = ojciec = 0;
		while (true) {
			lewySyn = ojciec + ojciec + 1;
			prawySyn = lewySyn + 1;
			if (lewySyn >= rozmiarKopca)
				break;
			kosztMin = koszta[kopiec[lewySyn]];
			synMin = lewySyn;
			if ((prawySyn < rozmiarKopca)
					&& (kosztMin > koszta[kopiec[prawySyn]])) {
				kosztMin = koszta[kopiec[prawySyn]];
				synMin = prawySyn;
			}
			if (koszta[kopiec[ojciec]] <= kosztMin)
				break;
			wezel = kopiec[ojciec];
			kopiec[ojciec] = kopiec[synMin];
			kopiec[synMin] = wezel;
			pozycjaKopiec[kopiec[ojciec]] = ojciec;
			pozycjaKopiec[kopiec[synMin]] = synMin;
			ojciec = synMin;
		}

		visited[korzen] = true;

		if (adjacency_list[korzen] != NULL)
			for (list_elem_1 = adjacency_list[korzen]; list_elem_1;
					list_elem_1 = list_elem_1->next)
				if (!visited[list_elem_1->w]
						&& (koszta[list_elem_1->w]
								> koszta[korzen] + list_elem_1->waga)) {
					koszta[list_elem_1->w] = koszta[korzen] + list_elem_1->waga;
					poprzednicy[list_elem_1->w] = korzen;

					for (syn = pozycjaKopiec[list_elem_1->w]; syn; syn =
							ojciec) {
						ojciec = syn / 2;
						if (koszta[kopiec[ojciec]] <= koszta[kopiec[syn]])
							break;
						wezel = kopiec[ojciec];
						kopiec[ojciec] = kopiec[syn];
						kopiec[syn] = wezel;
						pozycjaKopiec[kopiec[ojciec]] = ojciec;
						pozycjaKopiec[kopiec[syn]] = syn;
					}
				}
	}
	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	std::cout << std::endl;

	std::cout << "Najkrótsza ścieżka z wierzchołka " << w << ":" << std::endl;
	for (i = 0; i < vertex_number; i++) {
		szerokosc = -2;

		std::cout << i << ": ";

		if (koszta[i] == MAXINT || koszta[i] < 0)
			std::cout << "Brak" << std::endl;
		else {
			for (j = i; j > -1; j = poprzednicy[j]) {
				stos.push(j);
				szerokosc = szerokosc + 2;
			}

			while (!stos.empty()) {
				std::cout << stos.top() << " ";
				stos.pop();
			}
			for (j = 0; j < vertex_number - szerokosc; j++)
				std::cout << " ";
			std::cout << std::setw(5) << "(" << koszta[i] << ")" << std::endl;
		}
	}
	std::cout << std::endl << std::endl;
}

void Graph::PrimaMatrix() {

	int w, i, j, g;
	Timer czas;
	Edge krawedz;
	std::priority_queue<Edge, std::vector<Edge>, Edge> kolejka;
	SpanningTree *drzewo = new SpanningTree(vertex_number, edge_number);
	visited = new bool[vertex_number];
	for (i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}

	std::cout << "Graf nieskierowany:" << std::endl;

	std::cout << "      ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << i;

	}
	std::cout << std::endl << "      ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << "-";

	}

	std::cout << std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << std::setw(3) << i << " | ";
		for (int j = 0; j < krawedzieOdwrotne; j++)
			std::cout << std::setw(3) << incidence_matrix_non_directed[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Wagi: ";
	for (i = 0; i < krawedzieOdwrotne; i++) {
		std::cout << std::setw(3) << KO[i].weight;
	}
	std::cout << std::endl << std::endl;
	czas.startTimer();

	w = 0;
	visited[w] = true;
	for (i = 1; i < vertex_number; i++) {
		for (g = 0; g < krawedzieOdwrotne; g++) {

			if (incidence_matrix_non_directed[w][g] != 0)
				for (j = 0; j < vertex_number; j++)
					if (j != w && incidence_matrix_non_directed[j][g] != 0
							&& !visited[j]) {
						krawedz.wp = w;
						krawedz.wk = j;
						krawedz.weight = KO[g].weight;
						kolejka.push(krawedz);

					}
		}
		do {
			krawedz = kolejka.top();
			kolejka.pop();

		} while (visited[krawedz.wk]);

		drzewo->addEdge(krawedz);
		visited[krawedz.wk] = true;
		w = krawedz.wk;

	}
	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	std::cout << "Minimalne drzewo rozpinające:";
	drzewo->print();
	delete drzewo;
}

void Graph::PrimaList() {
	int w, i;
	Timer czas;
	Edge k;
	std::priority_queue<Edge, std::vector<Edge>, Edge> kolejka;
	SpanningTree *drzewo = new SpanningTree(vertex_number, edge_number);
	visited = new bool[vertex_number];
	for (i = 0; i < vertex_number; i++) {
		visited[i] = false;
	}
	std::cout << std::endl << "Graf nieskierowany: " << std::endl << std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << "[" << i << "] =";
		list_elem_1 = adjacency_list_non_directed[i];
		while (list_elem_1) {
			std::cout << std::setw(3) << list_elem_1->w << "("
					<< list_elem_1->waga << ") ";
			list_elem_1 = list_elem_1->next;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	czas.startTimer();
	w = 0;
	visited[w] = true;

	for (i = 1; i < vertex_number; i++) {

		for (list_elem_1 = adjacency_list_non_directed[w]; list_elem_1;
				list_elem_1 = list_elem_1->next) {
			if (!visited[list_elem_1->w]) {
				k.wp = w;
				k.wk = list_elem_1->w;
				k.weight = list_elem_1->waga;
				kolejka.push(k);
			}
		}
		do {
			k = kolejka.top();
			kolejka.pop();

		} while (visited[k.wk]);

		drzewo->addEdge(k);
		visited[k.wk] = true;
		w = k.wk;

	}

	czas.stopTimer();
	std::cout << std::endl << "Czas: " << czas.getTimeNs() << std::endl;
	std::cout << std::endl;
	std::cout << "Minimalne drzewo rozpinające:";
	drzewo->print();
	delete drzewo;
}

void Graph::print() {
	std::cout << "Macierz incydencji:" << std::endl;
	int i;
	std::cout << "      ";
	for (i = 0; i < edge_number; i++) {
		std::cout << std::setw(3) << i;

	}

	std::cout << std::endl << "      ";
	for (i = 0; i < edge_number; i++) {
		std::cout << std::setw(3) << "-";

	}

	std::cout << std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << std::setw(3) << i << " | ";
		for (int j = 0; j < edge_number; j++)
			std::cout << std::setw(3) << incidence_matrix[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Wagi: ";
	for (i = 0; i < edge_number; i++) {
		std::cout << std::setw(3) << K[i].weight;
	}

	std::cout << std::endl << std::endl << "Lista poprzedników i następników:"
			<< std::endl;
	for (i = 0; i < vertex_number; i++) {
		std::cout << "[" << i << "] =";
		list_elem_1 = adjacency_list[i];
		while (list_elem_1) {
			std::cout << std::setw(3) << list_elem_1->w << "("
					<< list_elem_1->waga << ") ";
			list_elem_1 = list_elem_1->next;
		}
		std::cout << std::endl;
	}
}
