#include <iostream>
#include <stdlib.h>
#include "Animal.h"
using namespace std;


Ladybug::Ladybug()
{
    position[0] = 0;
    position[1] = 1;
    this->life = 80 + (rand() % (int)(110 - 80 + 1));
    direction = North;
}

Ladybug::~Ladybug(){}

Ladybug::Ladybug(int position1, int position2)
{
    position[0] = position1;
    position[1] = position2;
}

Ladybug::Ladybug(int position1, int position2, float mvProb, float reProb, 
        float killProb, float dChangeProb)
{
        position[0] = position1;
        position[1] = position2;
        direction = North;
        this->life = 50 + (rand() % (int)(110 - 50 + 1));
        this->moveProb = mvProb;
        this->reproduceProb = reProb;
        this->fightProb = killProb;
        this->dirChangeProb = dChangeProb;
}

void Ladybug::setDirection(int nSteps)
{
    this->direction = static_cast<LadyDirection>(
                     (this->direction + nSteps) % NUM_DIRECTIONS);
}

void Ladybug::setDirChangeProb(float prob)
{
    this->dirChangeProb = prob;
}

float Ladybug::getDirChangeProb()
{
    return this->dirChangeProb;
}

void Ladybug::visitWith(AnimalVisitor &animal)
{
    animal.visit(*this);
}

bool Ladybug::visit(Aphid &animal)
{
    if(checkProbability(this->fightProb))
    {
        animal.setDead(true);
        //cout << "Kill aphid";
        return true;
    }
    else
    {
        //cout << "Did not kill aphid";
        return false;
    }
}

bool Ladybug::visit(Ladybug &animal)
{
    if(checkProbability(this->reproduceProb))
    {
        animal.setReproduce(true);
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
 * This function updates each individual ladybug according to their direction
 */
bool Ladybug::update(int grid_height, int grid_width)
{
    bool check = true;
    //Loop until check is false
    if(checkProbability(this->moveProb))
    {
        if(checkProbability(this->dirChangeProb))
        {
            setDirection(1 + rand()%(NUM_DIRECTIONS - 1));
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
        life = life - (rand() % 10 + 1);
        //cout << "Ladybug moved to " << position[0] << position[1] << endl;
        //cout << "Ladybugs life is " << life << endl;
        return true;
    }
    else
    {
        //cout << "Ladybug did not move" << endl;
        return false;
    }
}

