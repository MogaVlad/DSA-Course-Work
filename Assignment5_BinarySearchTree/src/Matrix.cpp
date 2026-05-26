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
	if (node == nullptr) return;
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


// BC: Θ(1) - the position is at the root or position is invalid
// WC: Θ(n) - the position is on the longest path in a degenerate BST (all nodes form a chain)
// TC: O(n), where n is the number of non-zero elements stored in the BST
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw exception();

	BSTNode** current = &root;
	while (*current != nullptr) {
		BSTNode* node = *current;
		if (i < node->line || (i == node->line && j < node->col)) {
			current = &(node->left);
		} else if (i > node->line || (i == node->line && j > node->col)) {
			current = &(node->right);
		} else {
			TElem old = node->value;
			if (e != NULL_TELEM) {
				node->value = e;
			} else {
				if (node->left == nullptr) {
					*current = node->right;
					delete node;
				} else if (node->right == nullptr) {
					*current = node->left;
					delete node;
				} else {
					BSTNode** successor = &(node->right);
					while ((*successor)->left != nullptr)
						successor = &((*successor)->left);
					node->line = (*successor)->line;
					node->col = (*successor)->col;
					node->value = (*successor)->value;
					BSTNode* succNode = *successor;
					*successor = succNode->right;
					delete succNode;
				}
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
		*current = newNode;
	}
	return NULL_TELEM;
}
