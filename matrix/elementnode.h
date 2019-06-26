#ifndef ELEMENint_H
#define ELEMENint_H

#include <iostream>
#include "headernode.h"

class Matrix;

class HeaderNode;

class ElementNode {
  public:
	 	ElementNode(){ value = 0; column = row = nullptr; down = right = nullptr; }
		ElementNode(HeaderNode *r, HeaderNode *c, int data) {
			down = nullptr;
			right = nullptr;
			row = r;
			column = c;
			value = data;
		}

		int getValue() { return value; }
		void setValue(int val) { value = val; }

		HeaderNode* getColumn() { return column; }
		void setColumn(HeaderNode *col) { column = col; }

		HeaderNode* getRow() { return row; }
		void setRow(HeaderNode *r) { row = r; }

		ElementNode* getDown() { return down; }
		void setDown(ElementNode *dwn) { down = dwn; }

		ElementNode* getRight() { return right; }
		void setRight(ElementNode *rgt) { right = rgt; }

    friend class Matrix;
		
	protected:
		int value;
		HeaderNode *column, *row;
		ElementNode *down, *right;
};

#endif