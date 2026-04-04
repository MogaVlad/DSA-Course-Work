#include "../include/PriorityQueue.h"

#include <exception>
using namespace std;

/// BC = WC = TC: Θ(1)
PriorityQueue::PriorityQueue(Relation r) : relation(r) {}

/// BC: Θ(1) - the priority queue is empty, or the new element has the highest priority (insert at head)
/// WC: Θ(numNodes) - the new element has the lowest priority (insert at tail)
/// TC: O(numNodes)
void PriorityQueue::push(TElem e, TPriority p) {
	DLLNode* newNode = new DLLNode;
	newNode->data = make_pair(e, p);

	if (isEmpty()) {
		dll.head = newNode;
		dll.tail = newNode;
		return;
	}

	DLLNode* current = dll.head;
	while (current != nullptr && relation(current->data.second, p)) {
		current = current->next;
	}

	if (current == dll.head) {
		newNode->next = dll.head;
		dll.head->prev = newNode;
		dll.head = newNode;
	}
	else if (current == nullptr) {
		newNode->prev = dll.tail;
		dll.tail->next = newNode;
		dll.tail = newNode;
	}
	else {
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

/// BC = WC = TC: Θ(1)
Element PriorityQueue::top() const {
	if (isEmpty())
		throw std::exception();
	return this->dll.head->data;
}

/// BC = WC = TC: Θ(1)
Element PriorityQueue::pop() {
	if (isEmpty())
		throw std::exception();

	DLLNode* nodeToDelete = this->dll.head;
	Element nodeToDeleteData = nodeToDelete->data;

	this->dll.head = this->dll.head->next;
	if (this->dll.head != nullptr)
		this->dll.head->prev = nullptr;
	else
		this->dll.tail = nullptr;
	delete nodeToDelete;

	return nodeToDeleteData;
}

/// BC = WC = TC: Θ(1)
bool PriorityQueue::isEmpty() const {
	return this->dll.head == nullptr;
}

/// BC = WC = TC: Θ(numNodes) - Must traverse all nodes to delete
PriorityQueue::~PriorityQueue() {
	DLLNode* current = this->dll.head;
	while (current != nullptr) {
		DLLNode* nextNode= current->next;
		delete current;
		current = nextNode;
	}
}