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
        Grid currentGrid;
        vector<Aphid> currentAphids;
        vector<Ladybug> currentLadys;
    
    public:
        
        void setVectors(vector<Aphid> newAphids, vector<Ladybug> newLadys);
        
        void updateAll();
};


#endif