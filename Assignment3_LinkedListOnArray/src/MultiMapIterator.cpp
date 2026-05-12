#include "../include/MultiMapIterator.h"
#include "../include/MultiMap.h"
#include <exception>

using namespace std;


/// BC = WC = TC = Θ(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	currentKey = col.keyHead;
	if (currentKey != -1)
		currentVal = col.keyNodes[currentKey].valHead;
	else
		currentVal = -1;
}


/// BC = WC = TC = Θ(1)
TElem MultiMapIterator::getCurrent() const {
	if (!valid())
		throw exception();
	return make_pair(col.keyNodes[currentKey].key, col.valNodes[currentVal].value);
}


/// BC = WC = TC = Θ(1)
bool MultiMapIterator::valid() const {
	return currentKey != -1 && currentVal != -1;
}


/// BC = WC = TC = Θ(1)
void MultiMapIterator::next() {
	if (!valid())
		throw exception();
	currentVal = col.valNodes[currentVal].next;
	if (currentVal == -1) {
		currentKey = col.keyNodes[currentKey].next;
		if (currentKey != -1)
			currentVal = col.keyNodes[currentKey].valHead;
	}
}


/// BC = WC = TC = Θ(1)
void MultiMapIterator::first() {
	currentKey = col.keyHead;
	if (currentKey != -1)
		currentVal = col.keyNodes[currentKey].valHead;
	else
		currentVal = -1;
}
