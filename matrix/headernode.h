#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include "elementnode.h"

class Matrix;

class ElementNode;

class HeaderNode {
	public:
		HeaderNode() { index = -1; next = nullptr; down = nullptr; }
		HeaderNode(char ind) { index = ind; next = nullptr; down = nullptr; }
		
		char getIndex() { if(index != -1) return index; else return -1; }
		void setIndex(char ind) { index = ind; } 

		HeaderNode* getNext() { return next; }
		void setNext(HeaderNode *nuevo) { next = nuevo; }

		ElementNode* getElement() { return down; }
		void setElement(ElementNode *nuevo) { down = nuevo; }


    friend class Matrix;

	protected:
		char index;
		HeaderNode *next;
		ElementNode *down;

};


#endif