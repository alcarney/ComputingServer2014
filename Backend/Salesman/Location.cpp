#include "Location.h"

Location::Location(double longitude, double latitude)
{
    y = longitude;
    x = latitude;
}

Location::~Location()
{

}

double Location::getDistanceTo(Location& loc)
{
    double longitude = loc.y - y;
    double latitude = loc.x - x;
    return sqrt((latitude*latitude) + (longitude*longitude));
}

