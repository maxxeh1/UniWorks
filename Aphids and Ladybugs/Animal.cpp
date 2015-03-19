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
 * Sets dead boolean
 * @param isDead
 */
void Animal::setDead(bool isDead)
{
    this->dead = isDead;
}

/**
 * Returns dead boolean
 * @return boolean dead
 */
bool Animal::getDead()
{
    return this->dead;
}

/**
 * Sets reproduce boolean
 * @param hasBaby
 */
void Animal::setReproduce(bool hasBaby)
{
    this->reproducing = hasBaby;
}

/**
 * Returns reproduce boolean
 * @return boolean reproduce
 */
bool Animal::getReproduce()
{
    return this->reproducing;
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

/**
 * Returns position of animal
 * Used for debugging at the moment
 * @return pair position
 */
pair<int,int> Animal::getPosition()
{
    return make_pair(this->position[0], this->position[1]);
}

/**
 * Set life of animal
 * @param tempLife
 */
void Animal::setLife(int tempLife)
{
    this->life = tempLife;
}

/**
 * Returns life of animal
 * @return int life
 */
int Animal::getLife()
{
    return this->life;
}

/**
 * Sets move probability of animal
 * @param float prob
 */
void Animal::setMoveProb(float prob)
{
    this->moveProb = prob;
}

/**
 * Returns move probability of animal
 * @return float moveProb
 */
float Animal::getMoveProb()
{
    return this->moveProb;
}

/**
 * Sets fight probability of animal
 * @param float prob
 */
void Animal::setFightProb(float prob)
{
    this->fightProb = prob;
}

/**
 * Returns fight probability of animal
 * @return float fightProb
 */
float Animal::getFightProb()
{
    return this->fightProb;
}

/**
 * Sets reproduce probability of animal
 * @param float prob
 */
void Animal::setReproduceProb(float prob)
{
    this->reproduceProb = prob;
}

/**
 * Returns reproduce probability of animal
 * @return float reproduceProb
 */
float Animal::getReproduceProb()
{
    return this->reproduceProb;
}

/**
 * Updates an animal's positions based on grid size
 * Not used, just over-ridden by children
 * @param int grid_height
 * @param int grid_width
 * @return bool hasMoved
 */
bool Animal::update(int grid_height, int grid_width)
{
    
}

/**
 * Checks the probability of any probability variable against a randomly 
 * generated float, and tells the program whether to go ahead with functionality
 * eg. Moving, Killing, Reproducing etc.
 * @param float probToCheck
 * @return bool willDo
 */
bool Animal::checkProbability(float probToCheck)
{
    //Generate a random float
    float chance = ((double) rand() / (RAND_MAX));
    
    //If it's less than the parameter probability, return true
    if(chance <= probToCheck)
    {
        return true;
    }
    else
    {
        return false;
    }
}