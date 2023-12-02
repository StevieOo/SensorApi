#ifndef ITERATOR_H
#define ITERATOR_H

template <class T> class Iterator {
public:
	virtual void first(void) = 0;
	virtual void next(void) = 0;
	virtual bool isDone(void) = 0;
	virtual T currentItem(void) = 0;
};

#endif