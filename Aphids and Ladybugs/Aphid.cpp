#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"
using namespace std;


//Global variables


//Constructor


	Aphid::Aphid()
	{
		position[0] = 0;
		position[1] = 1;
                this->life = 70 + (rand() % (int)(100 - 70 + 1));
	}
        
        Aphid::~Aphid(){}
        
	Aphid::Aphid(int position1, int position2)
	{
		position[0] = position1;
		position[1] = position2;
                //this->life = 70 + (rand() % (int)(100 - 70 + 1));
                this->life = 10;
	}

        void Aphid::update(int gridHeight, int gridWidth)
        {
            bool check = true;
            int store[2];
            memcpy(store, this->position, sizeof(store));
            
            
            while(check)
            {
                this->direction = rand() % 7;
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
                if(this->position[0] >= gridHeight 
                        || this->position[0] <= 0
                        || this->position[1] >= gridWidth
                        || this->position[1] <= 0)
                {
                    memcpy(this->position, store, sizeof(this->position));
                }
                else
                {
                    life = life - (rand() % 10 + 1);
                    check = false;
                }
            }
        }

