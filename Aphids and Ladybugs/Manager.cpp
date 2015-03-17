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

/**
 * This function is the core of the program. It loops through vectors of aphids
 * and ladybugs, and updates them in turn based on their probability. If an 
 * aphid and a ladybug meet in one cell, there's a chance for them to fight. 
 * If two of the same kind meet in one cell, there's a chance for them to 
 * reproduce. This functions ties in functionality from all sections of the code
 * to make the program do what it is supposed to do.
 */
void Manager::updateAll()
{
    //Loop through current alive aphids
    for (vector<Aphid>::iterator itA = this->currentAphids.begin();  
                itA != this->currentAphids.end(); ++itA)
    {
        //Check the probability that the selected aphid will move
        if(checkProbability(this->aphidMoveProb))
        {
            //Check if the selected aphid's life is at 0
            if((*itA).getLife() <= 0)
            {
                //Add this aphid to the dead aphids vector for processing later
                deadAphids.push_back(&(*itA));
                cout << "Aphid died" << endl;
            }
            else
            {
                //Update the aphid's location on the grid
                (*itA).update(currentGrid.getHeight(), currentGrid.getWidth());
            }
                //this->currentGrid.drawGrid(this->currentAphids, 
                //this->currentLadys);
            cout << "Aphid moved" << endl;
            //cin.get();
        }
        else
        {
            //Tell user if aphid does not move
            cout << "Aphid did not move" << endl;
            //cin.get();
        }
    }
    //Loop through current alive ladybugs
    for (vector<Ladybug>::iterator itL = this->currentLadys.begin();  
                itL != this->currentLadys.end(); ++itL)
    {
        //Check the probability that the selected ladybug will move
        if(checkProbability(this->ladyMoveProb))
        {
            //Check the probability that the selected ladybug will change 
            //direction before moving
            if(checkProbability(this->ladyDirectionProb))
            {
                //Sets the ladybug's direction until changed again
                (*itL).setDirection(1 + rand()%(NUM_DIRECTIONS - 1));
                cout << "Ladybug changed direction" << endl;
                //cin.get();
            }
            else
            {
                //Tell user that the ladybug did not change direction
                cout << "Ladybug did not change direction" << endl;
                //cin.get();
            }
            //Check if the selected aphid's life is at 0
            if((*itL).getLife() <= 0)
            {
                //Add this aphid to the dead aphids vector for processing later
                deadLadys.push_back(&(*itL));
                cout << "Lady died" << endl;
            }
            else
            {
                //Update the aphid's location on the grid
                (*itL).update();
            }
            //this->currentGrid.drawGrid(this->currentAphids, 
            //this->currentLadys);
            cout << "Ladybug moved" << endl;
            //cin.get();
        }
        else
        {
            //Tell user if ladybug does not move
            cout << "Ladybug did not move" << endl;
            //cin.get();
        }
    }

    cout << deadAphids.size();
    //Loop through vector of marked for death aphids
    for (vector<Aphid*>::iterator itA = this->deadAphids.begin();  
            itA != this->deadAphids.end(); ++itA)
    {
        //Loop through vector of alive aphids
        for (vector<Aphid>::iterator itAlive = this->currentAphids.begin();
                itAlive != this->currentAphids.end(); ++itAlive)
        {
            //If an aphid exists in deadAphids that exists in currentAphids, 
            //remove the aphid from currentAphids
            if(&(*itAlive) == *itA)
            {
                itAlive = currentAphids.erase(itAlive);
                break;
            }
        }
    }
    //Clear the deadAphids vector for the next turn
    this->deadAphids.clear();
    
    cout << deadLadys.size();
    //Loop through vector of marked for death ladybugs
    for (vector<Ladybug*>::iterator itL = this->deadLadys.begin();  
            itL != this->deadLadys.end(); ++itL)
    {
        //Loop through vector of alive ladybugs
        for (vector<Ladybug>::iterator itAlive = this->currentLadys.begin();
                itAlive != this->currentLadys.end(); ++itAlive)
        {
            //If an ladybug exists in deadLadys that exists in currentLadys, 
            //remove the ladybug from currentLadys
            if(&(*itAlive) == *itL)
            {
                itAlive = currentLadys.erase(itAlive);
                break;
            }
        }
    }
    //Clear the deadLadys vector for the next turn
    this->deadLadys.clear();
    //Print out remaining ladybugs and aphids
    cout << "Aphids: " << currentAphids.size() << endl << "Ladybugs: " 
            << currentLadys.size();
    //Print out turn number
    cout << endl << "Turn: " << turn++ << endl;
    //Draw grid with all updated data
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