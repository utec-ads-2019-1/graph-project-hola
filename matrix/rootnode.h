#ifndef ROOT_H
#define ROOT_H

#include "headernode.h"

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
	HeaderNode<T> *fcolumn;
	HeaderNode<T>	*frow;
public:
    Node() { fcolumn = nullptr; frow = nullptr; }
		
		void setHeaders(HeaderNode<T> *row, HeaderNode<T> *column) { 
			frow = row;
			fcolumn = column; }

		HeaderNode<T>* getColumn() { return fcolumn; }
		void setColumn(HeaderNode<T> *column) { fcolumn = column; }

		HeaderNode<T>* getRow() { return frow; }
		void setRow(HeaderNode<T> *row) { frow = row; }

    friend class Matrix<T>;
};

#endif //ROOT_H