#ifndef LIST_H
#define LIST_H

#include "Aggregate.h"
#include "ListIterator.h"

template <class T> class Iterator;

template <class T> struct Node {
	Node(const T& item) : data(item), nextNode(0), prevNode(0) { }
	T data;
	Node<T>* nextNode;
	Node<T>* prevNode;
};

template <class T> class List : public Aggregate<T> {
public:
	List() : headNode(0), tailNode(0), listSize(0) { }

	~List() {
		clear();
	}

	void clear() {
		Node<T>* current(headNode);

		while (current)
		{
			Node<T>* next(current->nextNode);
			delete current;
			current = next;
		}
		headNode = nullptr;
		tailNode = nullptr;
		listSize = 0;
	}

	int size() { return listSize; }

	void push_back(const T& item) {
		insertItem(item, 0);
	}

	void push_front(const T& item) {
		insertItem(item, headNode);
	}

	void pop_back() {
		removeItem(tailNode);
	}

	void pop_front() {
		removeItem(headNode);
	}

	Node<T>* front()
	{
		return headNode;
	}

	Node<T>* back()
	{
		return tailNode;
	}

	bool empty() { return (listSize <= 0); }

	Iterator<T>* createIterator(void) override { return new ListIterator<T>(this); }

private:
	Node<T>* headNode;
	Node<T>* tailNode;
	int listSize;

	Node<T>* insertItem(const T& item, Node<T>* position) {
		Node<T>* node = new Node<T>(item);

		listSize++;
		node->nextNode = position;

		if (position) {
			node->prevNode = position->prevNode;
			position->prevNode = node;
		}
		else {
			node->prevNode = tailNode;
			tailNode = node;
		}

		if (node->prevNode) {
			node->prevNode->nextNode = node;
		}
		else {
			headNode = node;
		}

		return node;
	}

	void removeItem(Node<T>* position) {
		if (position) {
			if (position->prevNode)
				position->prevNode->nextNode = position->nextNode;

			if (position->nextNode)
				position->nextNode->prevNode = position->prevNode;

			if (position == headNode)
				headNode = position->nextNode;

			if (position == tailNode)
				tailNode = position->prevNode;

			delete position;

			listSize--;
		}
	}
};

#endif