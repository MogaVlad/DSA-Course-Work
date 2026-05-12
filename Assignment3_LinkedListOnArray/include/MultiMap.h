#pragma once
#include<vector>
#include<utility>
#include <climits>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	struct ValueNode {
		TValue value;
		int next, prev;
	};

	struct KeyNode {
		TKey key;
		int next, prev;
		int valHead, valTail;
	};

	KeyNode* keyNodes;
	int keyCap, keyHead, keyTail, keyFirstEmpty, keyCount;

	ValueNode* valNodes;
	int valCap, valFirstEmpty;

	int totalPairs;

	int allocateKey();
	void freeKey(int position);
	int allocateVal();
	void freeVal(int position);
	int findKey(TKey c) const;

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();

};
