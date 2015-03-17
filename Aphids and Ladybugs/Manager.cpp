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

void Manager::setupGrid(int gridHeight, int gridWidth)
{
    currentGrid.setHeight(gridHeight);
    currentGrid.setWidth(gridWidth);
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
            if((*itA).getLife() <= 0)
            {
                currentAphids.erase(itA);
                cout << "Aphid died" << endl;
                //Call destructor
            }
            else
            {
                (*itA).update(currentGrid.getHeight(), currentGrid.getWidth());
            }
                //this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
            cout << "Aphid moved" << endl;
            //cin.get();
        }
        else
        {
            cout << "Aphid did not move" << endl;
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
                cout << "Ladybug changed direction" << endl;
                //cin.get();
            }
            else
            {
                cout << "Ladybug did not change direction" << endl;
                //cin.get();
            }
            if((*itL).getLife() <= 0)
            {
                currentLadys.erase(itL);
                cout << "Ladybug died" << endl;
                //Call destructor
            }
            else
            {
                (*itL).update();
            }
            //this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
            cout << "Ladybug moved" << endl;
            //cin.get();
        }
        else
        {
            cout << "Ladybug did not move" << endl;
            //cin.get();
        }
    }
    cout << endl << "Turn: " << turn++ << endl;
    this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
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