#ifndef MATRICES_CPP
#define MATRICES_CPP

#include <iostream>
#include <cmath>

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
            int numberOfColumns() {return number_of_columns};

};

#endif
