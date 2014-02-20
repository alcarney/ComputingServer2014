#include "Location.h"
#include "Salesman.h"

int main()
{
    Salesman sales;

    sales.addLocation(644.45, 65454.4);
    sales.addLocation(343.54, 45456.43);
    sales.addLocation(4322.44, 5454.32);
    sales.addLocation (6554.6,  5454.4);

    sales.showLocations();

}
