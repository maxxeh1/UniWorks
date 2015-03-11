#include <string>
#include "Animal.h"
using namespace std;



//int position[2];


Animal::Animal()
{
        position[0] = 0;
        position[1] = 1;
}
void Animal::setHeight(int height)
{
        this->position[0] = height;
}

void Animal::setWidth(int width)
{
        this->position[1] = width;
}

int Animal::getHeight()
{
        return this->position[0];
}

int Animal::getWidth()
{
        return this->position[1];
}

