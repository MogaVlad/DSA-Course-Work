#include "../include/Map.h"
#include "../include/MapIterator.h"

// BC: Θ(1) - n is even or less than 2
// WC: Θ(√n) - n is prime, loop runs up to √n
// TC: O(√n)
bool Map::isPrime(int n) {
	if (n < 2)
		return false;

	if (n % 2 == 0 && n != 2)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

// BC: Θ(√n) - n is already prime
// WC: Θ(n·sqrt(n)) - many consecutive composites before the next prime
// TC: O(n·sqrt(n))
int Map::nextPrime(int n) {
	while (!isPrime(n))
		n++;
	return n;
}

// BC = WC = TC: Θ(1)
int Map::hashFunction(TKey k) const {
	return ((k % capacity) + capacity) % capacity;
}

// BC = WC = TC: Θ(1)
Map::Map() {
	capacity = 7;
	count = 0;
	table = new TElem[capacity];
	status = new int[capacity];
	for (int i = 0; i < capacity; i++)
		status[i] = EMPTY;
}

// BC = WC = TC: Θ(1)
Map::~Map() {
	delete[] table;
	delete[] status;
}

// BC = WC = TC: Θ(newCapacity) - newCapacity = nextPrime(2 * oldCapacity)
void Map::resize() {
	int oldCapacity = capacity;
	TElem* oldTable = table;
	int* oldStatus = status;

	capacity = nextPrime(2 * oldCapacity);
	table = new TElem[capacity];
	status = new int[capacity];
	for (int i = 0; i < capacity; i++)
		status[i] = EMPTY;
	count = 0;

	for (int i = 0; i < oldCapacity; i++) {
		if (oldStatus[i] == OCCUPIED)
			add(oldTable[i].first, oldTable[i].second);
	}

	delete[] oldTable;
	delete[] oldStatus;
}

// BC: Θ(1) - the first probed slot is EMPTY or contains the key
// WC: Θ(newCapacity) - the key doesn't exist and a resize is needed
// TC: O(newCapacity)
TValue Map::add(TKey c, TValue v) {
	int h = hashFunction(c);
	int firstDeletedPos = -1;

	for (int i = 0; i < capacity; i++) {
		int pos = (h + i * i) % capacity;

		if (status[pos] == OCCUPIED && table[pos].first == c) {
			TValue old = table[pos].second;
			table[pos].second = v;
			return old;
		}

		if (status[pos] == DELETED && firstDeletedPos == -1)
			firstDeletedPos = pos;

		if (status[pos] == EMPTY) {
			int insertPos = pos;
			if (firstDeletedPos != -1)
				insertPos= firstDeletedPos;

			table[insertPos] = TElem(c, v);
			status[insertPos] = OCCUPIED;
			count++;

			double alpha = (double)count / capacity;
			if (alpha > LOAD_FACTOR_THRESHOLD)
				resize();

			return NULL_TVALUE;
		}
	}

	if (firstDeletedPos != -1) {
		table[firstDeletedPos] = TElem(c, v);
		status[firstDeletedPos] = OCCUPIED;
		count++;

		double alpha = (double)count / capacity;
		if (alpha > LOAD_FACTOR_THRESHOLD)
			resize();

		return NULL_TVALUE;
	}

	resize();
	return add(c, v);
}

// BC: Θ(1) - the key is at the first probed position, or the first position is EMPTY
// WC: Θ(capacity) - the key doesn't exist
// TC: O(capacity)
TValue Map::search(TKey c) const {
	int h = hashFunction(c);

	for (int i = 0; i < capacity; i++) {
		int pos = (h + i * i) % capacity;

		if (status[pos] == OCCUPIED && table[pos].first == c)
			return table[pos].second;

		if (status[pos] == EMPTY)
			return NULL_TVALUE;
	}

	return NULL_TVALUE;
}

// BC: Θ(1) - the key is at the first probed position, or the first position is EMPTY
// WC: Θ(capacity) - the key is at the end of a long probe chain, or absent and no EMPTY slot is found early
// TC: O(capacity)
TValue Map::remove(TKey c) {
	int h = hashFunction(c);

	for (int i = 0; i < capacity; i++) {
		int pos = (h + i * i) % capacity;

		if (status[pos] == OCCUPIED && table[pos].first == c) {
			TValue deletedValue = table[pos].second;
			status[pos] = DELETED;
			count--;
			return deletedValue;
		}

		if (status[pos] == EMPTY)
			return NULL_TVALUE;
	}
	return NULL_TVALUE;
}

// BC = WC = TC: Θ(1)
int Map::size() const {
	return count;
}

// BC = WC = TC: Θ(1)
bool Map::isEmpty() const {
	return count == 0;
}

// Complexity of MapIterator constructor
// BC: Θ(1) - the first slot in the table is OCCUPIED
// WC: Θ(capacity) - there is no element in the table / the first element in the table is found on the last position
// TC: O(capacity)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}
