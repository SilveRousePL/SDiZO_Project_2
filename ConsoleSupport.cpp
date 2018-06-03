/*
 * ConsoleSupport.cpp
 *
 *  Created on: 4 maj 2018
 *      Author: darek
 */

#include "ConsoleSupport.hpp"

ConsoleSupport::ConsoleSupport() {
	graph = NULL;
}

ConsoleSupport::~ConsoleSupport() {

}

void ConsoleSupport::start() {
	int option;
	while (to_begin) {
		std::cout << "Generowanie grafu:" << std::endl << "1. Z pliku"
				<< std::endl << "2. Losowy graf" << std::endl;
		std::cin >> option;
		switch (option) {
		case 1: {
			loadFile();
			algorithms();
		}
			break;
		case 2: {
			randomGraph();
			algorithms();
		}
			break;
		}
	}
}

void ConsoleSupport::algorithms() {
	int option;
	int vertex_begin;
	while (!to_begin) {
		std::cout << std::endl << "Wybierz algorytm:" << std::endl
				<< "1. Algorytm Prima" << std::endl << "2. Algorytm Dijkstry"
				<< std::endl << "3. Wyświetl graf w obu postaciach" << std::endl
				<< "4. Wygeneruj inny graf" << std::endl;
		std::cout << "6.kruskal\n7.ford belman" << std::endl;
		std::cin.clear();
		std::cin >> option;
		switch (option) {
		case 1:
			while (true) {
				std::cout << "Jakiej reprezentacji użyć w algorytmie?"
						<< std::endl << "1. Macierz Incydecji" << std::endl
						<< "2. Lista poprzedników i następników" << std::endl;
				std::cin >> option;
				if (option == 1)
					graph->PrimaMatrix();
				else if (option == 2)
					graph->PrimaList();
				else {
					std::cout << "Nie ma takiej opcji!" << std::endl
							<< std::endl;
					continue;
				}
				break;
			}
			break;
		case 6:
			while (true) {
				std::cout << "Jakiej reprezentacji użyć w algorytmie?"
						<< std::endl << "1. Macierz Incydecji" << std::endl
						<< "2. Lista poprzedników i następników" << std::endl;
				std::cin >> option;
				if (option == 1)
					graph->KruskalMatrix();
				else if (option == 2)
					graph->KruskalList();
				else {
					std::cout << "Nie ma takiej opcji!" << std::endl
							<< std::endl;
					continue;
				}
				break;
			}
			break;
		case 2:
			while (true) {
				std::cout << "Zdefiniuj wierzchołek początkowy: ";
				std::cin >> vertex_begin;
				if (vertex_begin == -1)
					return;
				else if (vertex_begin >= graph->vertex_number
						&& graph->vertex_number < 0) {
					std::cout << "Graf nie zawiera wierzchołka o numerze "
							<< vertex_begin << "." << std::endl
							<< "Obecna ilość wierzchołków: "
							<< graph->vertex_number << std::endl;

				} else
					break;
			}
			while (true) {
				std::cout << "Jakiej reprezentacji użyć w algorytmie?"
						<< std::endl << "1. Macierz Incydecji" << std::endl
						<< "2. Lista poprzedników i następników" << std::endl;
				std::cin >> option;
				if (option == 1)
					graph->DijkstraMatrix(vertex_begin);
				else if (option == 2)
					graph->DijkstraList(vertex_begin);
				else {
					std::cout << "Nie ma takiej opcji!" << std::endl
							<< std::endl;
					continue;
				}
				break;
			}
			break;
		case 7:
			while (true) {
				std::cout << "Zdefiniuj wierzchołek początkowy: ";
				std::cin >> vertex_begin;
				if (vertex_begin == -1)
					return;
				else if (vertex_begin >= graph->vertex_number
						&& graph->vertex_number < 0) {
					std::cout << "Graf nie zawiera wierzchołka o numerze "
							<< vertex_begin << "." << std::endl
							<< "Obecna ilość wierzchołków: "
							<< graph->vertex_number << std::endl;

				} else
					break;
			}
			while (true) {
				std::cout << "Jakiej reprezentacji użyć w algorytmie?"
						<< std::endl << "1. Macierz Incydecji" << std::endl
						<< "2. Lista poprzedników i następników" << std::endl;
				std::cin >> option;
				if (option == 1)
					graph->FordBellmanMatrix(vertex_begin);
				else if (option == 2)
					graph->FordBellmanList(vertex_begin);
				else {
					std::cout << "Nie ma takiej opcji!" << std::endl
							<< std::endl;
					continue;
				}
				break;
			}
			break;
		case 3:
			graph->print();
			std::cout << std::endl;
			break;
		case 4:
			delete graph;
			to_begin = true;
			break;
		}
	}
}

void ConsoleSupport::randomGraph() {
	int vertex_number;
	int density;
	to_begin = false;
	while (true) {
		std::cout << "Ile wierzchołków? ";
		std::cin >> vertex_number;
		if (vertex_number > 1)
			break;
		else
			std::cout << "Liczba wierzchołków nie może być mniejsza niż 2"
					<< std::endl;
	}
	int max_edge = vertex_number * (vertex_number - 1);
	double min_density = ceil(
			(((double) vertex_number - 1) * 100) / (double) max_edge);
	while (true) {

		std::cout << "Podaj gęstość grafu (co najmniej " << min_density
				<< "%) ";
		std::cin >> density;
		if (density < min_density || density > 100)
			std::cout << "Podana gęstość nie jest dozwolona" << std::endl;
		else
			break;
	}
	double edges = ceil((max_edge * density) / 100);
	graph = new Graph(vertex_number, edges);
	graph->randomGraph();
}

void ConsoleSupport::loadFile() {
	to_begin = false;
	ListElement* list_elem;
	std::string s, filename;
	int a = 0;
	int vertex_number;
	int edge_number;
	std::cout << "Nazwa pliku: ";
	std::cin >> filename;
	std::ifstream handle(filename);
	if (!handle) {
		std::cout << "Błąd wczytywania pliku: Nie można otworzyć pliku"
				<< std::endl;
		to_begin = true;

	} else {
		{
			handle >> vertex_number >> edge_number;
			if (!handle || edge_number < vertex_number - 1 || vertex_number <= 1
					|| edge_number > (vertex_number * (vertex_number - 1))) {
				std::cout << "Błąd wczytywania pliku: Zły plik lub zły format"
						<< std::endl;
				to_begin = true;
			} else {
				graph = new Graph(vertex_number, edge_number);
				while (!handle.eof() && a < edge_number) {
					handle >> graph->edges[a].vertex_begin
							>> graph->edges[a].vertex_end
							>> graph->edges[a].weight;
					if (graph->edges[a].vertex_begin >= vertex_number
							|| graph->edges[a].vertex_end >= vertex_number
							|| graph->edges[a].weight < 1) {
						std::cout
								<< "Błąd wczytywania pliku: Krawędzie są nieprawidłowo określone"
								<< std::endl;
						to_begin = true;
						break;
					}

					if (handle) {
						a++;
					} else {
						std::cout
								<< "Błąd wczytywania pliku: Krawędzie są nieprawidłowo określone"
								<< std::endl;
						to_begin = true;
						break;
					}
				}
				if (a == edge_number) {
					for (int i = 0; i < vertex_number; i++)
						graph->incidence_matrix[i] = new int[edge_number];
					for (int i = 0; i < vertex_number; i++)
						for (int j = 0; j < edge_number; j++) {
							graph->incidence_matrix[i][j] = 0;
						}

					for (int i = 0; i < vertex_number; i++)
						graph->adjacency_list[i] = NULL;

					for (int i = 0; i < edge_number; i++) {
						int wp = graph->edges[i].vertex_begin;
						int wk = graph->edges[i].vertex_end;
						list_elem = new ListElement;
						list_elem->vertex = wk;
						list_elem->weight = graph->edges[i].weight;
						list_elem->next = graph->adjacency_list[wp];
						graph->adjacency_list[wp] = list_elem;
						graph->incidence_matrix[wp][i] = 1;
						graph->incidence_matrix[wk][i] = -1;
					}
					handle.close();
					graph->changeToNonDirected();
					if (!(graph->checkIntegrity())) {
						std::cout
								<< "Błąd wczytywania pliku: Graf jest niespójny"
								<< std::endl;
						to_begin = true;
						delete graph;
					} else {
						algorithms();
					}

				} else if (!to_begin) {
					to_begin = true;
					std::cout
							<< "Błąd wczytywania pliku: Brak danych dotyczących krawędzi grafu"
							<< std::endl;
				}
			}
		}
	}
}
