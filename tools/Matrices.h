#ifndef MATRICES_CPP
#define MATRICES_CPP

#include <iostream>
#include <cmath>

//! A class that defines a matrix
/*!
 * This class defines a matrix of arbitrary dimesions, I think
 * the current implementation restricts this to a square matrix
 * (nxn) where n is the square root of the value given to the 
 * constructor.
 */

class Matrix
{
    private:
            double* values;
            int number_of_columns;
            int number_of_elements;

    public:
            Matrix(int elements);
            ~Matrix();

            bool setElement(int row, int column, double value);
            double getElement(int row, int column);

            void showMatrix();
            int numberOfColumns() {return number_of_columns;};

};

#endif
