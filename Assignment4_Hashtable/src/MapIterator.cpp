#include "../include/Map.h"
#include "../include/MapIterator.h"
#include <exception>
using namespace std;

// BC: Θ(1) - the first slot is OCCUPIED
// WC: Θ(capacity) - there is no element in the table / the first element in the table is found on the last position
// TC: O(capacity)
MapIterator::MapIterator(const Map& d) : map(d)
{
	currentIndex = 0;
	while (currentIndex < map.capacity && map.status[currentIndex] != Map::OCCUPIED)
		currentIndex++;
}

// BC: Θ(1) - the first slot is OCCUPIED
// WC: Θ(capacity) - there is no element in the table / the first element in the table is found on the last position
// TC: O(capacity)
void MapIterator::first() {
	currentIndex = 0;
	while (currentIndex < map.capacity && map.status[currentIndex] != Map::OCCUPIED)
		currentIndex++;
}

// BC: Θ(1) - the very next slot is OCCUPIED
// WC: Θ(capacity) - there are no more elements in the table
// TC: O(capacity)
void MapIterator::next() {
	if (!valid())
		throw exception();
	currentIndex++;
	while (currentIndex < map.capacity && map.status[currentIndex] != Map::OCCUPIED)
		currentIndex++;
}

// BC = WC = TC: Θ(1)
TElem MapIterator::getCurrent(){
	if (!valid())
		throw exception();
	return map.table[currentIndex];
}

// BC = WC = TC: Θ(1)
bool MapIterator::valid() const {
	return currentIndex < map.capacity;
}
