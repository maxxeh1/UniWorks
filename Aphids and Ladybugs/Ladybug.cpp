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

void Ladybug::update()
{
    bool check = true;
    while(check)
    {
        switch(this->direction)
        {
            case(North):
                if(position[0] == 0)
                {
                    this->direction = South;
                    break;
                }
                this->position[0]--;
                if(this->position[1] == 9)
                {
                    this->subdirection = 2;
                }
                else if(this->position[1] == 0)
                {
                    this->subdirection = 1;
                }
                else
                {
                    this->subdirection = rand() % 3;
                }
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
            case(East):
                if(position[1] == 9)
                {
                    this->direction = West;
                    break;
                }
                this->position[1]++;
                
                if(this->position[0] == 9)
                {
                    this->subdirection = 1;
                }
                else if(this->position[0] == 0)
                {
                    this->subdirection = 2;
                }
                else
                {
                    this->subdirection = rand() % 3;
                }
                subdirection = rand() % 3;
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
            case(South):
                if(position[0] == 9)
                {
                    this->direction = North;
                    break;
                }
                this->position[0]++;
                
                if(this->position[1] == 9)
                {
                    this->subdirection = 2;
                }
                else if(this->position[1] == 0)
                {
                    this->subdirection = 1;
                }
                else
                {
                    this->subdirection = rand() % 3;
                }
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
            case(West):
                if(this->position[1] == 0)
                {
                    this->direction == East;
                    break;
                }
                this->position[1]--;
                
                if(this->position[0] == 9)
                {
                    this->subdirection = 1;
                }
                else if(this->position[0] == 0)
                {
                    this->subdirection = 2;
                }
                else
                {
                    this->subdirection = rand() % 3;
                }
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

