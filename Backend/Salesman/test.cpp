#include "Location.h"

int main()
{
    Location loc1(-2,1);
    Location loc2(1,5);

    std::cout << loc1.getDistanceTo(loc2) << std::endl;
}
