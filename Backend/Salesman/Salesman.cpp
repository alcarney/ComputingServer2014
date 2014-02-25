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
    std::cout << "\t[SALESMAN][INFO]: New location added at " << longitude << ", " << latitude << std::endl;

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

// Go through each entry in the linked list and compile a matrix that describes 
// the graph of the whole problem
bool Salesman::populateMatrix()
{
    if (hasMatrix)
    {
        std::cout << "Error this salesman already has a matrix defining the problem, aborting...\n";
        return false;
    }

    // Store the number of locations in a variable since we will need it many times
    int num_locations = locations->getListLength();

    // Create a new matrix to hold the distances
    distanceMatrix = new Matrix(num_locations*num_locations);

    std::cout << "Compiling matrix...\n";

    // Start from the first location in the list
    locations->fromStart();
    
    // Create pointers to nodes to hold our elements in while we process them
    Location* loc;
    Location* loc2;
    double distance;

    // For each element in the list for each current element in the list
    for (int i = 0; i < num_locations; i++)
    {
        // Get the next location in the list
        loc = locations->getNextNode();

        for (int j = 0; j < num_locations; j++)
        {

            // Get the next node
            loc2 = locations->getNodeAt(j);

            // Get the distance and add it to the matrix
            distance = loc->getDistanceTo(*loc2);
            distanceMatrix->setElement(i,j,distance);
        }

    }

    distanceMatrix->showMatrix();
}

// Return the index of the node with the shortest distance to
// the node at the given index
/*int Salesman::getNextStop(int NodeIndex)
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
}*/



