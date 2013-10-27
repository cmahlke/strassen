#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <memory.h>
#include <iostream.h>

// matrix is assumed to be square
class Matrix {
	// Everything will be made public to make the access easier
	public:
		int operator!= (Matrix &M);
		void SetSize (int s, char *);
		
		// Friend member functions
		friend istream &operator >> (istream&, Matrix&);
  		friend ostream &operator << (ostream&, Matrix&);

  		// Constructor and member nonstatic functions
  		Matrix();
  		Matrix(int, char * );
  		Matrix(int , int , int, Matrix& );
		~Matrix();
		inline int& operator()  (int x, int y) {  
			return *(this->mat + x * Matrix::startSize + y); 
		}
		inline int& elt (int x, int y) { 
			return *(this->mat + x * Matrix::startSize + y); 
		}
  		Matrix *submatrix(int);
  		Matrix* Matrix::sub(Matrix *A, Matrix *B);
  		Matrix* Matrix::add(Matrix *A, Matrix *B);
  		Matrix* Matrix::mult(Matrix *A, Matrix *B);
		
		// Variables used by the class
  		int size;
  		int initSize;
		char *name;
  		int type;
  		int *mat;
		private:
		int startSize;
};
#endif

