#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"
#include "Manager.h"
using namespace std;


//Global variables


//Constructor

Aphid::Aphid()
{
        position[0] = 0;
        position[1] = 1;
        this->life = 60 + (rand() % (int)(100 - 60 + 1));
}

Aphid::~Aphid(){}

Aphid::Aphid(int position1, int position2)
{
    position[0] = position1;
    position[1] = position2;
}

Aphid::Aphid(int position1, int position2, float mvProb, float reProb, 
        float killProb, float gKillProb)
{
    position[0] = position1;
    position[1] = position2;
    this->life = 40 + (rand() % (int)(100 - 40 + 1));
    this->moveProb = mvProb;
    this->reproduceProb = reProb;
    this->fightProb = killProb;
    this->groupKillProb = gKillProb;
}

void Aphid::setGroupKillProb(float prob)
{
    this->groupKillProb = prob;
}

float Aphid::getGroupKillProb()
{
    return this->groupKillProb;
}

void Aphid::visitWith(AnimalInteractor &animal)
{
    animal.visit(*this);
}

bool Aphid::visit(Aphid &animal)
{
    if(checkProbability(this->reproduceProb))
    {
        animal.setReproduce(true);
        //cout << "Aphids reproduce";
        return true;
    }
    else
    {
        //cout << "Aphids do not reproduce";
        return false;
    }
    
}

bool Aphid::visit(Ladybug &animal)
{
    if(checkProbability(this->fightProb))
    {
        //cout << "Kill ladybugs";
        animal.setDead(true);
        //currentManager.kill(animal);
        return true;
    }
    else
    {
        //cout << "Did not kill ladybug";
        return false;
    }
}

bool Aphid::update(int gridHeight, int gridWidth)
{
    bool check = true;
    int store[2];
    memcpy(store, this->position, sizeof(store));

    if(checkProbability(this->moveProb))
    {
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
                    || this->position[0] < 0
                    || this->position[1] >= gridWidth
                    || this->position[1] < 0)
            {
                memcpy(this->position, store, sizeof(this->position));
            }
            else
            {
                life = life - (rand() % 10 + 1);
                //cout << "Aphid moved to " << this->position[0] << 
                //        this->position[1] << endl;
                //cout << "Aphids life is " << this->life << endl;
                check = false;
                return true;
            }
        }
    }
    else
    {
        //cout << "Aphid did not move" << endl;
        return false;
    }
}

