#include "../include/Matrix.h"
#include <exception>
using namespace std;


// BC = WC = TC: Θ(1)
Matrix::Matrix(int nrLines, int nrCols) {
	if (nrLines <= 0 || nrCols <= 0)
		throw exception();

	this->nrLin = nrLines;
	this->nrCol = nrCols;
	this->root = nullptr;
}


// BC = WC = TC: Θ(n), where n is the number of non-zero elements stored in the BST
void Matrix::destroyTree(BSTNode* node) {
	if (node == nullptr)
		return;
	destroyTree(node->left);
	destroyTree(node->right);
	delete node;
}


// BC = WC = TC: Θ(n), where n is the number of non-zero elements stored in the BST
Matrix::~Matrix() {
	destroyTree(root);
}


// BC = WC = TC: Θ(1)
int Matrix::nrLines() const {
	return nrLin;
}


// BC = WC = TC: Θ(1)
int Matrix::nrColumns() const {
	return nrCol;
}


// BC: Θ(1) - the searched position is at the root or position is invalid
// WC: Θ(n) - the searched position is on the longest path in a degenerate BST (all nodes form a chain)
// TC: O(n), where n is the number of non-zero elements stored in the BST
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw exception();

	BSTNode* current = root;
	while (current != nullptr) {
		if (i < current->line || (i == current->line && j < current->col))
			current = current->left;
		else if (i > current->line || (i == current->line && j > current->col))
			current = current->right;
		else
			return current->value;
	}

	return NULL_TELEM;
}


// BC: Θ(1) - the position is invalid, or the position is at the root and e != NULL_TELEM
// WC: Θ(n) - the position is on the longest path in a degenerate BST (all nodes form a chain)
// TC: O(n), where n is the number of non-zero elements stored in the BST
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw exception();

	BSTNode* current = root;
	BSTNode* parent = nullptr;
	while (current != nullptr) {
		if (i < current->line || (i == current->line && j < current->col)) {
			parent = current;
			current = current->left;
		}
		else if (i > current->line || (i == current->line && j > current->col)) {
			parent = current;
			current = current->right;
		}
		else {
			TElem old = current->value;
			if (e != NULL_TELEM) {
				current->value = e;
			} else { // e == NULL_TELEM - we have to eliminate the current element
				BSTNode* replacement;
				if (current->left == nullptr) // no child on the left, or current is a leaf
					replacement = current->right;
				else if (current->right == nullptr) // no child on the right
					replacement = current->left;
				else {
					BSTNode* succParent = current;
					BSTNode* successor = current->right;
					while (successor->left != nullptr) {
						succParent = successor;
						successor = successor->left;
					}
					current->line = successor->line;
					current->col = successor->col;
					current->value = successor->value;
					if (succParent == current)
						succParent->right = successor->right;
					else
						succParent->left = successor->right;
					delete successor;
					return old;
				}

				if (parent == nullptr) // current == root
					root = replacement;
				else if (parent->left == current)
					parent->left = replacement;
				else
					parent->right = replacement;
				delete current;
			}
			return old;
		}
	}

	if (e != NULL_TELEM) {
		BSTNode* newNode = new BSTNode;
		newNode->line = i;
		newNode->col = j;
		newNode->value = e;
		newNode->left = nullptr;
		newNode->right = nullptr;
		if (parent == nullptr) // root == nullptr
			root = newNode;
		else if (i < parent->line || (i == parent->line && j < parent->col))
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	return NULL_TELEM;
}
