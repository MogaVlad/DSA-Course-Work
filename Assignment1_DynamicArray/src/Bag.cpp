#include "../include/Bag.h"
#include "../include/BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
Bag::Bag() {
	this -> elementsCapacity = 10;
	this -> elementsSize = 0;
	this -> elements = new TElem[this -> elementsCapacity];

	this -> positionsCapacity = 10;
	this -> positionsSize = 0;
	this -> positions = new int[this -> positionsCapacity];
}

/// BC - Θ(1) - no resize needed, element already exists, and it is found on the first position
/// WC - Θ(positionsSize) - positions resize needed
/// TC - O(positionsSize)
void Bag::add(TElem elem) {
	if (this -> elementsCapacity == this -> elementsSize) {
		this -> elementsCapacity = this -> elementsCapacity * 2;

		TElem* temp = new TElem[this -> elementsCapacity];
		for (int i = 0; i < this -> elementsSize; i++)
			temp[i] = this -> elements[i];

		delete [] this -> elements;
		this -> elements = temp;
	}

	if (this -> positionsCapacity == this -> positionsSize) {
		this -> positionsCapacity = this -> positionsCapacity * 2;

		int* temp = new int[this -> positionsCapacity];
		for (int i = 0; i < this -> positionsSize; i++)
			temp[i] = this -> positions[i];

		delete [] this -> positions;
		this -> positions = temp;
	}

	bool found = false;
	for (int i = 0; i < this -> elementsSize; i++)
		if (this -> elements[i] == elem) {
			found = true;
			this -> positions[this -> positionsSize] = i;
			this -> positionsSize++;
			break;
		}

	if (!found) {
		this -> elements[this -> elementsSize] = elem;
		this -> positions[this -> positionsSize] = this -> elementsSize;
		this -> elementsSize++;
		this -> positionsSize++;
	}
}

/// BC - Θ(positionsSize) - always parses the whole positions array
/// WC - Θ(positionsSize) - parses the whole positions array, and the removed element appears only once, so it has to fix the displaced indexes
/// TC - Θ(positionsSize)
bool Bag::remove(TElem elem) {
	int occurrenceCount = 0, positionIndex = -1;

	for (int i = 0; i < this -> positionsSize; i++)
		if (this -> elements[this -> positions[i]] == elem) {
			occurrenceCount++;
			if (positionIndex == -1)
				positionIndex = i;
		}

	if (positionIndex == -1)
		return false;

	if (occurrenceCount == 1) {
		int removedElementPosition = this -> positions[positionIndex];
		int lastElementPosition = this -> elementsSize - 1;

		this -> elements[removedElementPosition] = this -> elements[lastElementPosition];
		this -> elementsSize--;

		for (int j = 0; j < this -> positionsSize; j++)
			if (this -> positions[j] == lastElementPosition)
				this -> positions[j] = removedElementPosition;
	}

	this -> positions[positionIndex] = this -> positions[this -> positionsSize - 1];
	this -> positionsSize--;
	return true;
}

/// BC - Θ(1) - element found on the first position
/// WC - Θ(elementsSize) - element not found in the unique elements array
/// TC - O(elementsSize)
bool Bag::search(TElem elem) const {
	for (int i = 0; i < this -> elementsSize; i++)
		if (this -> elements[i] == elem)
			return true;
	return false;
}

/// BC - Θ(positionsSize) - always parses the whole positions array
/// WC - Θ(positionsSize)
/// TC - Θ(positionsSize)
int Bag::nrOccurrences(TElem elem) const {
	int count = 0;
	for (int i = 0; i < this -> positionsSize; i++)
		if (this -> elements[this -> positions[i]] == elem)
			count++;
	return count;
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
int Bag::size() const {
	return this -> positionsSize;
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
bool Bag::isEmpty() const {
	return this -> positionsSize == 0;
}

/// BC - Θ(1) - always calls a Θ(1) function
/// WC - Θ(1)
/// TC - Θ(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

/// BC - Θ(1)
/// WC - Θ(1)
/// TC - Θ(1)
Bag::~Bag() {
	delete [] this -> elements;
	delete [] this -> positions;
}

/// BC - Θ(positionsSize) - always parses both the unique elements array and positions array (positionsSize >= elementsSize always)
/// WC - Θ(positionsSize)
/// TC - Θ(positionsSize)
Bag::Bag(const Bag& other) {
	this -> elementsCapacity = other.elementsCapacity;
	this -> elementsSize = other.elementsSize;
	this -> elements = new TElem[this -> elementsCapacity];
	for (int i = 0; i < this -> elementsSize; i++)
		this -> elements[i] = other.elements[i];

	this -> positionsCapacity = other.positionsCapacity;
	this -> positionsSize = other.positionsSize;
	this -> positions = new int[this -> positionsCapacity];
	for (int i = 0; i < this -> positionsSize; i++)
		this -> positions[i] = other.positions[i];
}

/// BC - Θ(1) - self assignment
/// WC - Θ(positionsSize) - not a self assignment, has to parse both the unique elements array and positions array (p >= u always)
/// TC - O(positionsSize)
Bag& Bag::operator=(const Bag& other) {
	if (this == &other)
		return *this;

	delete [] this -> elements;
	delete [] this -> positions;

	this -> elementsCapacity = other.elementsCapacity;
	this -> elementsSize = other.elementsSize;
	this -> elements = new TElem[this -> elementsCapacity];
	for (int i = 0; i < this -> elementsSize; i++)
		this -> elements[i] = other.elements[i];

	this -> positionsCapacity = other.positionsCapacity;
	this -> positionsSize = other.positionsSize;
	this -> positions = new int[this -> positionsCapacity];
	for (int i = 0; i < this -> positionsSize; i++)
		this -> positions[i] = other.positions[i];

	return *this;
}
