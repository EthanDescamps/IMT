#ifndef vector_CPP			//	© 2020, Alois Pichler
#define vector_CPP


#include "matrix.h"		// header file
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
#include <cmath>



template<typename T> 		// copy constructor
Vector<T>::Vector(const Vector<T>& src)
{ 	vLen= src.vLen;
 	vData= new T[vLen]; 	// deep copy
 	std::memcpy(vData, src.vData, vLen*sizeof(T));}


template<>				// construct a Vector from Matrix
Vector<double>::Vector(const Matrix& src)
{	vLen= src.rows()* src.cols();
	for(unsigned i= 0; i< src.Length(); i++)
    // vector.cpp has been moved to vector.tpp for template visibility.
    // Do not compile this file directly. If this file remains, it should be empty
    // or produce an error to prevent accidental compilation.

    #error "Do not compile vector.cpp; templates are in vector.tpp and included via matrix.h"

#endif vector_CPP