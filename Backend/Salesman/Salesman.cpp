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

