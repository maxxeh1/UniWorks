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
void Animal::set_dead(bool is_dead)
{
    this->dead = is_dead;
}

/**
 * Returns dead boolean
 * @return boolean dead
 */
bool Animal::get_dead()
{
    return this->dead;
}

/**
 * Sets reproduce boolean
 * @param hasBaby
 */
void Animal::set_reproduce(bool will_reproduce)
{
    this->reproducing = will_reproduce;
}

/**
 * Returns reproduce boolean
 * @return boolean reproduce
 */
bool Animal::get_reproduce()
{
    return this->reproducing;
}

/**
 * Sets height of animal
 * @param int height
 */
void Animal::set_height(int height)
{
    this->position[0] = height;
}

/**
 * Sets width of animal
 * @param int width
 */
void Animal::set_width(int width)
{
        this->position[1] = width;
}

/**
 * Gets height of animal
 * @return int position
 */
int Animal::get_height()
{
        return this->position[0];
}

/**
 * Gets width of animal
 * @return int position
 */
int Animal::get_width()
{
    return this->position[1];
}

/**
 * Returns position of animal
 * Used for debugging at the moment
 * @return pair position
 */
pair<int,int> Animal::get_position()
{
    return make_pair(this->position[0], this->position[1]);
}

/**
 * Set life of animal
 * @param tempLife
 */
void Animal::set_life(int life_span)
{
    this->life = life_span;
}

/**
 * Returns life of animal
 * @return int life
 */
int Animal::get_life()
{
    return this->life;
}

/**
 * Sets move probability of animal
 * @param float prob
 */
void Animal::set_move_prob(float prob)
{
    this->move_prob = prob;
}

/**
 * Returns move probability of animal
 * @return float moveProb
 */
float Animal::get_move_prob()
{
    return this->move_prob;
}

/**
 * Sets fight probability of animal
 * @param float prob
 */
void Animal::set_fight_prob(float prob)
{
    this->fight_prob = prob;
}

/**
 * Returns fight probability of animal
 * @return float fightProb
 */
float Animal::get_fight_prob()
{
    return this->fight_prob;
}

/**
 * Sets reproduce probability of animal
 * @param float prob
 */
void Animal::set_reproduce_prob(float prob)
{
    this->reproduce_prob = prob;
}

/**
 * Returns reproduce probability of animal
 * @return float reproduceProb
 */
float Animal::get_reproduce_prob()
{
    return this->reproduce_prob;
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
bool Animal::check_probability(float prob_to_check)
{
    //Generate a random float
    float chance = ((double) rand() / (RAND_MAX));
    
    //If it's less than the parameter probability, return true
    if(chance <= prob_to_check)
    {
        return true;
    }
    else
    {
        return false;
    }
}