#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "Animal.h"
#include "Grid.h"
using namespace std;


class Manager
{
    friend class Animal;
    
    protected:
        float aphidMoveProb, ladyMoveProb, ladyDirectionProb;
        Grid currentGrid;
        vector<Aphid> currentAphids;
        vector<Ladybug> currentLadys;
    
    public:
        Manager(vector<Aphid> newAphids, vector<Ladybug> newLadys, 
        float tempAphidMove, float tempLadyMove, float tempLadyDir);
        
        void setVectors(vector<Aphid> newAphids, vector<Ladybug> newLadys);
        
        void updateAll();
        
        void fight(Animal movedAnimal, Animal currentAnimal);
        
        bool checkProbability(float probToCheck);
};


#endif