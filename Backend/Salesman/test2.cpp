#include "Location.h"

int main ()
{
    Location loc(-1,1);
    Location loc2(5,6);

    std::cout << loc.getDistanceTo(loc2) << std::endl;

}
