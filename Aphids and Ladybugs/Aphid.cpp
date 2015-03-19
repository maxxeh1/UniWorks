#include <string>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"
#include "Manager.h"
using namespace std;

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

Aphid::Aphid(int position1, int position2, float mv_prob, float re_prob, 
        float kil_prob, float g_kill_prob)
{
    position[0] = position1;
    position[1] = position2;
    this->life = 40 + (rand() % (int)(100 - 40 + 1));
    this->move_prob = mv_prob;
    this->reproduce_prob = re_prob;
    this->fight_prob = kil_prob;
    this->group_kill_prob = g_kill_prob;
}

void Aphid::set_group_kill_prob(float prob)
{
    this->group_kill_prob = prob;
}

float Aphid::get_group_kill_prob()
{
    return this->group_kill_prob;
}

void Aphid::visit_with(AnimalVisitor &animal)
{
    animal.visit(*this);
}

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

bool Aphid::update(int grid_height, int grid_width)
{
    bool check = true;
    int store[2];
    memcpy(store, this->position, sizeof(store));

    if(check_probability(this->move_prob))
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
            if(this->position[0] >= grid_height
                    || this->position[0] < 0
                    || this->position[1] >= grid_width
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

