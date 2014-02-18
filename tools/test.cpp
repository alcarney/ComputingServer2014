#include "LinkedList.h"

int main()
{
    LinkedList<int>* list = new LinkedList<int>;

    for (int i = 0; i < 11; i++)
    {
        list->appendNode(i);
    }

    list->loopThroughFrom(4);

}
