#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

int ceilLogAndCompute(int x);

Matrix::Matrix() {
	name = NULL;
	type = 1;
	initSize = size = startSize = 0;
	mat = NULL;
}

Matrix::Matrix(int s, char *str) {
  initSize 	= s;
  type 		= 0;
  startSize = size = ceilLogAndCompute(s);

  if(size == 0) {
	  cerr << "Error: Inappropriate matrix size." << endl;
	  exit (1);
  } else {     // initialize every element to 0
	  name = new char[strlen(str)+2];
	  strcpy (name, str);
	  mat = new int [size*size];
	  memset (mat , 0, size*size*sizeof(int));
  }
}

// Constructor that will be used by a submatrix function
Matrix::Matrix(int s, int adjSize, int c, Matrix& m) {
	size = initSize = s;
  	type = 1;
  	startSize = adjSize;
 	mat = &(m.mat[c]);
}


Matrix::~Matrix() {
  if (type == 0) {
	  delete mat;
  }
}


Matrix * Matrix::submatrix(int which) {
	switch(which) {
		case 1:
			return new Matrix (size/2, startSize, 0, *this);
    	case 2:
      		return new Matrix (size/2, startSize, size/2, *this);
    	case 3:
      		return new Matrix (size/2, startSize, (size / 2) * startSize, *this);
    	case 4:
      		return new Matrix (size/2, startSize, (size / 2) * startSize + size/2, *this);
  		default:
			cerr << "Error: The matrix only divides in four submatrices." << endl;
			exit(1);
	}
}

Matrix * Matrix::mult(Matrix *A, Matrix *B) {
	if ((B->initSize != A->initSize) || (B->size != A->size)) {
    	cerr << "Error: Can't multiply matrices of different sizes." << endl;
    	exit(1);
	}

  	int matsize = this->initSize = A->initSize;
  	this->size = A->size;

  	int tmp, i, j, k;

  	for (i = 0; i < matsize; i++) {
    	for (j = 0; j < matsize; j++) {
      		for (tmp = 0, k = 0; k < matsize; k++) {
				tmp += A->elt(i,k) * B->elt(k,j);
			}
			elt(i,j) = tmp;
		}
	}
	return this;
}

ostream& operator<< (ostream& out, Matrix& m) {
	for (int i = 0; i < m.initSize; i++) {
		for (int j = 0; j < m.initSize; j++) {
			out << setw(5) <<  m(i,j) << '\t';
		}
		out << endl;
	}  
	return out;
}  

// Assuming the input is going to be entered correctly
istream& operator >> (istream& in, Matrix& m) {
	for (int i = 0; i < m.initSize; i++) {
    	for (int j = 0; j < m.initSize; j++) {
      		in >> m(i,j);
		}
  }
  return in;
}

Matrix* Matrix::add (Matrix *A, Matrix *B) {
  if ((A->size != B->size) || (A->initSize != B->initSize)) {
    cerr << "Error: Trying to add two matrices of different sizes." << endl;
    exit(1);
  }

  this->size = A->size;
  int matsize = this->initSize = A->initSize;

  for (int i = 0; i < matsize; i++) {
	  for (int j = 0; j < matsize; j++) {
		  elt(i,j) = A->elt(i,j) + B->elt(i,j);
	  }
  }
  return this;
}

Matrix* Matrix::sub (Matrix *A, Matrix *B) {
	if ((A->size != B->size) || (A->initSize != B->initSize)) {
		cerr << "Error: Trying to add two matrices of different sizes." << endl;
		exit(1);
	}

  	this->size = B->size;
  	int matsize = this->initSize = B->initSize;

  	for (int i = 0; i < matsize; i++) {
    	for (int j = 0; j < matsize; j++) {
      		elt(i,j) = A->elt(i,j) - B->elt(i,j);
		}
	}
	return this;
}

int ceilLogAndCompute(int y) {
	if (y <= 2)
		return 2;
	return (int) pow (2.0, (int)(log(y)/log(2.0) + .999));
}

void Matrix::SetSize(int s, char *str) {
	if (mat)
		delete [] mat;

	type 		= 0;
	initSize 	= s;
	startSize 	= size = ceilLogAndCompute(s);
	mat 		= new int [size * size];
	name 		= new char[strlen(str)+2];
	strcpy(name, str);
}

int Matrix::operator !=(Matrix & M) {
	if ((size != M.size) || (initSize != M.initSize)) {
		cerr << "Can\'t compare matrixes of diff sizes\n";
	}

	for (int i = 0; i < initSize ; i++)
		for (int j = 0; j < initSize; j++) {
			if (this->operator()(i,j) != M(i,j))
				return 1;
		}
	return 0;
}
