#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Manager.h"
#include "Grid.h"
using namespace std;

/**
 * Manager constructor, assigns vectors to the manager
 * @param newAphids
 * @param newLadys
 */
Manager::Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys)
{
    currentAphids = newAphids;
    currentLadys = newLadys;
}

/**
 * Sets up the grid with inputted values
 * @param gridHeight
 * @param gridWidth
 */
void Manager::setupGrid(int gridHeight, int gridWidth)
{
    currentGrid.setHeight(gridHeight);
    currentGrid.setWidth(gridWidth);
    currentGrid.drawGrid(currentAphids, currentLadys);
}

/**
 * Resets the vector which holds all the animals, and fills it with updated 
 * vectors at any point in the simulation. Ensures no dangling pointers to 
 * deleted objects
 */
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
        if((*itAll)->getLife() <= 0)
        {
            //If aphid or ladybug is dead, mark it for death
            (*itAll)->setDead(true);
        }
        //If aphid or ladybug still has life
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
                        if(checkSameCell (**itAll, **itCheck))
                        {
                            /***************DEBUGGING COUTS********************/
                            //cout << "Two in same position" << endl;
                            //Draw the grid to show them in same cell
                            //this->currentGrid.drawGrid(this->currentAphids, 
                            //        this->currentLadys);
                            /**************************************************/
                            /**
                             * Use visitor pattern to call correct function
                             * polymorphically. This marks an aphid or ladybug
                             * for death or reproduction
                             */
                            (*itAll)->visitWith(**itCheck);
                            //cin.get(); //For debugging each update
                        }
                    }
                }
            }
            else //For debugging, or future extensions
            {
                //cout << "Did not move";
            }
        }
    }
    
    //Loop through currentAphids vector
    vector<Aphid>::iterator iA = currentAphids.begin();
    while(iA != currentAphids.end())
    {
        //If an aphid is marked for death
        if(iA->getDead())
        {
            //Delete and destruct aphid
            iA = currentAphids.erase(iA);
        }
        //Or increment iterator
        else
        {
            ++iA;
        }
    }
    //Reset iterator
    iA = currentAphids.begin();
    //Loop through currentAphids again
    while(iA != currentAphids.end())
    {
        //If an aphid is marked for reproduction
        if(iA->getReproduce())
        {
            //Create a new aphid object at the end of the vector with same 
            //variables as parent
            currentAphids.emplace_back(iA->getHeight(), iA->getWidth(), 
                    iA->getMoveProb(), iA->getReproduceProb(), 
                    iA->getFightProb(), iA->getGroupKillProb());
            //Reset reproduce marker 
            iA->setReproduce(false);
            //Reset iterator
            iA = currentAphids.begin();
        }
        //Increment iterator
        ++iA;
    }
    
    //Loop through currentLadys vector
    vector<Ladybug>::iterator l = currentLadys.begin();
    while(l != currentLadys.end())
    {
        //If a ladybug is marked for death
        if(l->getDead())
        {
            //Delete and destruct ladybug
            l = currentLadys.erase(l);
        }
        //Or increment iterator
        else
        {
            ++l;
        }
    }
    //Reset iterator
    l = currentLadys.begin();
    //Loop through currentLadys again
    while(l != currentLadys.end())
    {
        //If a ladybug is marked for reproduction
        if(l->getReproduce())
        {
            //Create a new ladybug object at the end of the vector with same 
            //variables as parent
            currentLadys.emplace_back(l->getHeight(), l->getWidth(), l->getMoveProb(), 
                    l->getReproduceProb(), l->getFightProb(), 
                    l->getDirChangeProb());
            //Reset reproduce marker
            l->setReproduce(false);
            //Reset iterator
            l = currentLadys.begin();
        }
        //Increment iterator
        ++l;
    }
    
    //Update allAnimals vector with updated positions and animals
    setVectors();
    
    /*******ENABLE THIS IF YOU WANT STATISTICS FOR EACH OBJECT*****************/ 
    /*****************BAD FOR LONG SIMULATIONS*********************************/
    /*for (vector<Animal*>::iterator a = this->allAnimals.begin();
        a != this->allAnimals.end(); ++a)
    {
        if(!(**a).getDead())
        {
            cout << endl << "Width: " << (*a)->getWidth() << "Height: " 
                    << (*a)->getHeight() << "Life: " << (*a)->getLife() << endl;
        }
    }*/
    
    //Print out remaining ladybugs and aphids
    cout << "Aphids: " << currentAphids.size() << endl << "Ladybugs: " 
            << currentLadys.size();
    //Print out turn number
    cout << endl << "Turn: " << turn++ << endl;
    //Draw grid with all updated data
    this->currentGrid.drawGrid(this->currentAphids, this->currentLadys);
}

/**
 * Checks if an animal is in the same cell as another animal
 * @param movedAnimal
 * @param currentAnimal
 * @return boolean
 */
bool Manager::checkSameCell(Animal &movedAnimal, Animal &currentAnimal)
{
    //If the getHeight() and getWidth() functions return the same values, they 
    //are in the same cell
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

/**
 * This function marks a specific animal for death.
 * Not used in the program, but can be used for debugging
 * @param animalToKill
 */
void Manager::markDeath(Animal &animalToKill)
{
    animalToKill.setDead(true);
}

/**
 * This function marks a specific animal for reproduction.
 * Not used in the program, but can be used for debugging
 * @param animalToReproduce
 */
void Manager::markReproduce(Animal &animalToReproduce)
{
    animalToReproduce.setReproduce(true);
}
