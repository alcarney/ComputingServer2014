#include "Location.h"
#include "Salesman.h"

int main()
{
    Salesman sales;

    sales.addLocation (6, 4);
    sales.addLocation (3, 4);
    sales.addLocation (-4, 4);
    sales.addLocation (65, 4);
    sales.addLocation (5.3, 7);
    sales.addLocation (3, 7);


    sales.showLocations();
    sales.populateMatrix();

}
