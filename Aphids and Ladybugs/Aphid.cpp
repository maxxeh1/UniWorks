#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"
#include "Manager.h"
using namespace std;

//Default constructor
Aphid::Aphid()
{
        position[0] = 0;
        position[1] = 1;
        //Sets a random number between 60 and 100 for each aphid to have 
        //different lifespans
        this->life = 60 + (rand() % (int)(100 - 60 + 1));
}

//Destructor
Aphid::~Aphid(){}

/**
 * Constructor to just set positions of an aphid
 * @param int position1
 * @param int position2
 */
Aphid::Aphid(int position1, int position2)
{
    position[0] = position1;
    position[1] = position2;
}

/**
 * Second constructor that takes probabilities as well as positions
 * @param int position1
 * @param int position2
 * @param float mv_prob
 * @param float re_prob
 * @param float kill_prob
 * @param float g_kill_prob
 */
Aphid::Aphid(int position1, int position2, float mv_prob, float re_prob, 
        float kill_prob, float g_kill_prob)
{
    position[0] = position1;
    position[1] = position2;
    this->life = 40 + (rand() % (int)(100 - 40 + 1));
    this->move_prob = mv_prob;
    this->reproduce_prob = re_prob;
    this->fight_prob = kill_prob;
    this->group_kill_prob = g_kill_prob;
}

/**
 * Sets aphid's group kill probability
 * @param float prob
 */
void Aphid::set_group_kill_prob(float prob)
{
    this->group_kill_prob = prob;
}

/**
 * Returns aphid's group kill probability
 * @return float group_kill_prob
 */
float Aphid::get_group_kill_prob()
{
    return this->group_kill_prob;
}

/**
 * Visitor pattern function. Decides which visit() function to call 
 * @param AnimalVisitor animal
 */
void Aphid::visit_with(AnimalVisitor &animal)
{
    animal.visit(*this);
}

/**
 * Visitor pattern function. Chosen polymorphically. Checks if an aphid will 
 * be marked for reproduction
 * @param AnimalVisitor animal
 * @return boolean will_reproduce
 */
bool Aphid::visit(Aphid &animal)
{
    if(check_probability(this->reproduce_prob))
    {
        animal.set_reproduce(true);
        //cout << "Aphids reproduce";
        return true;
    }
    else
    {
        //cout << "Aphids do not reproduce";
        return false;
    }
    
}

/**
 * Visitor pattern function. Chosen polymorphically. Checks if an aphid will 
 * fight a ladybug
 * @param AnimalVisitor animal
 * @return boolean will_fight
 */
bool Aphid::visit(Ladybug &animal)
{
    if(check_probability(this->fight_prob))
    {
        //cout << "Kill ladybugs";
        animal.set_dead(true);
        //currentManager.kill(animal);
        return true;
    }
    else
    {
        //cout << "Did not kill ladybug";
        return false;
    }
}

/**
 * Checks if aphid will move, then decides a direction. Then increments 
 * the position of the aphid in chosen direction. Also checks if aphid will go
 * out of bounds, and change the direction. At the end, decrements the aphid's
 * life
 * @param grid_height
 * @param grid_width
 * @return boolean moved
 */
bool Aphid::update(int grid_height, int grid_width)
{
    //Local variables
    bool check = true;
    int store[2];
    //Store a copy of the position, allows reverting if out of bounds
    memcpy(store, this->position, sizeof(store));

    //Check probability of movement
    if(check_probability(this->move_prob))
    {
        //If position is out of bounds, loop again
        while(check)
        {
            //Choose a random direction
            this->direction = rand() % 7;
            //Change position based on chosen direction
            switch(this->direction)
            {
                case(0): //North
                    this->position[0]--;
                    break;
                case(1): //North-east
                    this->position[0]--;
                    this->position[1]++;
                    break;
                case(2): //East
                    this->position[1]++;
                    break;
                case(3): //South-east
                    this->position[0]++;
                    this->position[1]++;
                    break;
                case(4): //South
                    this->position[0]++;
                    break;
                case(5): //South-west
                    this->position[0]++;
                    this->position[1]--;
                    break;
                case(6): //West
                    this->position[1]--;
                    break;
                case(7): //North-west
                    this->position[0]--;
                    this->position[1]--;
                    break;
            }
            //If the changed position is out of bounds
            if(this->position[0] >= grid_height
                    || this->position[0] < 0
                    || this->position[1] >= grid_width
                    || this->position[1] < 0)
            {
                //Revert to original position
                memcpy(this->position, store, sizeof(this->position));
            }
            //Aphid moved
            else
            {
                //Decrement life by a random amount out of 10
                life = life - (rand() % 10 + 1);
                //cout << "Aphid moved to " << this->position[0] << 
                //        this->position[1] << endl;
                //cout << "Aphids life is " << this->life << endl;
                
                //Stop looping
                check = false;
                return true;
            }
        }
    }
    //Aphid did not move
    else
    {
        //cout << "Aphid did not move" << endl;
        return false;
    }
}

