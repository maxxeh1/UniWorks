#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "Animal.h"
#include "Grid.h"
using namespace std;


class Manager
{
    friend class Animal;
    
    protected:
        int turn = 0;
        float aphidMoveProb, ladyMoveProb, ladyDirectionProb;
        Grid currentGrid;
        vector<Aphid> currentAphids;
        vector<Aphid*> deadAphids;
        vector<Ladybug> currentLadys;
        vector<Ladybug*> deadLadys;
        vector<Animal*> allAnimals;
        vector<Animal*> deadAnimals;
    
    public:
        Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys);
        
        void setupGrid(int gridHeight, int gridWidth);
        
        void setVectors();
        
        void updateAll();
        
        void fight(Animal movedAnimal, Animal currentAnimal);
        
        void killAnimal(vector<Animal> currentAnimals, 
            vector <Animal*> deadAnimals);
        
        bool checkProbability(float probToCheck);
};


#endif