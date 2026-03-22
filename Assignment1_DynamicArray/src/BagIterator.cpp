#include <exception>
#include "../include/BagIterator.h"
#include "../include/Bag.h"

using namespace std;

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this -> currentIndex = 0;
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
void BagIterator::first() {
	this -> currentIndex = 0;
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
void BagIterator::next() {
	if (!valid())
		throw exception();
	this -> currentIndex++;
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
bool BagIterator::valid() const {
	return this -> currentIndex < this -> bag.size();
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception();
	int position = this -> bag.positions[this -> currentIndex];
	return this -> bag.elements[position];
}
