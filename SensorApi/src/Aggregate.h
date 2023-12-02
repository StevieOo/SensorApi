#ifndef AGGREGATE_H
#define AGGREGATE_H

#include "Iterator.h"

template <class T> class Aggregate {
public:
	virtual Iterator<T>* createIterator(void) = 0;
};

#endif