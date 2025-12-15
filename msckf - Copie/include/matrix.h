#ifndef matrix_H		//	© 2020, Alois Pichler
#define matrix_H


#include <cstring>		// enable memcpy
#include <cassert>		// enable assert
#include <ostream>
#include "vector3d.h"
#include "types.h"

		// forward declaration (see below)




class Matrix
{	public:

	Matrix(): mRows(0), mCols(0), mData(nullptr) {};	// default constructor
	Matrix(const unsigned);					// constructor of a square matrix
	Matrix(const unsigned, const unsigned);	// constructor of a rectangular matrix
	Matrix Let(std::initializer_list<double>);
	Matrix(const Matrix&);					// copy constructor
	~Matrix(){	delete [] mData;}			// destructor	// construct from Vector


	template<unsigned mRows, unsigned mCols>	// construct from array
	Matrix(const double (&arr)[mRows][mCols]) : Matrix(mRows, mCols)
	{	std::memcpy(mData, arr, mRows* mCols* sizeof(double));}
	//	Matrix A((double[][3]){{ -1.6, 7, 13}, {5, 9.3, 2}}); enable array initialization

	Matrix& operator= (const Matrix&);		// assignment operator=

	double* operator[] (unsigned) const;	// element access operator
	double& operator()(unsigned, unsigned) const;//	the indexes are ONE-based, NOT zero based.
	unsigned rows() const {return mRows;}	// the number of rows
	unsigned cols() const {return mCols;}	// the number of columns

	Matrix operator+ (const Matrix&);		// matrix addition
	Matrix operator+ (double);				// add a multiple of the unit matrix
	Matrix operator- (const Matrix&);		// matrix subtraction
	Matrix operator* (double);				// multiplication by scalar
	Matrix operator* (const Matrix&);		// matrix multiplication

	Matrix Fill(const double);
	
	private:
	double *mData; unsigned mRows, mCols;
};


Matrix Eye(const unsigned);					// identity matrix
Matrix Transpose(Matrix);					// transpose matrix
std::ostream& operator << (std::ostream&, const Matrix);

// multiplie R (3x3) par v, écrit le résultat dans out
Vector3d multiplyRbyVector(const Matrix& R, const Vector3d& v);
void multiplyRbyVector(const Matrix& R, const Vector3d& v, Vector3d& out);



// Prototypes from inverse.cpp (declared here to avoid including inverse.cpp in header)



 // detailed template definitions (moved from vector.cpp)


#endif		// matrix_H