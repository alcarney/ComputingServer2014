#include "Location.h"
#include "Salesman.h"

int main()
{
    Salesman sales;

    std::cout << "\n";

    sales.addLocation (6, 4);
    sales.addLocation (3, 4);
    sales.addLocation (-4, 4);
    sales.addLocation (65, 4);
    sales.addLocation (5.3, 7);
    sales.addLocation (3, 7);

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
