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

void Ladybug::setDirection(LadyDirection temp_direction)
{
    this->direction = temp_direction;
}

void Ladybug::update()
{
    switch(this->direction)
    {
        case(North):
            this->position[0]--;
            this->subdirection = rand() % 3;
            switch(this->subdirection)
            {
                case(0): //North
                    break;
                case(1): //North-east
                    this->position[1]++;
                    break;
                case(2): //North-west
                    this->position[1]--;
                    break;
            }
            break;
        case(East):
            this->position[1]++;
            subdirection = rand() % 3;
            switch(this->subdirection)
            {
                case(0): //East
                    break;
                case(1): //East-north
                    this->position[0]--;
                    break;
                case(2): //East-south
                    this->position[0]++;
                    break;
            }
            break;
        case(South):
            this->position[0]++;
            subdirection = rand() % 3;
            switch(this->subdirection)
            {
                case(0): //South
                    break;
                case(1): //South-east
                    this->position[1]++;
                    break;
                case(2): //South-west
                    this->position[1]--;
                    break;
            }
            break;
        case(West):
            this->position[1]--;
            subdirection = rand() % 3;
            switch(this->subdirection)
            {
                case(0): //West
                    break;
                case(1): //West-north
                    this->position[0]--;
                    break;
                case(2): //West-south
                    this->position[0]++;
                    break;
            }
            break;
    }
}


