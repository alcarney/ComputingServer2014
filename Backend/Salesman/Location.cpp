#include "Location.h"

Location::Location(double longitude, double latitude)
{
    y = longitude;
    x = latitude;
}

Location::~Location()
{
    // Nothing to see here 
}

// Gets the distance to another location
// Another instance of the Location class is passed in by reference
double Location::getDistanceTo(Location& loc)
{
    // Get the difference in the x, y co ordinates
    double longitude = loc.y - y;
    double latitude = loc.x - x;

    // Calculate and return the magnitude
    return sqrt((latitude*latitude) + (longitude*longitude));
}

