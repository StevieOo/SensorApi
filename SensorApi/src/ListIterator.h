#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "Iterator.h"
#include "List.h"

template <class T> class List;
template <class T> class Node;

template <class T> 
class ListIterator : public Iterator<T> {
public:
	ListIterator(List<T>* _list) {
		list = _list;
		currentNode = list->front();
	}

	void first(void) override {
		currentNode = list->front();
	}

	void next(void) override {
		currentNode = currentNode->nextNode;
	}

	bool isDone(void) override {
		return (currentNode == nullptr);
	}

	T currentItem(void) override {
		return currentNode->data;
	}


private:
	List<T>* list;
	Node<T>* currentNode;
};

#endif