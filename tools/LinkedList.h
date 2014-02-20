// This file contains all the declarations needed to define a linked list

#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>
#include <stdexcept>

//                                              Class Definitions
//========================================================================================================

// This class actually stores data while the next class manages these and organises them into a list. 
template <class Type>
class Node : public Type
{
    public:
        Node<Type>* next;
        Node<Type>* previous;

        Node(double longitude, double latitude) : Type(longitude, latitude) 
            {next = NULL; previous = NULL;};

};

// Here is the actual linked list class
template <class Type>
class LinkedList 
{
    private:

        Node<Type>* front;
        Node<Type>* back;
        Node<Type>* currentNode;

        int list_length;

    public:

        LinkedList();
        ~LinkedList();

        void appendNode(double longitude, double latitude);

        Type* getNextNode();
        int getListLength() {return list_length;};

        void loopThroughFrom(int NodeIndex);
        void fromStart() {currentNode = front;};

        void displayNodes();
        void displayNodesR();

        void emptyList();
};

//                                              Node Class Method Definitions 
//==============================================================================================================

/*
template <class Type>
Node<Type>::Node(Type data)
{
    this->data = data;
    next = NULL;
    previous = NULL;
}
*/

//                                              Linked List Method Definitions
//===============================================================================================================


//              Constructors and Destructors
//===============================================
template<class Type>
LinkedList<Type>::LinkedList()
{
    front = NULL;
    back = NULL;
}

template<class Type>
LinkedList<Type>::~LinkedList()
{
    emptyList();
}

//          Adding Nodes
//========================================

// Adds a node to the end of the list
template<class Type>
void LinkedList<Type>::appendNode(double longitude, double latitude)
{
    Node<Type>* n = new Node<Type>(longitude, latitude);   // Create new node to add

    if(back == NULL)                        // If list is empty
    {
        back = n;
        front = n;                          // Then n is the only node in the list so it's both
                                            // add the front and back.
    }
    else
    {
        back->next = n;                         // Assign the next pointer of the last node in the list to the new one 
        n->previous = back;                     // Set the previous pointer of the new node to the previous in the list 
        back = n;                               // Set the pointer to the last node in the list to the new one
    }

    list_length += 1;                           // Increment the length of the list
}

//              Displaying Nodes
//=====================================================

// Write out all the nodes in the list to screen
template <class Type>
void LinkedList<Type>::displayNodes()
{
    std::cout << "Nodes:\n";

    Node<Type>* temp = front;                       // Create a pointer to a  node pointing at the first node in the list
    while(temp != NULL)                             // While it's not pointing at nothing
    {
        std::cout << "\t" << temp->data << "\n";    // Write out the node's data in a nice list
        temp = temp->next;                          // Set the temporary node to point at the next node
    }
}

// Write out all the nodes in the list to screen in reverse order
template<class Type>
void LinkedList<Type>::displayNodesR()
{
    std::cout << "Nodes in reverse order:\n";

    Node<Type>* temp = back;                            // Create a pointer to a node pointing at the last node in the list
    while(temp != NULL)                                   // While it's not pointing at nothing
    {
        std::cout << "\t" << temp->data << "\n";            // Write out the node's data in a nice list
        temp = temp->previous;                              // Set the temporary node pointing at the previous node
    }
}

//              Node Manipulations
//======================================================

// Get the value store in the next node
template<class Type>
Type* LinkedList<Type>::getNextNode()
{
    // If the currentNode variable isn't assigned or its next pointer doesn't point to anything 
    // meaning currentNode is the last one in the list. Then assign it to the first one again
    if (currentNode == NULL || currentNode->next == NULL)
    {
        currentNode = front;
    }

    Type* data = currentNode;              // Assign the value to a variable

    currentNode = currentNode->next;            // Move the pointer to the next one

    return data;
}

// Loop from the Node given unitl the end, in its current state this 
// function does nothing, look at adding an argument which is the pointer
// to a function, and the function is some operation to be done on each node.
template<class Type>
void LinkedList<Type>::loopThroughFrom(int NodeIndex)
{
    // Check to see that the starting index given is within range
    //if (NodeIndex > list_length)
    //{
    //    throw out_of_range("[LinkedList][ERROR]: Specified index is out of range\n");
    //}

    // Create a temporay node that we will use to walk through the list and set it to the first
    // node in the list
    Node<Type>* temp = front;

    // Walk through to our starting index
    for (int i = 0; i < NodeIndex; i++)
    {
        temp = temp->next;
    }

    // Now we are at the correct node, loop through 
    while (temp != NULL)
    {   
        // Look at adding a function pointer here
        temp = temp->next;
    }

}

//              Removing Nodes
//=========================================================

// Delete all the nodes in the list
template <class Type>
void LinkedList<Type>::emptyList()
{
    Node<Type>* temp = back;        // Create a pointer to a node to traverse the list with and point it at the last node 	

    while(temp != NULL)             // While it's not pointing at nothing
    {
        Node<Type>* temp2 = temp;   // Create another pointer to a node, set it to the same as temp	
        temp = temp->previous;      // Point temp at the previous node
        delete temp2;                   // Delete the node temp2 points at 
    }

    back = NULL;                    // Finally set the front and back pointers to nothing and delete 
    front = NULL;                     // our original temp node

    delete temp;
    list_length = 0;                // Reflect the changes in the list counter
}


#endif
