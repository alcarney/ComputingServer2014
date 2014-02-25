#include "Location.h"
#include "Salesman.h"

int main()
{
    Salesman sales;

    sales.addLocation (6, 4);
    sales.addLocation (3, 4);


    sales.showLocations();
    sales.populateMatrix();

}
