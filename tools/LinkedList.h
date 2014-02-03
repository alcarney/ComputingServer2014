// This file contains all the declarations needed to define a linked list

#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include <iostream>

// This class actually stores data while the next class manages these and organises them into a list. 
template <class Type>
class Node
{
	public:
		Type data;
		Node<Type>* next;
		Node<Type>* previous;

		Node(Type data);

};

template <class Type>
Node<Type>::Node(Type data)
{
	this->data = data;
	next = NULL;
	previous = NULL;
}

// Here is the actual linked list class
template <class Type>
class LinkedList 
{
	private:

		Node<Type>* front;
		Node<Type>* back;
        Node<Type>* currentNode;

	public:

		LinkedList();
		~LinkedList();

		void appendNode(Type data);

        Type getNextNode();

		void displayNodes();
		void displayNodesR();

		void emptyList();
};

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

// Adds a node to the end of the list
template<class Type>
void LinkedList<Type>::appendNode(Type data)
{
	Node<Type>* n = new Node<Type>(data);	// Create new node to add
	
	if(back == NULL)						// If list is empty
	{
		back = n;
		front = n;							// Then n is the only node in the list so it's both
											// add the front and back. 
	}
	else
	{
		back->next = n;						// Assign the next pointer of the last node in the list to the new one 
		n->previous = back;					// Set the previous pointer of the new node to the previous in the list 
		back = n;							// Set the pointer to the last node in the list to the new one
	}
}

// Write out all the nodes in the list to screen
template <class Type>
void LinkedList<Type>::displayNodes()			
{
	std::cout << "Nodes:\n";

	Node<Type>* temp = front;				// Create a pointer to a  node pointing at the first node in the list
	while(temp != NULL)				// While it's not pointing at nothing
	{
		std::cout << "\t" << temp->data << "\n";	// Write out the node's data in a nice list
		temp = temp->next;			// Set the temporary node to point at the next node
	}
}

// Write out all the nodes in the list to screen in reverse order
template<class Type>
void LinkedList<Type>::displayNodesR()			
{
	std::cout << "Nodes in reverse order:\n";

	Node<Type>* temp = back;				// Create a pointer to a node pointing at the last node in the list
	while(temp != NULL)				// While it's not pointing at nothing
	{
		std::cout << "\t" << temp->data << "\n";	// Write out the node's data in a nice list
		temp = temp->previous;			// Set the temporary node pointing at the previous node
	}
}

// Get the value store in the next node
template<class Type>
Type LinkedList<Type>::getNextNode()
{
    // If the currentNode variable isn't assigned or its next pointer doesn't point to anything 
    // meaning currentNode is the last one in the list. Then assign it to the first one again
    if (currentNode == NULL || currentNode->next == NULL)
    {
        currentNode = front;
    }

    unsigned long data = currentNode->data;     // Assign the value to a variable

    currentNode = currentNode->next;            // Move the pointer to the next one

    return data;
}


// Delete all the nodes in the list
template <class Type>
void LinkedList<Type>::emptyList()
{
	Node<Type>* temp = back;		// Create a pointer to a node to traverse the list with and point it at the last node 	

	while(temp != NULL)				// While it's not pointing at nothing
	{
		Node<Type>* temp2 = temp;	// Create another pointer to a node, set it to the same as temp	
		temp = temp->previous;		// Point temp at the previous node
		delete temp2;				// Delete the node temp2 points at 
	}

	back = NULL;					// Finally set the front and back pointers to nothing and delete 
	front = NULL;					// our original temp node
	
	delete temp;
}


#endif 
