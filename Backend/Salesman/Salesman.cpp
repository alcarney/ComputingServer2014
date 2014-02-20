#include "Salesman.h"


// Constructor, allocates memory for the linked list that will store the locations
Salesman::Salesman()
{
    // Create a linked list to store the locations in
    locations = new LinkedList<Location>;

    // Route linked list, uncomment when needed
    // route = new LinkedList<Location>;

    // Let us know that a new salesman object was created
    std::cout << "[SALESMAN][INFO]: New salesman object created\n";
}

// Destructor de-allocates the memory for the linked list
Salesman::~Salesman()
{
    // Remove the memory allocated for the linked lists
    delete locations;
    //delete route;
}

// Add a new location to the problem
void Salesman::addLocation(double longitude, double latitude)
{
    locations->appendNode(longitude, latitude);
    std::cout << "[SALESMAN][INFO]: New location added at " << longitude << " ," << latitude << std::endl;

}

// Print out a list of all the locations
void Salesman::showLocations()
{
    // Reset the counter on the linked list so we start from the start
    locations->fromStart();

    // Create a dummy pointer to a location for use in the loop below
    Location* loc;
    // Loop through and print locations
    for (int i = 0; i < locations->getListLength(); i++)
    {
        loc = locations->getNextNode();
        std::cout << i << ":\t";
        loc->printCoords();
    }
}

