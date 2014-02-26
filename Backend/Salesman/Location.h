// Declares the information required to define a location
#ifndef LOCATION_CPP
#define LOCATION_CPP

#include <iostream>
#include <cmath>

#include "../../tools/LinkedList.h"

class Location
{

    public:
            bool isStart;
            int locationID;
            double y;
            double x;

            Location(double longitude=0, double latitude=0);
            ~Location();

            // Functions to set/unset and determine if the current location insance is the starting location
            void setStart() {isStart = true;};
            bool startLocation() {return isStart;};
            void notStart() {isStart = false;};

            // Show the coords
            void printCoords() {std::cout << "x: "<< x << "\ty: " << y << std::endl;};

            // Get distance to provided location
            double getDistanceTo(Location& loc);

            // Let's C++ convert this to a Node<Location> for use in a linked list
            operator Node<Location> () const {return Node<Location>(y,x);};

};

#endif
