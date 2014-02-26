#include "Location.h"
#include "Salesman.h"

int main()
{
    Salesman sales;

    std::cout << "\n";

    sales.addLocation(0,0);
    sales.addLocation (2, 3);
    sales.addLocation (6, 1);
    sales.addLocation (-1, 1);
    sales.addLocation (-3, 3);
    sales.addLocation (4, -3);
    sales.addLocation (5, 6);
    sales.addLocation (1, -4);
    sales.addLocation (7, -2);
    sales.addLocation (-4, -3);
    sales.addLocation (-3, -8);

    std::cout << "\n";

    sales.showLocations();
    sales.populateMatrix();
    std::cout << "\n";
    sales.calculateRoute();
    std::cout << "\n";
    sales.showRoute();

/*
    Location loc(7,6);
    loc.printCoords();
    Node<Location> node = loc;
    node.printCoords();
*/
}
