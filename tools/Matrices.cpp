#include "Matrices.h"

// Constructor allocates memory for the matrix
Matrix::Matrix(int elements)
{
    values = new double[elements];

    number_of_elements = elements;
    number_of_columns = sqrt(elements);

    std::cout << "New matrix object created\n";
}

// Destructor
Matrix::~Matrix()
{
    delete values;
}

// Set the contents of the ith row and jth column
// has a boolean return value to signify if it was a success or not
bool Matrix::setElement(int row, int column, double value)
{
    // Since the elements are stored in a linear array, convert row/colmun to the appropriate index
    int index = (row * number_of_columns) + column;

    // Check that the provided index is in range
    if (number_of_elements < index)
    {
        std::cout << "Error!: Index provided to matrix out of range... \nAborting....\n";
        return false;
    }

    // Add the appropriate value
    values[index] = value;

    return true;
}

// Get element from the ith row and jth column
double Matrix::getElement(int row, int column)
{
    // Since elements are stored in a linear array convert row/column to the correct index
    int index = (row * number_of_columns) + column;

    // Check that the provided index is in range
    if (number_of_elements < index)
    {
        std::cout << "Error!: Index provided to matrix out of range... \nAborting....\n";
        return false;
    }

    // Get the value stored there
    return values[index];
}

// Print the contents of the matrix to screen
void Matrix::showMatrix()
{
    int index;

    for (int i = 0; i < number_of_columns; i++)
    {

        for (int j = 0 ; j < number_of_columns; j++)
        {
            index = (i*number_of_columns) + j;
            std::cout << "\t" << values[index];
        }
        std::cout << "\n";
    }
}
