#include "Matrices.h"

int main()
{
    Matrix mat(16);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (i == j)
                mat.setElement(i,j,1);
            else
                mat.setElement(i,j,0);
        }
    }

    std::cout << "The following is a 4x4 identity matrix\n";
    
    mat.showMatrix();

    return 0;
}
