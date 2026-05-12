#include "../include/MultiMap.h"
#include "../include/MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


/// BC = WC = TC = Θ(1)
MultiMap::MultiMap() {
	keyCap = 10;
	keyHead = -1;
	keyTail = -1;
	keyFirstEmpty = 0;
	keyCount = 0;
	keyNodes = new KeyNode[keyCap];

	for (int i = 0; i < keyCap; i++) {
		keyNodes[i].next = i + 1;
		keyNodes[i].prev = i - 1;
	}
	keyNodes[keyCap - 1].next = -1;

	valCap = 10;
	valFirstEmpty = 0;
	valNodes = new ValueNode[valCap];
	for (int i = 0; i < valCap; i++) {
		valNodes[i].next = i + 1;
		valNodes[i].prev = i - 1;
	}
	valNodes[valCap - 1].next = -1;

	totalPairs = 0;
}


/// BC = Θ(1) - when the free list is not empty,
/// WC = Θ(k) - when resize is needed (k = number of unique keys),
/// TC = O(k)
int MultiMap::allocateKey() {
	if (keyFirstEmpty == -1) {
		int newCap = keyCap * 2;
		KeyNode* newNodes = new KeyNode[newCap];
		for (int i = 0; i < keyCap; i++)
			newNodes[i] = keyNodes[i];

		for (int i = keyCap; i < newCap; i++) {
			newNodes[i].next = i + 1;
			newNodes[i].prev = i - 1;
		}
		newNodes[keyCap].prev = -1;
		newNodes[newCap - 1].next = -1;
		keyFirstEmpty = keyCap;

		delete[] keyNodes;
		keyNodes = newNodes;
		keyCap = newCap;
	}

	int pos = keyFirstEmpty;
	keyFirstEmpty = keyNodes[pos].next;
	if (keyFirstEmpty != -1)
		keyNodes[keyFirstEmpty].prev = -1;
	keyNodes[pos].next = -1;
	keyNodes[pos].prev = -1;
	return pos;
}


/// BC = WC = TC = Θ(1)
void MultiMap::freeKey(int pos) {
	keyNodes[pos].next = keyFirstEmpty;
	keyNodes[pos].prev = -1;
	if (keyFirstEmpty != -1)
		keyNodes[keyFirstEmpty].prev = pos;
	keyFirstEmpty = pos;
}


/// BC = Θ(1) - when the free list is not empty,
/// WC = Θ(n) - when resize is needed,
/// TC = O(n)
int MultiMap::allocateVal() {
	if (valFirstEmpty == -1) {
		int newCap = valCap * 2;
		ValueNode* newNodes = new ValueNode[newCap];
		for (int i = 0; i < valCap; i++)
			newNodes[i] = valNodes[i];

		for (int i = valCap; i < newCap; i++) {
			newNodes[i].next = i + 1;
			newNodes[i].prev = i - 1;
		}
		newNodes[valCap].prev = -1;
		newNodes[newCap - 1].next = -1;
		valFirstEmpty = valCap;

		delete[] valNodes;
		valNodes = newNodes;
		valCap = newCap;
	}

	int pos = valFirstEmpty;
	valFirstEmpty = valNodes[pos].next;
	if (valFirstEmpty != -1)
		valNodes[valFirstEmpty].prev = -1;
	valNodes[pos].next = -1;
	valNodes[pos].prev = -1;
	return pos;
}


/// BC = WC = TC = Θ(1)
void MultiMap::freeVal(int position) {
	valNodes[position].next = valFirstEmpty;
	valNodes[position].prev = -1;
	if (valFirstEmpty != -1)
		valNodes[valFirstEmpty].prev = position;
	valFirstEmpty = position;
}


/// BC = Θ(1) - key is the first in the list,
/// WC = Θ(k) - key is last or not found (k = number of unique keys),
/// TC = O(k)
int MultiMap::findKey(TKey c) const {
	int current = keyHead;
	while (current != -1) {
		if (keyNodes[current].key == c)
			return current;

		current = keyNodes[current].next;
	}
	return -1;
}


/// BC = Θ(n) - key already exists and no resize needed,
/// WC = Θ(k + n) - key not found + resize needed (k = unique keys, n = total pairs),
/// TC = O(k + n)
void MultiMap::add(TKey c, TValue v) {
	int keyPos = findKey(c);
	if (keyPos == -1) {
		keyPos = allocateKey();
		keyNodes[keyPos].key = c;
		keyNodes[keyPos].valHead = -1;
		keyNodes[keyPos].valTail = -1;
		keyNodes[keyPos].next = -1;
		keyNodes[keyPos].prev = keyTail;
		if (keyTail != -1)
			keyNodes[keyTail].next = keyPos;
		keyTail = keyPos;
		if (keyHead == -1)
			keyHead = keyPos;
		keyCount++;
	}

	int valPos = allocateVal();
	valNodes[valPos].value = v;
	valNodes[valPos].next = -1;
	valNodes[valPos].prev = keyNodes[keyPos].valTail;
	if (keyNodes[keyPos].valTail != -1)
		valNodes[keyNodes[keyPos].valTail].next = valPos;
	keyNodes[keyPos].valTail = valPos;
	if (keyNodes[keyPos].valHead == -1)
		keyNodes[keyPos].valHead = valPos;

	totalPairs++;
}


/// BC = Θ(1) - key and value are first in their lists,
/// WC = Θ(k + v) - key search + value search (k = unique keys, v = values for that key),
/// TC = O(k + v)
bool MultiMap::remove(TKey c, TValue v) {
	int keyPos = findKey(c);
	if (keyPos == -1)
		return false;

	int valCur = keyNodes[keyPos].valHead;
	while (valCur != -1) {
		if (valNodes[valCur].value == v) {
			int prevVal = valNodes[valCur].prev;
			int nextVal = valNodes[valCur].next;
			if (prevVal != -1)
				valNodes[prevVal].next = nextVal;
			else
				keyNodes[keyPos].valHead = nextVal;
			if (nextVal != -1)
				valNodes[nextVal].prev = prevVal;
			else
				keyNodes[keyPos].valTail = prevVal;
			freeVal(valCur);
			totalPairs--;

			if (keyNodes[keyPos].valHead == -1) {
				int prevKey = keyNodes[keyPos].prev;
				int nextKey = keyNodes[keyPos].next;
				if (prevKey != -1)
					keyNodes[prevKey].next = nextKey;
				else
					keyHead = nextKey;
				if (nextKey != -1)
					keyNodes[nextKey].prev = prevKey;
				else
					keyTail = prevKey;
				freeKey(keyPos);
				keyCount--;
			}
			return true;
		}
		valCur = valNodes[valCur].next;
	}
	return false;
}


/// BC = Θ(1) - key is first in the list,
/// WC = Θ(k + v) - key search + traversing all values (k = unique keys, v = values for that key),
/// TC = O(k + v)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> result;
	int keyPos = findKey(c);
	if (keyPos == -1)
		return result;
	int valCur = keyNodes[keyPos].valHead;
	while (valCur != -1) {
		result.push_back(valNodes[valCur].value);
		valCur = valNodes[valCur].next;
	}
	return result;
}


/// BC = WC = TC = Θ(1)
int MultiMap::size() const {
	return totalPairs;
}


/// BC = WC = TC = Θ(1)
bool MultiMap::isEmpty() const {
	return totalPairs == 0;
}


/// BC = WC = TC = Θ(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


/// BC = WC = TC = Θ(1)
MultiMap::~MultiMap() {
	delete[] keyNodes;
	delete[] valNodes;
}