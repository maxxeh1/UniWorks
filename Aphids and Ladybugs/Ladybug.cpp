#include <iostream>
#include <stdlib.h>
#include "Animal.h"
using namespace std;

//Default constructor
Ladybug::Ladybug()
{
    position[0] = 0;
    position[1] = 1;
    this->life = 80 + (rand() % (int)(110 - 80 + 1));
    direction = North;
}

//Destructor
Ladybug::~Ladybug(){}

/**
 * Constructor to just set positions of an ladybug
 * @param int position1
 * @param int position2
 */
Ladybug::Ladybug(int position1, int position2)
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
 * @param float d_change_prob
 */
Ladybug::Ladybug(int position1, int position2, float mv_prob, float re_prob, 
        float kill_prob, float d_change_prob)
{
        position[0] = position1;
        position[1] = position2;
        direction = North;
        this->life = 50 + (rand() % (int)(110 - 50 + 1));
        this->move_prob = mv_prob;
        this->reproduce_prob = re_prob;
        this->fight_prob = kill_prob;
        this->dir_change_prob = d_change_prob;
}

/**
 * Sets the preferred direction for the ladybug
 * @param int nSteps
 */
void Ladybug::set_direction(int n_steps)
{
    this->direction = static_cast<LadyDirection>(
                     (this->direction + n_steps) % NUM_DIRECTIONS);
}

/**
 * Sets the probability to change preferred direction
 * @param float prob
 */
void Ladybug::set_dir_change_prob(float prob)
{
    this->dir_change_prob = prob;
}

/**
 * Returns the probability to change preferred direction
 * @return float dir_change_prob
 */
float Ladybug::get_dir_change_prob()
{
    return this->dir_change_prob;
}

/**
 * Visitor pattern function. Decides which visit() function to call 
 * @param AnimalVisitor animal
 */
void Ladybug::visit_with(AnimalVisitor &animal)
{
    animal.visit(*this);
}

/**
 * Visitor pattern function. Chosen polymorphically. Checks if a ladybug
 * will fight an aphid
 * @param AnimalVisitor animal
 * @return boolean will_fight
 */
bool Ladybug::visit(Aphid &animal)
{
    if(check_probability(this->fight_prob))
    {
        animal.set_dead(true);
        //cout << "Kill aphid";
        return true;
    }
    else
    {
        //cout << "Did not kill aphid";
        return false;
    }
}

/**
 * Visitor pattern function. Chosen polymorphically. Checks if a ladybug
 * will be marked for reproduction
 * @param AnimalVisitor animal
 * @return boolean will_reproduce
 */
bool Ladybug::visit(Ladybug &animal)
{
    if(check_probability(this->reproduce_prob))
    {
        animal.set_reproduce(true);
        //cout << "Ladybugs reproduce";
        return true;
    }
    else
    {
        //cout << "Ladybugs do not reproduce";
        return false;
    }
}

/**
 * Updates a ladybug based on their preferred direction. First checks if the 
 * ladybug will move. Then checks if the ladybug will change their preferred
 * direction. Then chooses a new direction, NOT the original one. Performs 
 * constant checks for if the ladybug will go out bounds before incrementing.
 * Then reduces the ladybug's life.
 * @param int grid_height
 * @param int grid_width
 * @return boolean moved
 */
bool Ladybug::update(int grid_height, int grid_width)
{
    bool check = true;
    //Loop until check is false
    if(check_probability(this->move_prob))
    {
        if(check_probability(this->dir_change_prob))
        {
            set_direction(1 + rand()%(NUM_DIRECTIONS - 1));
            //cout << "Ladybug changed direction to " << direction << endl;
        }
        else
        {
            //cout << "Ladybug did not change direction" << endl;
        }
        while(check)
        {
            //Check what direction is set
            switch(this->direction)
            {
                //If direction is north
                case(North):
                    //If ladybug is in the top-most row, change direction to 
                    //south and repeat
                    if(position[0] == 0)
                    {
                        this->direction = South;
                        break;
                    }
                    //Go north by one
                    this->position[0]--;

                    //If ladybug is in the east-most column, change subdirection to
                    //west
                    if(this->position[1] == (grid_width - 1))
                    {
                        this->subdirection = 2;
                    }
                    //If ladybug is in the west-most column, change subdirection to
                    //east
                    else if(this->position[1] == 0)
                    {
                        this->subdirection = 1;
                    }
                    //Choose a random subdirection
                    else
                    {
                        this->subdirection = rand() % 3;
                    }

                    /**
                     * Go north-west, north or north-east based on subdirection
                     * Set check to false to break out of loop when movement is 
                     * concluded
                     */
                    switch(this->subdirection)
                    {
                        case(0): //North
                            check = false;
                            break;
                        case(1): //North-east
                            this->position[1]++;
                            check = false;
                            break;
                        case(2): //North-west
                            this->position[1]--;
                            check = false;
                            break;
                    }
                    break;

                //If direction is east
                case(East):
                    //If ladybug is at east-most column, change direction and 
                    //restart
                    if(position[1] == (grid_width - 1))
                    {
                        this->direction = West;
                        break;
                    }
                    //Move ladybug to the east
                    this->position[1]++;

                    //If ladybug is in the south-most row, change subdirection to
                    //north
                    if(this->position[0] == (grid_height - 1))
                    {
                        this->subdirection = 1;
                    }
                    //If ladybug is in the north-most row, change subdirection to 
                    //south
                    else if(this->position[0] == 0)
                    {
                        this->subdirection = 2;
                    }
                    //Choose a random subdirection
                    else
                    {
                        this->subdirection = rand() % 3;
                    }

                    /**
                     * Go east-north, east or east-south based on subdirection
                     * Set check to false to break out of loop when movement is 
                     * concluded
                     */
                    switch(this->subdirection)
                    {
                        case(0): //East
                            check = false;
                            break;
                        case(1): //East-north
                            this->position[0]--;
                            check = false;
                            break;
                        case(2): //East-south
                            this->position[0]++;
                            check = false;
                            break;
                    }
                    break;

                //If direction is south
                case(South):
                    //If ladybug is at south-most row, change direction and 
                    //restart
                    if(position[0] == (grid_height - 1))
                    {
                        this->direction = North;
                        break;
                    }
                    //Move ladybug to the south
                    this->position[0]++;

                    //If ladybug is in the east-most column, change subdirection to
                    //west
                    if(this->position[1] == (grid_width - 1))
                    {
                        this->subdirection = 2;
                    }
                    //If ladybug is in the west-most column, change subdirection to
                    //east
                    else if(this->position[1] == 0)
                    {
                        this->subdirection = 1;
                    }
                    //Choose a random subdirection
                    else
                    {
                        this->subdirection = rand() % 3;
                    }

                    /**
                     * Go south-east, south or south-west based on subdirection
                     * Set check to false to break out of loop when movement is 
                     * concluded
                     */
                    switch(this->subdirection)
                    {
                        case(0): //South
                            check = false;
                            break;
                        case(1): //South-east
                            this->position[1]++;
                            check = false;
                            break;
                        case(2): //South-west
                            this->position[1]--;
                            check = false;
                            break;
                    }
                    break;
                //If direction is west
                case(West):
                    //If ladybug is at west-most row, change direction and 
                    //restart
                    if(position[1] == 0)
                    {
                        this->direction = East;
                        break;
                    }
                    //Move ladybug to the west
                    this->position[1]--;

                    //If ladybug is in the south-most row, change subdirection to
                    //north
                    if(this->position[0] == (grid_height - 1))
                    {
                        this->subdirection = 1;
                    }
                    //If ladybug is in the north-most row, change subdirection to
                    //south
                    else if(this->position[0] == 0)
                    {
                        this->subdirection = 2;
                    }
                    //Choose a random subdirection
                    else
                    {
                        this->subdirection = rand() % 3;
                    }

                    /**
                     * Go west-north, west or west-south based on subdirection
                     * Set check to false to break out of loop when movement is 
                     * concluded
                     */
                    switch(this->subdirection)
                    {
                        case(0): //West
                            check = false;
                            break;
                        case(1): //West-north
                            this->position[0]--;
                            check = false;
                            break;
                        case(2): //West-south
                            this->position[0]++;
                            check = false;
                            break;
                    }
                    break;
            }
        }
        //Decrement ladybug's life by a random number out of 10
        life = life - (rand() % 10 + 1);
        //cout << "Ladybug moved to " << position[0] << position[1] << endl;
        //cout << "Ladybugs life is " << life << endl;
        return true;
    }
    //Did not move
    else
    {
        //cout << "Ladybug did not move" << endl;
        return false;
    }
}

