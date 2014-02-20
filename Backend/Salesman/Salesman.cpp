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
    std::cout << "\t[SALESMAN][INFO]: New location added at " << longitude << " ," << latitude << std::endl;

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

// Return the index of the node with the shortest distance to
// the node at the given index
int Salesman::getNextStop(int NodeIndex)
{
    // Start from the start of the list
    locations->fromStart();

    // Get the Node we are calculating from
    Location* loc = locations->getNode(NodeIndex);
    Location* temp;

    // Variable to store the closest node in, initialised to -1 so we now 
    // when it's unassigned
    int closestNode = -1;
    double closestDistance = -1;    // -1 for the same reason
    double distance;

    // Then loop through the nodes from the next index
    for (int i = 1; i < locations->getListLength(); i++)
    {
        // Dont calculate distance with yourself
        if (NodeIndex == i)
            continue;                   // Skips to next loop iteration

        temp = locations->getNextNode();
        distance = loc.getDistanceTo(temp);

        if (distance < closestDistance || closestDistance == -1)
        {
            closestDistance = distance;
            closestNode = i;
        }
    }

    return closestNode;
}



