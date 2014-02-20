#include "LinkedList.h"

class Dummy
{
    private:
            double x;
            double y;
    public: 
        Dummy(double longitude, double latitude);

        void getInfo();
};

Dummy::Dummy(double longitude, double latitude)
{
    x = latitude;
    y = longitude;
}

void Dummy::getInfo()
{
    std::cout << "x: " << x << " y: " << y << std::endl;
}

int main()
{
    LinkedList<Dummy>* dum = new LinkedList<Dummy>;

    dum->appendNode(14.2,34.5);
    dum->appendNode(90.4,-23.4);
    dum->appendNode(256.7, 7654.4);

    Dummy* node;

    for (int i = 0; i < 3; i++)
    {
        node = dum->getNextNode();
        node->getInfo();
    }

    return 0;
}
