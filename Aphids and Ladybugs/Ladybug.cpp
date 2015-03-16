#include <stdlib.h>
#include "Animal.h"
using namespace std;


Ladybug::Ladybug()
        {
            position[0] = 0;
            position[1] = 1;
            direction = North;
        }

Ladybug::Ladybug(int position1, int position2)
{
        position[0] = position1;
        position[1] = position2;
        direction = North;
}

void Ladybug::setDirection(int nSteps)
{
    this->direction = static_cast<LadyDirection>(
                     (this->direction + nSteps) % NUM_DIRECTIONS);
}

/**
 * This function updates each individual ladybug according to their direction
 */
void Ladybug::update()
{
    bool check = true;
    //Loop until check is false
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
                if(this->position[1] == 9)
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
                if(position[1] == 9)
                {
                    this->direction = West;
                    break;
                }
                //Move ladybug to the east
                this->position[1]++;
                
                //If ladybug is in the south-most row, change subdirection to
                //north
                if(this->position[0] == 9)
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
                if(position[0] == 9)
                {
                    this->direction = North;
                    break;
                }
                //Move ladybug to the south
                this->position[0]++;
                
                //If ladybug is in the east-most column, change subdirection to
                //west
                if(this->position[1] == 9)
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
                if(this->position[1] == 0)
                {
                    this->direction == East;
                    break;
                }
                //Move ladybug to the west
                this->position[1]--;
                
                //If ladybug is in the south-most row, change subdirection to
                //north
                if(this->position[0] == 9)
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
}

