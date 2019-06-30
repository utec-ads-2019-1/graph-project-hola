#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include "headernode.h"
#include "elementnode.h"

using namespace std;

class Matrix {
private:
    Node *root;
    unsigned len;

public:
		Matrix() {
			root = new Node;
			rows = columns = 0;
		}

    Matrix(unsigned len) {
			root = new Node;
			HeaderNode* row = new HeaderNode(0);
			HeaderNode* column = new HeaderNode(0);

			root->setHeaders(row, column);
			
			addHeaders(row, len);
			addHeaders(column, len);

			this->len = len;
		}

		HeaderNode* getRow(char index) {
			HeaderNode *tmp = root->getRow();

			while (tmp != nullptr) {
				if (tmp->getIndex() == index) return tmp;
				tmp = tmp->getNext();
			}

			return nullptr;
		}

		HeaderNode* getCol(char index) {
			HeaderNode *tmp = root->getColumn();

			while (tmp != nullptr) {
				if (tmp->getIndex() == index) return tmp;
				tmp = tmp->getNext();
			}

			return nullptr;
		}

		ElementNode* getElement(unsigned row, unsigned column) {
			HeaderNode *r = getRow(row);
			HeaderNode *c = getCol(column);

			if (r != nullptr && c != nullptr) {
				ElementNode *tmp = r->getElement();
				
				while (tmp != nullptr) {
					if (tmp->getColumn()->getIndex() == column) return tmp;

					tmp = tmp->getRight();
				}
				
				return nullptr;	
			}

			return nullptr;

		}

		bool findElement(char r_index, char c_index, int e_value) {
			HeaderNode *row = getRow(r_index);
			HeaderNode *column = getCol(c_index);

			if (row != nullptr && column != nullptr) {
				ElementNode *tmp = row->getElement();
				
				while (tmp != nullptr) {
					if (tmp->getValue() == e_value && tmp->getColumn()->getIndex() == c_index )
						return true;
					tmp = tmp->getRight();
				}
				
				return false;	
			}

			return false;
		}

		int getElementValue(unsigned row, unsigned column) {
			ElementNode* element = getElement(row, column);

			if (element) return element->getValue();

			else return 0;
		}

		void addHeaders(HeaderNode* node, int n) {
			int i = 1;

			HeaderNode* tmp = node;
			while ( i < n ) {
				HeaderNode* nuevo = new HeaderNode(tmp->getIndex() + 1);
				if (nuevo->getIndex() == (node->getIndex() + 1)) node->setNext(tmp);
				tmp->setNext(nuevo);
				tmp = nuevo;
				i++;
			}
		}

		bool addElement(unsigned row, unsigned column, int value) {
			if (findElement(row, column, value)) return false;

			else {
				HeaderNode *r = getRow(row);
				HeaderNode *c = getCol(column);

				ElementNode *element = new ElementNode(r, c, value);

				while (r->getIndex() < row) r = r->getNext();
				
				if (r->getElement() == nullptr) r->setElement(element);
				
				else {
					element->setRight(r->getElement()->getRight());
					r->getElement()->setRight(element);
				}

				while (c->getIndex() < column) c = c->getNext();
				
				if (c->getElement() == nullptr) {
					c->setElement(element);
				}

				else {
					element->setDown(c->getElement()->getDown());
					c->getElement()->setDown(element);
				}
			
				return true;
			}	
		}

    void set(unsigned row, unsigned column, int value) {
			addElement(row, column, value);
		}



    int operator()(unsigned row, unsigned column) {
			return getElementValue(row, column);
		}

    void print() {
			for (int i = 0; i < getRowNum(); i++) {
				for (int j = 0; j < getColNum(); j++) {
					std::cout << getElementValue(i, j) << " ";
				}

				std::cout << "\n";
			}
		}

};

#endif //SPARSE_MATRIX_MATRIX_H