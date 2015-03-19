#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "Animal.h"
#include "Grid.h"
using namespace std;

class Manager
{
    //Let animal and children see protected variables
    friend class Animal;
    
    //Initialise protected variables
    protected:
        int turn = 0;
        Grid currentGrid;
        vector<Aphid> currentAphids;
        vector<Aphid*> deadAphids;
        vector<Ladybug> currentLadys;
        vector<Ladybug*> deadLadys;
        vector<Animal*> allAnimals;
        vector<Animal*> deadAnimals;
    
    //Define functions to be implemented
    public:
        /**
         * Manager constructor, assigns vectors to the manager
         * @param newAphids
         * @param newLadys
         */
        Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys);
        
        /**
         * Sets up the grid with inputted values
         * @param gridHeight
         * @param gridWidth
         */
        void setupGrid(int gridHeight, int gridWidth);
        
        /**
         * Resets the vector which holds all the animals, and fills it with updated 
         * vectors at any point in the simulation. Ensures no dangling pointers to 
         * deleted objects
         */
        void setVectors();
        
        /**
         * This function is the core of the program. It loops through vectors 
         * of aphids and ladybugs, and updates them in turn based on their 
         * probability. If an aphid and a ladybug meet in one cell, there's a 
         * chance for them to fight. If two of the same kind meet in one cell, 
         * there's a chance for them to reproduce. This functions ties in 
         * Functionality from all sections of the code to make the program do 
         * what it is supposed to do.
         */
        void updateAll();
        
        /**
         * Checks if an animal is in the same cell as another animal
         * @param movedAnimal
         * @param currentAnimal
         * @return boolean
         */
        bool checkSameCell(Animal &movedAnimal, Animal &currentAnimal);
        
        void killAnimal(vector<Animal> currentAnimals, 
            vector <Animal*> deadAnimals);
        
        /**
         * This function marks a specific animal for death.
         * Not used in the program, but can be used for debugging
         * @param animalToKill
         */
        void markDeath(Animal &animalToKill);
        
        /**
         * This function marks a specific animal for reproduction.
         * Not used in the program, but can be used for debugging
         * @param animalToReproduce
         */
        void markReproduce(Animal &animalToReproduce);
};

#endif