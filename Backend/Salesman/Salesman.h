#ifndef SALESMAN_CPP
#define SALESMAN_CPP

#include "Location.h"
#include "../../tools/LinkedList.h"
#include "../../tools/Matrices.h"

// Look at making the Node class from LinkedList.h be a component of
// this class and LinkedList will have to be modified to expect
// Node to be a component of a given class rather than the class itself.
class Salesman
{
    private:

            LinkedList<Location>* locations;
            LinkedList<Location>* route;

            Matrix* distanceMatrix;

            bool hasMatrix;

    public:

            Salesman();
            ~Salesman();

            void addLocation(double longitude, double latitude);
            void showLocations();

            bool populateMatrix();
            //int getNextStop(int NodeIndex);
            
            void calculateRoute();

};

#endif
