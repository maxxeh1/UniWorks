#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Manager.h"
#include "Grid.h"
using namespace std;

Manager::Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys)
{
    currentAphids = newAphids;
    currentLadys = newLadys;
}

void Manager::setupGrid(int gridHeight, int gridWidth)
{
    currentGrid.setHeight(gridHeight);
    currentGrid.setWidth(gridWidth);
    currentGrid.drawGrid(currentAphids, currentLadys);
}

void Manager::setVectors()
{
    //Loop through vector of aphids
    for (vector<Aphid>::iterator itA = this->currentAphids.begin();
            itA != this->currentAphids.end(); ++itA)
    {
        //Push aphids to vector of aphids and ladybugs
        allAnimals.push_back(&(*itA));
    }
    //Loop through vector of ladybugs
    for (vector<Ladybug>::iterator itL = this->currentLadys.begin();
            itL != this->currentLadys.end(); ++itL)
    {
        //Push ladybugs to vector of aphids and ladybugs
        allAnimals.push_back(&(*itL));
    }
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
    //Loop through vector of animals
    for(vector<Animal*>::iterator itAll = allAnimals.begin();
            itAll != allAnimals.end(); ++itAll)
    {
        //Check life of aphid or ladybug
        if((*itAll)->getLife() <= 0)
        {
            //If aphid or ladybug is dead, mark for death
            deadAnimals.push_back(*itAll);
            cout << "Animal" <<  "has died" << endl;
        }
        else
        {
            //Update aphid or ladybug position on grid
            if((*itAll)->update(currentGrid.getHeight(), currentGrid.getWidth()))
            {
                for(vector<Animal*>::iterator itCheck = itAll;
                        itCheck != itAll; ++ itCheck)
                {
                    if(*itAll != *itCheck)
                    {
                        if((*itAll)->getHeight() == (*itCheck)->getHeight() 
                                && (*itAll)->getWidth() 
                                == (*itCheck)->getWidth())
                        {
                            cout << "Two in same position." << endl;
                            cin.get();
                        }
                    }
                }
            }
            else
            {
                cout << "Did not move";
            }
        }
    }

    //Loop through vector of marked for death aphids
    for (vector<Animal*>::iterator itAni = this->deadAnimals.begin();  
            itAni != this->deadAnimals.end(); ++itAni)
    {
        //Loop through vector of alive aphids
        for (vector<Aphid>::iterator itAlive = this->currentAphids.begin();
                itAlive != this->currentAphids.end(); ++itAlive)
        {
            //If an aphid exists in deadAphids that exists in currentAphids, 
            //remove the aphid from currentAphids
            if(&(*itAlive) == *itAni)
            {
                itAlive = currentAphids.erase(itAlive);
                break;
            }
        }
        //Loop through vector of alive ladybugs
        for (vector<Ladybug>::iterator itAlive = this->currentLadys.begin();
                itAlive != this->currentLadys.end(); ++itAlive)
        {
            //If an ladybug exists in deadLadys that exists in currentLadys, 
            //remove the ladybug from currentLadys
            if(&(*itAlive) == *itAni)
            {
                itAlive = currentLadys.erase(itAlive);
                break;
            }
        }
    }
    //Clear the deadAphids vector for the next turn
    this->deadAnimals.clear();

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

/*void Manager::killAnimal(vector<Animal> currentAnimals, 
        vector <Animal*> deadAnimals)
{
    for (vector<Animal*>::iterator itA = this->deadAnimals.begin();  
            itA != this->deadAnimals.end(); ++itA)
    {
        //Loop through vector of alive aphids
        for (vector<Animal>::iterator itAlive = this->currentAnimals.begin();
                itAlive != this->currentAnimals.end(); ++itAlive)
        {
            //If an aphid exists in deadAphids that exists in currentAphids, 
            //remove the aphid from currentAphids
            if(&(*itAlive) == *itA)
            {
                itAlive = currentAnimals.erase(itAlive);
                break;
            }
        }
    }
    //Clear the deadAphids vector for the next turn
    this->deadAnimals.clear();
}*/

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