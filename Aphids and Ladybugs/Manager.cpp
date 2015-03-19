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
    this->allAnimals.clear();
    this->currentAphids.shrink_to_fit();
    this->currentLadys.shrink_to_fit();
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
    this->allAnimals.shrink_to_fit();
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
        bool checker = false;
        if((*itAll)->getLife() <= 0)
        {
            //If aphid or ladybug is dead, mark for death
            (*itAll)->setDead(true);
            //deadAnimals.push_back(*itAll);
            //cout << "Animal" <<  "has died" << endl;
        }
        else
        {
            //Update aphid or ladybug position on grid
            if((*itAll)->update(currentGrid.getHeight(), 
                    currentGrid.getWidth()))
            {
                //Loop through vector of animals again
                for(vector<Animal*>::iterator itCheck = allAnimals.begin();
                        itCheck != allAnimals.end(); ++ itCheck)
                {
                    //Don't compare to self
                    if(*itAll != *itCheck)
                    {
                        //If two animals are in the same cell
                        if(checkFight (**itAll, **itCheck))
                        {
                            //cout << "Two in same position" << endl;
                            //Draw the grid to show them in same cell
                            //this->currentGrid.drawGrid(this->currentAphids, 
                            //        this->currentLadys);
                            //Use visitor pattern to call correct function
                            //polymorphically
                            (*itAll)->visitWith(**itCheck);
                            //cin.get();
                        }
                    }
                }
            }
            else
            {
                //cout << "Did not move";
            }
        }
    }

        vector<Aphid>::iterator iA = currentAphids.begin();
        while(iA != currentAphids.end())
        {
            if(iA->getDead())
            {
                iA = currentAphids.erase(iA);
                ++iA;
            }
            else
            {
                ++iA;
            }
        }
        iA = currentAphids.begin();
        while(iA != currentAphids.end())
        {
            if(iA->getReproduce())
            {
                currentAphids.emplace_back(iA->getHeight(), iA->getWidth(), iA->getMoveProb(), 
                        iA->getReproduceProb(), iA->getFightProb(), 
                        iA->getGroupKillProb());
                //allAnimals.push_back(&newLady);
                iA->setReproduce(false);
                //setVectors();
                //break;
                iA = currentAphids.begin();
            }
            ++iA;
        }

        vector<Ladybug>::iterator l = currentLadys.begin();
        while(l != currentLadys.end())
        {
            if(l->getDead())
            {
                l = currentLadys.erase(l);
                ++l;
            }
            else
            {
                ++l;
            }
        }
        l = currentLadys.begin();
        while(l != currentLadys.end())
        {
            if(l->getReproduce())
            {
                currentLadys.emplace_back(l->getHeight(), l->getWidth(), l->getMoveProb(), 
                        l->getReproduceProb(), l->getFightProb(), 
                        l->getDirChangeProb());
                l->setReproduce(false);
                l = currentLadys.begin();
            }
            ++l;
        }
    //}
    setVectors();
    for (vector<Animal*>::iterator a = this->allAnimals.begin();
        a != this->allAnimals.end(); ++a)
    {
        //if(!(**a).getDead())
        //{
            //cout << endl << "Width: " << (*a)->getWidth() << "Height: " << (*a)->getHeight() << "Life: " << (*a)->getLife() << endl;
       // }
    }
    //Print out remaining ladybugs and aphids
    cout << "Aphids: " << currentAphids.size() << endl << "Ladybugs: " 
            << currentLadys.size();
    //Print out turn number
    cout << endl << "Turn: " << turn++ << endl;
    //Draw grid with all updated data
    this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
}

bool Manager::checkFight(Animal &movedAnimal, Animal &currentAnimal)
{
    if(movedAnimal.getHeight() == currentAnimal.getHeight() 
            && movedAnimal.getWidth() == currentAnimal.getWidth())
    {
        return true;
    }
    else
    {
        return false;
    }
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

void Manager::kill(Animal &animalToKill)
{
    animalToKill.setDead(true);
    
    /*for(vector<Animal*>::iterator itCheck = allAnimals.begin();
            itCheck != allAnimals.end(); ++ itCheck)
    {
        if(*itCheck == &animalToKill)
        {
            
        }
    }*/
        //this->currentAphids.erase(animalToKill);
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