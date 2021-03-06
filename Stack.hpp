/*
 * Stack.hpp
 *
 *  Created on: 9 maj 2018
 *      Author: darek
 */

#ifndef STACK_HPP_
#define STACK_HPP_
#include "ListElement.hpp"

class Stack {
	ListElement* s;

public:
	Stack() {
		s = NULL;
	}

	virtual ~Stack() {
		while (s)
			pop();
	}

	bool empty() {
		return !s;
	}

	int top() {
		return s->vertex;
	}

	void pop() {
		if (s) {
			ListElement* e = s;
			s = s->next;
			delete e;
		}
	}

	void push(int w) {
		ListElement* e = new ListElement;
		e->vertex = w;
		e->next = s;
		s = e;
	}
};

#endif /* STACK_HPP_ */
