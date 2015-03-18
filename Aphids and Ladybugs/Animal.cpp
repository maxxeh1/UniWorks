#include <string>
#include <stdlib.h>
#include "Animal.h"
using namespace std;

/**
 * Default constructor
 */
Animal::Animal()
{
        position[0] = 0;
        position[1] = 1;
}

/**
 * Sets height of animal
 * @param int height
 */
void Animal::setHeight(int height)
{
        this->position[0] = height;
}

/**
 * Sets width of animal
 * @param int width
 */
void Animal::setWidth(int width)
{
        this->position[1] = width;
}

/**
 * Gets height of animal
 * @return int position
 */
int Animal::getHeight()
{
        return this->position[0];
}

/**
 * Gets width of animal
 * @return int position
 */
int Animal::getWidth()
{
    return this->position[1];
}

pair<int,int> Animal::getPosition()
{
    return make_pair(this->position[0], this->position[1]);
}

void Animal::setLife(int tempLife)
{
    this->life = tempLife;
}

int Animal::getLife()
{
    return this->life;
}

void Animal::setMoveProb(float prob)
{
    this->moveProb = prob;
}

float Animal::getMoveProb()
{
    return this->moveProb;
}

bool Animal::update(int grid_height, int grid_width)
{
    
}

bool Animal::checkProbability(float probToCheck)
{
    float chance = ((double) rand() / (RAND_MAX));
    if(chance <= probToCheck)
    {
        return true;
    }
    else
    {
        return false;
    }
}