#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Manager.h"
#include "Grid.h"
using namespace std;

Manager::Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys, 
        float tempAphidMove, float tempLadyMove, float tempLadyDir)
{
    currentAphids = newAphids;
    currentLadys = newLadys;
    aphidMoveProb = tempAphidMove;
    ladyMoveProb = tempLadyMove;
    ladyDirectionProb = tempLadyDir;
}

void Manager::setVectors(vector<Aphid> newAphids, vector<Ladybug> newLadys)
{
    currentAphids = newAphids;
    currentLadys = newLadys;
    /*for (vector<Aphid>::iterator itA = this->currentAphids.begin();
            itA != this->currentAphids.end(); ++itA)
    {
        allAnimals.push_back(itA);
    }
    for (vector<Ladybug>::iterator itL = this->currentLadys.begin();
            itL != this->currentLadys.end(); ++itL)
    {
        allAnimals.push_back(itL);
    }*/
}

void Manager::updateAll()
{
    for (vector<Aphid>::iterator itA = this->currentAphids.begin();  
                itA != this->currentAphids.end(); ++itA)
    {
        if(checkProbability(this->aphidMoveProb))
        {
            (*itA).update();
            this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
            cout << "Aphid moved";
            //cin.get();
        }
        else
        {
            cout << "Aphid did not move";
            //cin.get();
        }
    }
    for (vector<Ladybug>::iterator itL = this->currentLadys.begin();  
                itL != this->currentLadys.end(); ++itL)
    {
        
        if(checkProbability(this->ladyMoveProb))
        {
            if(checkProbability(this->ladyDirectionProb))
            {
                (*itL).setDirection(1 + rand()%(NUM_DIRECTIONS - 1));
                cout << "Ladybug changed direction";
                //cin.get();
            }
            else
            {
                cout << "Ladybug did not change direction";
                //cin.get();
            }
            (*itL).update();
            this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
            cout << "Ladybug moved";
            //cin.get();
        }
        else
        {
            cout << "Ladybug did not move";
            //cin.get();
        }
    }
}

void Manager::fight(Animal movedAnimal, Animal currentAnimal)
{
    
}

bool Manager::checkProbability(float probToCheck)
{
    float chance = ((double) rand() / (RAND_MAX));
    if(chance <= probToCheck)
    {
        return true;
    }
    else
    {
        return false;
    }
}